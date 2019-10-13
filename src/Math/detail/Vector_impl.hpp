//////////////////////////////////////////////////////////////////////////////
//
//            Copyright (c) 2019 Ronnie Brohn (EpicBrownie)      
//
//                Distributed under The MIT License (MIT).
//              (See accompanying file LICENSE or copy at 
//                 https://opensource.org/licenses/MIT)
//
//           Please report any bugs, typos, or suggestions to
//             https://github.com/unstable-sort/Epic/issues
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Vector_decl.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <type_traits>

#include "VectorBase.h"
#include "Quaternion_decl.h"
#include "MetaHelpers.hpp"
#include "../Angle.h"
#include "../Tags.h"
#include "../../Meta/Utility.hpp"

//////////////////////////////////////////////////////////////////////////////

// Vector
template<class T, size_t N>
class Epic::Vector : public Epic::detail::VectorBase<T, N>
{
public:
	using type = Epic::Vector<T, N>;
	using base_type = Epic::detail::VectorBase<T, N>;

public:
	using base_type::Values;

public:
	Vector() noexcept = default;
	Vector(const Vector&) noexcept = default;
	Vector(Vector&&) noexcept = default;
	~Vector() noexcept = default;

	Vector(const ZeroesTag&) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) = T(0);
	}

	Vector(const OnesTag&) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) = T(1);
	}

	Vector(const IdentityTag&) noexcept
	{
		if constexpr (N > 1)
		{
			for (size_t n = 0; n < N - 1; ++n)
				at(n) = T(0);
		}

		at(N - 1) = T(1);
	}

	template<class... Us, typename = std::enable_if_t<
		!Meta::IsVariadicTypeOf<type, Us...> &&
		!detail::HasTag_v<Us...> &&
		detail::Span_v<Us...> == N>>
	Vector(Us&&... values) noexcept
	{
		detail::SpanConstructor<T>::Construct(std::begin(Values), std::forward<Us>(values)...);
	}

public:
	constexpr const T& at(size_t index) const
	{
		return Values[index];
	}

	constexpr T& at(size_t index)
	{
		return Values[index];
	}

	constexpr const T& operator[] (size_t index) const
	{
		return Values[index];
	}

	constexpr T& operator[] (size_t index)
	{
		return Values[index];
	}

public:
	template<class... Us, typename = std::enable_if_t<detail::Span_v<Us...> == N>>
	constexpr type& Reset(Us&&... values) noexcept
	{
		detail::SpanConstructor<T>::Construct(std::begin(Values), std::forward<Us>(values)...);

		return *this;
	}

	constexpr type& Fill(T value) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) = value;

		return *this;
	}

	constexpr type& Clamp(T minValue, T maxValue) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) = std::min(std::max(minValue, at(n)), maxValue);

		return *this;
	}

	type& Normalize() noexcept
	{
		return *this /= Magnitude();
	}

	type& NormalizeSafe() noexcept
	{
		const auto m = Magnitude();

		return (m == T(0)) ? (*this) : (*this /= m);
	}

	type& Power(T exp) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) = static_cast<T>(std::pow(at(n), exp));

		return *this;
	}

	type& Power(type exp) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) = static_cast<T>(std::pow(at(n), exp[n]));

		return *this;
	}

public:
	constexpr auto Cross(type vec) const noexcept
	{
		if constexpr (N == 1)
			assert(false && "Cannot compute the cross product of Vectors of size 1.");

		else if constexpr (N == 2)
			return T{ at(0) * vec[1] - at(1) * vec[0] };

		else if constexpr (N == 3)
			return type
			{
				at(1) * vec[2] - at(2) * vec[1],
				at(2) * vec[0] - at(0) * vec[2],
				at(0) * vec[1] - at(1) * vec[0]
			};

		else if constexpr (N > 3)
		{
			type result;

			result[0] = at(1) * vec[2] - at(2) * vec[1];
			result[1] = at(2) * vec[0] - at(0) * vec[2];
			result[2] = at(0) * vec[1] - at(1) * vec[0];

			return result;
		}
	}

	type Project(type axis) const noexcept;

	type ProjectN(type axis) const noexcept;

	type Reflect(type normal) const noexcept;

	type Refract(type normal, T eta) const noexcept;

public:
	constexpr T Dot(type vec) const noexcept
	{
		if constexpr (N == 1)
			return at(0) * vec[0];

		else if constexpr (N == 2)
			return at(0) * vec[0] + at(1) * vec[1];

		else if constexpr (N == 3)
			return at(0) * vec[0] + at(1) * vec[1] + at(2) * vec[2];

		else if constexpr (N == 4)
			return at(0) * vec[0] + at(1) * vec[1] + at(2) * vec[2] + at(3) * vec[3];

		else if constexpr (N > 4)
		{
			T result = T(0);

			for (size_t n = 0; n < N; ++n)
				result += at(n) * vec[n];

			return result;
		}
	}

	constexpr T MagnitudeSq() const noexcept
	{
		return Dot(*this);
	}

	constexpr T ProjectionMagnitude(type axis) const noexcept
	{
		return { Dot(axis) / axis.MagnitudeSq() };
	}

	T Magnitude() const noexcept
	{
		return { static_cast<T>(std::sqrt(MagnitudeSq())) };
	}

public:
	static auto MixOf(const type& vecA, const type& vecB, const T w = T(0.5)) noexcept
	{
		return vecA + ((vecB - vecA) * w);
	}

	static type NormalOf(type vec) noexcept
	{
		return vec.Normalize();
	}

	static type SafeNormalOf(type vec) noexcept
	{
		return vec.NormalizeSafe();
	}

	static type OrthoNormalOf(const type& vecA, const type& vecB) noexcept
	{
		return NormalOf(vecA - vecB * vecB.Dot(vecA));
	}

public:
	type& operator *= (const Quaternion<T>& quat) noexcept;

	type operator - () const noexcept
	{
		if constexpr (N == 1)
			return { -at(0) };

		else if constexpr (N == 2)
			return { -at(0), -at(1) };

		else if constexpr (N == 3)
			return { -at(0), -at(1), -at(2) };

		else if constexpr (N == 4)
			return { -at(0), -at(1), -at(2), -at(3) };

		else
		{
			type result;

			for (size_t n = 0; n < N; ++n)
				result[n] = -at(n);

			return result;
		}
	}

	template<typename = std::enable_if_t<(N == 1)>>
	operator T() const noexcept
	{
		return at(0);
	}

	type& operator = (const IdentityTag&) noexcept
	{
		if constexpr (N > 1)
		{
			for (size_t n = 0; n < N - 1; ++n)
				at(n) = T(0);
		}

		at(N - 1) = T(1);

		return *this;
	}

public:
	#pragma region Assignment Operators

	type& operator = (T value) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) = value;

		return *this;
	}

	type& operator += (T value) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) += value;

		return *this;
	}

	type& operator -= (T value) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) -= value;

		return *this;
	}

	type& operator *= (T value) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) *= value;

		return *this;
	}

	type& operator /= (T value) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) /= value;

		return *this;
	}

	type& operator = (const T(&values)[N]) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) = values[n];

		return *this;
	}

	type& operator += (const T(&values)[N]) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) += values[n];

		return *this;
	}

	type& operator -= (const T(&values)[N]) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) -= values[n];

		return *this;
	}

	type& operator *= (const T(&values)[N]) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) *= values[n];

		return *this;
	}

	type& operator /= (const T(&values)[N]) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) /= values[n];

		return *this;
	}

	type& operator = (const type& vec) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) = vec[n];

		return *this;
	}

	type& operator = (type&& vec) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) = vec[n];

		return *this;
	}

	type& operator += (const type& vec) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) += vec[n];

		return *this;
	}

	type& operator -= (const type& vec) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) -= vec[n];

		return *this;
	}

	type& operator *= (const type& vec) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) *= vec[n];

		return *this;
	}

	type& operator /= (const type& vec) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) /= vec[n];

		return *this;
	}

	template<size_t M, size_t... Indices, typename = std::enable_if_t<(sizeof...(Indices) == N)>>
	type& operator = (const detail::VectorSwizzler<T, M, Indices...>& vec) noexcept
	{
		vec.IterateN([&](size_t iOther, size_t iThis) { at(iThis) = vec[iOther]; });

		return *this;
	}

	template<size_t M, size_t... Indices, typename = std::enable_if_t<(sizeof...(Indices) == N)>>
	type& operator += (const detail::VectorSwizzler<T, M, Indices...>& vec) noexcept
	{
		vec.IterateN([&](size_t iOther, size_t iThis) { at(iThis) += vec[iOther]; });

		return *this;
	}

	template<size_t M, size_t... Indices, typename = std::enable_if_t<(sizeof...(Indices) == N)>>
	type& operator -= (const detail::VectorSwizzler<T, M, Indices...>& vec) noexcept
	{
		vec.IterateN([&](size_t iOther, size_t iThis) { at(iThis) -= vec[iOther]; });

		return *this;
	}

	template<size_t M, size_t... Indices, typename = std::enable_if_t<(sizeof...(Indices) == N)>>
	type& operator *= (const detail::VectorSwizzler<T, M, Indices...>& vec) noexcept
	{
		vec.IterateN([&](size_t iOther, size_t iThis) { at(iThis) *= vec[iOther]; });

		return *this;
	}

	template<size_t M, size_t... Indices, typename = std::enable_if_t<(sizeof...(Indices) == N)>>
	type& operator /= (const detail::VectorSwizzler<T, M, Indices...>& vec) noexcept
	{
		vec.IterateN([&](size_t iOther, size_t iThis) { at(iThis) /= vec[iOther]; });

		return *this;
	}
	
	#pragma endregion

public:
	#pragma region Logic Assignment Operators

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type& operator |= (T value) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) |= value;

		return *this;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type& operator &= (T value) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) &= value;

		return *this;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type& operator ^= (T value) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) ^= value;

		return *this;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type& operator %= (T value) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) %= value;

		return *this;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type& operator <<= (T value) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) <<= value;

		return *this;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type& operator >>= (T value) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) >>= value;

		return *this;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type& operator |= (const T(&values)[N]) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) |= values[n];

		return *this;													
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type& operator &= (const T(&values)[N]) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) &= values[n];

		return *this;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type& operator ^= (const T(&values)[N]) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) ^= values[n];

		return *this;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type& operator %= (const T(&values)[N]) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) %= values[n];

		return *this;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type& operator <<= (const T(&values)[N]) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) <<= values[n];

		return *this;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type& operator >>= (const T(&values)[N]) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) >>= values[n];

		return *this;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type& operator |= (const type& vec) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) |= vec[n];

		return *this;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type& operator &= (const type& vec) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) &= vec[n];

		return *this;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type& operator ^= (const type& vec) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) ^= vec[n];

		return *this;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type& operator %= (const type& vec) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) %= vec[n];

		return *this;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type& operator <<= (const type& vec) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) <<= vec[n];

		return *this;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type& operator >>= (const type& vec) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			at(n) >>= vec[n];

		return *this;
	}
																		
	template<size_t M, size_t... Indices, 
		typename = std::enable_if_t<(std::is_integral_v<T> && sizeof...(Indices) == N)>>
	type& operator |= (const detail::VectorSwizzler<T, M, Indices...>& vec) noexcept		
	{
		vec.IterateN([&](size_t iOther, size_t iThis) { at(iThis) |= vec[iOther]; });			
		
		return *this;													
	}
	
	template<size_t M, size_t... Indices,
		typename = std::enable_if_t<(std::is_integral_v<T> && sizeof...(Indices) == N)>>
		type& operator &= (const detail::VectorSwizzler<T, M, Indices...>& vec) noexcept
	{
		vec.IterateN([&](size_t iOther, size_t iThis) { at(iThis) &= vec[iOther]; });
		
		return *this;
	}

	template<size_t M, size_t... Indices,
		typename = std::enable_if_t<(std::is_integral_v<T> && sizeof...(Indices) == N)>>
	type& operator ^= (const detail::VectorSwizzler<T, M, Indices...>& vec) noexcept
	{
		vec.IterateN([&](size_t iOther, size_t iThis) { at(iThis) ^= vec[iOther]; });
		
		return *this;
	}

	template<size_t M, size_t... Indices,
		typename = std::enable_if_t<(std::is_integral_v<T> && sizeof...(Indices) == N)>>
	type& operator %= (const detail::VectorSwizzler<T, M, Indices...>& vec) noexcept
	{
		vec.IterateN([&](size_t iOther, size_t iThis) { at(iThis) %= vec[iOther]; });
		
		return *this;
	}

	template<size_t M, size_t... Indices,
		typename = std::enable_if_t<(std::is_integral_v<T> && sizeof...(Indices) == N)>>
	type& operator <<= (const detail::VectorSwizzler<T, M, Indices...>& vec) noexcept
	{
		vec.IterateN([&](size_t iOther, size_t iThis) { at(iThis) <<= vec[iOther]; });

		return *this;
	}

	template<size_t M, size_t... Indices,
		typename = std::enable_if_t<(std::is_integral_v<T> && sizeof...(Indices) == N)>>
	type& operator >>= (const detail::VectorSwizzler<T, M, Indices...>& vec) noexcept
	{
		vec.IterateN([&](size_t iOther, size_t iThis) { at(iThis) >>= vec[iOther]; });
		
		return *this;
	}

	#pragma endregion

public:
	#pragma region Arithmetic Operators

	type operator + (T value) const noexcept
	{
		return type(*this) += std::move(value);
	}

	type operator - (T value) const noexcept
	{
		return type(*this) -= std::move(value);
	}

	type operator * (T value) const noexcept
	{
		return type(*this) *= std::move(value);
	}

	type operator / (T value) const noexcept
	{
		return type(*this) /= std::move(value);
	}

	type operator + (const T(&values)[N]) const	noexcept
	{
		return type(*this) += values;
	}

	type operator - (const T(&values)[N]) const	noexcept
	{
		return type(*this) -= values;
	}

	type operator * (const T(&values)[N]) const	noexcept
	{
		return type(*this) *= values;
	}

	type operator / (const T(&values)[N]) const	noexcept
	{
		return type(*this) /= values;
	}

	type operator + (type vec) const noexcept
	{
		return type(*this) += std::move(vec);
	}

	type operator - (type vec) const noexcept
	{
		return type(*this) -= std::move(vec);
	}

	type operator * (type vec) const noexcept
	{
		return type(*this) *= std::move(vec);
	}

	type operator / (type vec) const noexcept
	{
		return type(*this) /= std::move(vec);
	}

	template<size_t M, size_t... Indices, typename = std::enable_if_t<(sizeof...(Indices) == N)>>
	type operator + (const detail::VectorSwizzler<T, M, Indices...>& vec) const noexcept
	{
		return type(*this) += vec;
	}

	template<size_t M, size_t... Indices, typename = std::enable_if_t<(sizeof...(Indices) == N)>>
	type operator - (const detail::VectorSwizzler<T, M, Indices...>& vec) const noexcept
	{
		return type(*this) -= vec;
	}

	template<size_t M, size_t... Indices, typename = std::enable_if_t<(sizeof...(Indices) == N)>>
	type operator * (const detail::VectorSwizzler<T, M, Indices...>& vec) const noexcept
	{
		return type(*this) *= vec;
	}

	template<size_t M, size_t... Indices, typename = std::enable_if_t<(sizeof...(Indices) == N)>>
	type operator / (const detail::VectorSwizzler<T, M, Indices...>& vec) const noexcept
	{
		return type(*this) /= vec;
	}
	
	friend type operator + (T value, type vec) noexcept
	{
		return type(std::move(vec)) += std::move(value);
	}

	friend type operator - (T value, type vec) noexcept
	{
		return type(std::move(vec)) -= std::move(value);
	}

	friend type operator * (T value, type vec) noexcept
	{
		return type(std::move(vec)) *= std::move(value);
	}

	friend type operator / (T value, type vec) noexcept
	{
		return type(std::move(vec)) /= std::move(value);
	}

	#pragma endregion

public:
	#pragma region Logic Arithmetic Operators

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type operator | (T value) const noexcept
	{
		return type(*this) |= std::move(value);
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type operator & (T value) const noexcept
	{
		return type(*this) &= std::move(value);
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type operator ^ (T value) const noexcept
	{
		return type(*this) ^= std::move(value);
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type operator % (T value) const noexcept
	{
		return type(*this) %= std::move(value);
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type operator << (T value) const noexcept
	{
		return type(*this) <<= std::move(value);
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type operator >> (T value) const noexcept
	{
		return type(*this) >>= std::move(value);
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type operator | (const T(&values)[N]) const	noexcept
	{
		return type(*this) |= values;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type operator & (const T(&values)[N]) const	noexcept
	{
		return type(*this) &= values;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type operator ^ (const T(&values)[N]) const	noexcept
	{
		return type(*this) ^= values;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type operator % (const T(&values)[N]) const	noexcept
	{
		return type(*this) %= values;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type operator << (const T(&values)[N]) const	noexcept
	{
		return type(*this) <<= values;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type operator >> (const T(&values)[N]) const	noexcept
	{
		return type(*this) >>= values;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type operator | (type vec) const noexcept
	{
		return type(*this) |= std::move(vec);
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type operator & (type vec) const noexcept
	{
		return type(*this) &= std::move(vec);
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type operator ^ (type vec) const noexcept
	{
		return type(*this) ^= std::move(vec);
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type operator % (type vec) const noexcept
	{
		return type(*this) %= std::move(vec);
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type operator << (type vec) const noexcept
	{
		return type(*this) <<= std::move(vec);
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	type operator >> (type vec) const noexcept
	{
		return type(*this) >>= std::move(vec);
	}

	template<size_t M, size_t... Indices, 
		typename = std::enable_if_t<(std::is_integral_v<T> && sizeof...(Indices) == N)>>
	type operator | (const detail::VectorSwizzler<T, M, Indices...>& vec) const noexcept
	{
		return type(*this) |= vec;
	}

	template<size_t M, size_t... Indices, 
		typename = std::enable_if_t<(std::is_integral_v<T> && sizeof...(Indices) == N)>>
	type operator & (const detail::VectorSwizzler<T, M, Indices...>& vec) const noexcept
	{
		return type(*this) &= vec;
	}

	template<size_t M, size_t... Indices, 
		typename = std::enable_if_t<(std::is_integral_v<T> && sizeof...(Indices) == N)>>
	type operator ^ (const detail::VectorSwizzler<T, M, Indices...>& vec) const noexcept
	{
		return type(*this) ^= vec;
	}

	template<size_t M, size_t... Indices,
		typename = std::enable_if_t<(std::is_integral_v<T> && sizeof...(Indices) == N)>>
	type operator % (const detail::VectorSwizzler<T, M, Indices...>& vec) const noexcept
	{
		return type(*this) %= vec;
	}

	template<size_t M, size_t... Indices, 
		typename = std::enable_if_t<(std::is_integral_v<T> && sizeof...(Indices) == N)>>
	type operator << (const detail::VectorSwizzler<T, M, Indices...>& vec) const noexcept
	{
		return type(*this) <<= vec;
	}

	template<size_t M, size_t... Indices, 
		typename = std::enable_if_t<(std::is_integral_v<T> && sizeof...(Indices) == N)>>
	type operator >> (const detail::VectorSwizzler<T, M, Indices...>& vec) const noexcept
	{
		return type(*this) >>= vec;
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	friend type operator | (T value, type vec) noexcept
	{
		return type(std::move(vec)) |= std::move(value);
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	friend type operator & (T value, type vec) noexcept
	{
		return type(std::move(vec)) &= std::move(value);
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	friend type operator ^ (T value, type vec) noexcept
	{
		return type(std::move(vec)) ^= std::move(value);
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	friend type operator % (T value, type vec) noexcept
	{
		return type(std::move(vec)) %= std::move(value);
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	friend type operator << (T value, type vec) noexcept
	{
		return type(std::move(vec)) <<= std::move(value);
	}

	template<typename = std::enable_if_t<std::is_integral_v<T>>>
	friend type operator >> (T value, type vec) noexcept
	{
		return type(std::move(vec)) >>= std::move(value);
	}

	#pragma endregion
};

//////////////////////////////////////////////////////////////////////////////

// Implementation
namespace Epic
{
	template<class T, size_t N>
	Vector<T, N> Vector<T, N>::Project(type axis) const noexcept
	{
		return axis *= ProjectionMagnitude(axis);
	}

	template<class T, size_t N>
	Vector<T, N> Vector<T, N>::ProjectN(type axis) const noexcept
	{
		axis.Normalize();
		return axis * Dot(axis);
	}

	template<class T, size_t N>
	Vector<T, N> Vector<T, N>::Reflect(type normal) const noexcept
	{
		return type(*this) - (normal * T(2) * Dot(normal));
	}

	template<class T, size_t N>
	Vector<T, N> Vector<T, N>::Refract(type normal, T eta) const noexcept
	{
		type vI = type::NormalOf(*this);
		type vN = normal;

		const T NdotI = vN.Dot(vI);
		const T k = T(1) - (eta * eta * (T(1) - NdotI * NdotI));

		if (k < T(0))
			return{ Zero };

		vI *= eta;
		vN *= eta * NdotI + T(std::sqrt(k));
		vI -= vN;

		return vI;
	}
}

//////////////////////////////////////////////////////////////////////////////

// Friend Operators
namespace Epic
{
	template<class T, size_t N>
	inline bool operator == (const Vector<T, N>& vecA, const Vector<T, N>& vecB) noexcept
	{
		for (size_t n = 0; n < N; ++n)
			if (vecA[n] != vecB[n]) return false;

		return true;
	}

	template<class T, size_t N>
	inline bool operator != (const Vector<T, N>& vecA, const Vector<T, N>& vecB) noexcept
	{
		return !(vecA == vecB);
	}

	template<class T, size_t N>
	inline std::ostream& operator << (std::ostream& stream, const Vector<T, N>& vec)
	{
		stream << '[';
		for (size_t n = 0; n < N; ++n)
		{
			if (n > 0) stream << ", ";
			stream << vec[n];
		}
		stream << ']';

		return stream;
	}

	template<class T, size_t N>
	inline std::wostream& operator << (std::wostream& stream, const Vector<T, N>& vec)
	{
		stream << L'[';
		for (size_t n = 0; n < N; ++n)
		{
			if (n > 0) stream << L", ";
			stream << vec[n];
		}
		stream << L']';

		return stream;
	}

	template<class T, size_t N>
	inline std::istream& operator >> (std::istream& stream, Vector<T, N>& vec)
	{
		if (stream.peek() == '[')
			stream.ignore(1);

		for (size_t n = 0; n < N; ++n)
		{
			if (n > 0 && stream.peek() == ',')
				stream.ignore(1);

			stream >> vec[n];
		}

		if (stream.peek() == ']')
			stream.ignore(1);

		return stream;
	}

	template<class T, size_t N>
	inline std::wistream& operator >> (std::wistream& stream, Vector<T, N>& vec)
	{
		if (stream.peek() == L'[')
			stream.ignore(1);

		for (size_t n = 0; n < N; ++n)
		{
			if (n > 0 && stream.peek() == L',')
				stream.ignore(1);

			stream >> vec[n];
		}

		if (stream.peek() == L']')
			stream.ignore(1);

		return stream;
	}
}

//////////////////////////////////////////////////////////////////////////////

// Deduction Guides
namespace Epic
{
	template<class... Ts, typename = std::enable_if_t<!detail::HasTag_v<Ts...>>>
	Vector(Ts&&... values) -> Vector<Epic::detail::SpanElement_t<Ts...>, Epic::detail::Span_v<Ts...>>;
}

//////////////////////////////////////////////////////////////////////////////

// Algorithms
namespace Epic
{
	namespace
	{
		template<class T, size_t N>
		auto Distance(const Vector<T, N>& vecA, const Vector<T, N>& vecB) noexcept
		{
			return (vecA - vecB).Magnitude();
		}

		template<class T, size_t N>
		auto Mean(const Vector<T, N>& vec) noexcept
		{
			T result = T(0);

			for (size_t n = 0; n < N; ++n)
				result += vec[n];

			return result / T(N);
		}

		template<class T, size_t N>
		auto WeightedMean(const Vector<T, N>& vec, const T(&weights)[N]) noexcept
		{
			T result = T(0);
			T tweights = T(0);

			for (size_t n = 0; n < N; ++n)
			{
				result += vec[n] * weights[n];
				tweights += weights[n];
			}

			assert(tweights != T(0));

			return result / tweights;
		}

		template<class T, size_t N>
		auto Negative(const Vector<T, N>& vec, const T ceil = T(1)) noexcept
		{
			return Vector<T, N>().Fill(ceil) - vec;
		}

		template<class T, size_t N>
		Radian<T> AngleOf(const Vector<T, N>& vecA, const Vector<T, N>& vecB) noexcept
		{
			return { std::acos(vecA.Dot(vecB)) };
		}
	}
}