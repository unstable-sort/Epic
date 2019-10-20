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

#include "VectorSwizzler_decl.h"

#include <cassert>
#include <iostream>

#include "../../Meta/Sequence.hpp"
#include "Vector_decl.h"
#include "VectorData.h"

//////////////////////////////////////////////////////////////////////////////

template<class T, size_t N, size_t... Indices>
class Epic::detail::VectorSwizzler
{
public:
	using type = Epic::detail::VectorSwizzler<T, N, Indices...>;
	using vector_type = Epic::Vector<T, sizeof...(Indices)>;
	using value_type = T;

	static constexpr size_t VectorSize = N;
	static constexpr size_t Size = sizeof...(Indices);

private:
	using TArray = VectorData<T, N>;
	using IndexSeq = Meta::Sequence<size_t, Indices...>;
	using VectorSeq = Meta::MakeSequence<size_t, Size>;
	
	static constexpr bool IsAssignableLValue = Meta::IsSequenceUnique_v<IndexSeq>;

private:
	TArray m_Values;

public:
	VectorSwizzler() noexcept = default;
	VectorSwizzler(const VectorSwizzler&) noexcept = default;
	VectorSwizzler(VectorSwizzler&&) noexcept = default;
	~VectorSwizzler() noexcept = default;

public:
	vector_type ToVector() const noexcept
	{
		vector_type result;

		IterateN([&](size_t src, size_t dest) { result[dest] = m_Values[src]; });

		return result;
	}

	VectorSwizzler& Assign(Epic::Vector<T, sizeof...(Indices)>& vec)
	{
		assert(IsAssignableLValue && "All swizzled indices must be unique to use this operation.");

		Meta::ForEach2<IndexSeq, Meta::MakeSequence<size_t, sizeof...(Indices)>>
			::Call([&](size_t i, size_t j) { m_Values[i] = vec[j]; });

		return *this;
	}

	vector_type operator() () const noexcept
	{
		return ToVector();
	}

	template<typename = std::enable_if_t<(sizeof...(Indices) == 1)>>
	operator T() const noexcept
	{
		return Get<0>();
	}

public:
	template<class Function, class... Args>
	VectorSwizzler& Iterate(Function fn, Args&&... args)
	{
		Meta::ForEach<IndexSeq>::Call(fn, args...);

		return *this;
	}

	template<class Function, class... Args>
	const VectorSwizzler& Iterate(Function fn, Args&&... args) const
	{
		Meta::ForEach<IndexSeq>::Call(fn, args...);

		return *this;
	}

	template<class Function, class... Args>
	VectorSwizzler& IterateN(Function fn, Args&&... args)
	{
		Meta::ForEach2<IndexSeq, VectorSeq>::Call(fn, args...);

		return *this;
	}

	template<class Function, class... Args>
	const VectorSwizzler& IterateN(Function fn, Args&&... args) const
	{
		Meta::ForEach2<IndexSeq, VectorSeq>::Call(fn, args...);

		return *this;
	}

private:
	template<size_t I>
	constexpr T Get() const
	{
		return m_Values[Getter<I, 0, Indices...>::Get()];
	}

	template<size_t I, size_t J, size_t... Rest>
	struct Getter { };

	template<size_t I, size_t J, size_t Current, size_t... Rest>
	struct Getter<I, J, Current, Rest...>
	{
		constexpr static size_t Get()
		{
			static_assert(I < sizeof...(Indices));

			if constexpr (J >= I)
				return Current;
			else
				return Getter<I, I + 1, Rest...>::Get();
		}
	};

public:
	#pragma region Assignment Operators

	VectorSwizzler& operator = (T value) noexcept
	{
		assert(IsAssignableLValue && "All swizzled indices must be unique to use this operator.");

		Iterate([&](size_t i) { m_Values[i] = value; });

		return *this;
	}

	VectorSwizzler& operator += (T value) noexcept
	{
		assert(IsAssignableLValue && "All swizzled indices must be unique to use this operator.");

		Iterate([&](size_t i) { m_Values[i] += value; });

		return *this;
	}

	VectorSwizzler& operator -= (T value) noexcept
	{
		assert(IsAssignableLValue && "All swizzled indices must be unique to use this operator.");

		Iterate([&](size_t i) { m_Values[i] -= value; });

		return *this;
	}

	VectorSwizzler& operator *= (T value) noexcept
	{
		assert(IsAssignableLValue && "All swizzled indices must be unique to use this operator.");

		Iterate([&](size_t i) { m_Values[i] *= value; });

		return *this;
	}

	VectorSwizzler& operator /= (T value) noexcept
	{
		assert(IsAssignableLValue && "All swizzled indices must be unique to use this operator.");

		Iterate([&](size_t i) { m_Values[i] /= value; });

		return *this;
	}

	VectorSwizzler& operator = (const T(&values)[Size]) noexcept
	{
		assert(IsAssignableLValue && "All swizzled indices must be unique to use this operator.");

		IterateN([&](size_t i, size_t j) { m_Values[i] = values[j]; });

		return *this;
	}

	VectorSwizzler& operator += (const T(&values)[Size]) noexcept
	{
		assert(IsAssignableLValue && "All swizzled indices must be unique to use this operator.");

		IterateN([&](size_t i, size_t j) { m_Values[i] += values[j]; });

		return *this;
	}

	VectorSwizzler& operator -= (const T(&values)[Size]) noexcept
	{
		assert(IsAssignableLValue && "All swizzled indices must be unique to use this operator.");

		IterateN([&](size_t i, size_t j) { m_Values[i] -= values[j]; });

		return *this;
	}

	VectorSwizzler& operator *= (const T(&values)[Size]) noexcept
	{
		assert(IsAssignableLValue && "All swizzled indices must be unique to use this operator.");

		IterateN([&](size_t i, size_t j) { m_Values[i] *= values[j]; });

		return *this;
	}

	VectorSwizzler& operator /= (const T(&values)[Size]) noexcept
	{
		assert(IsAssignableLValue && "All swizzled indices must be unique to use this operator.");

		IterateN([&](size_t i, size_t j) { m_Values[i] /= values[j]; });

		return *this;
	}

	VectorSwizzler& operator = (const vector_type& vec) noexcept
	{
		assert(IsAssignableLValue && "All swizzled indices must be unique to use this operator.");

		IterateN([&](size_t i, size_t j) { m_Values[i] = vec[j]; });

		return *this;
	}

	VectorSwizzler& operator += (const vector_type& vec) noexcept
	{
		assert(IsAssignableLValue && "All swizzled indices must be unique to use this operator.");

		IterateN([&](size_t i, size_t j) { m_Values[i] += vec[j]; });

		return *this;
	}

	VectorSwizzler& operator -= (const vector_type& vec) noexcept
	{
		assert(IsAssignableLValue && "All swizzled indices must be unique to use this operator.");

		IterateN([&](size_t i, size_t j) { m_Values[i] -= vec[j]; });

		return *this;
	}

	VectorSwizzler& operator *= (const vector_type& vec) noexcept
	{
		assert(IsAssignableLValue && "All swizzled indices must be unique to use this operator.");

		IterateN([&](size_t i, size_t j) { m_Values[i] *= vec[j]; });

		return *this;
	}

	VectorSwizzler& operator /= (const vector_type& vec) noexcept
	{
		assert(IsAssignableLValue && "All swizzled indices must be unique to use this operator.");

		IterateN([&](size_t i, size_t j) { m_Values[i] /= vec[j]; });

		return *this;
	}

	template<size_t M, size_t... Is, typename = std::enable_if_t<(sizeof...(Is) == Size)>>
	VectorSwizzler& operator = (const VectorSwizzler<T, M, Is...>& vec) noexcept
	{
		assert(IsAssignableLValue && "All swizzled indices must be unique to use this operator.");

		Meta::ForEach2<IndexSeq, typename VectorSwizzler<T, M, Is...>::IndexSeq>
			::Call([&](size_t i, size_t j) { m_Values[i] = vec.m_Values[j]; });

		return *this;
	}

	template<size_t M, size_t... Is, typename = std::enable_if_t<(sizeof...(Is) == Size)>>
	VectorSwizzler& operator += (const VectorSwizzler<T, M, Is...>& vec) noexcept
	{
		assert(IsAssignableLValue && "All swizzled indices must be unique to use this operator.");

		Meta::ForEach2<IndexSeq, typename VectorSwizzler<T, M, Is...>::IndexSeq>
			::Call([&](size_t i, size_t j) { m_Values[i] += vec.m_Values[j]; });

		return *this;
	}

	template<size_t M, size_t... Is, typename = std::enable_if_t<(sizeof...(Is) == Size)>>
	VectorSwizzler& operator -= (const VectorSwizzler<T, M, Is...>& vec) noexcept
	{
		assert(IsAssignableLValue && "All swizzled indices must be unique to use this operator.");

		Meta::ForEach2<IndexSeq, typename VectorSwizzler<T, M, Is...>::IndexSeq>
			::Call([&](size_t i, size_t j) { m_Values[i] -= vec.m_Values[j]; });

		return *this;
	}

	template<size_t M, size_t... Is, typename = std::enable_if_t<(sizeof...(Is) == Size)>>
	VectorSwizzler& operator *= (const VectorSwizzler<T, M, Is...>& vec) noexcept
	{
		assert(IsAssignableLValue && "All swizzled indices must be unique to use this operator.");

		Meta::ForEach2<IndexSeq, typename VectorSwizzler<T, M, Is...>::IndexSeq>
			::Call([&](size_t i, size_t j) { m_Values[i] *= vec.m_Values[j]; });

		return *this;
	}

	template<size_t M, size_t... Is, typename = std::enable_if_t<(sizeof...(Is) == Size)>>
	VectorSwizzler& operator /= (const VectorSwizzler<T, M, Is...>& vec) noexcept
	{
		assert(IsAssignableLValue && "All swizzled indices must be unique to use this operator.");

		Meta::ForEach2<IndexSeq, typename VectorSwizzler<T, M, Is...>::IndexSeq>
			::Call([&](size_t i, size_t j) { m_Values[i] /= vec.m_Values[j]; });

		return *this;
	}

	#pragma endregion

public:
	#pragma region Arithmetic Operators

	auto operator + (T value) const noexcept { return ToVector() + value; }
	auto operator - (T value) const noexcept { return ToVector() - value; }
	auto operator * (T value) const noexcept { return ToVector() * value; }
	auto operator / (T value) const noexcept { return ToVector() / value; }

	auto operator + (const T(&values)[Size]) const noexcept { return ToVector() + values; }
	auto operator - (const T(&values)[Size]) const noexcept { return ToVector() - values; }
	auto operator * (const T(&values)[Size]) const noexcept { return ToVector() * values; }
	auto operator / (const T(&values)[Size]) const noexcept { return ToVector() / values; }

	auto operator + (const vector_type& vec) const noexcept { return ToVector() + vec; }
	auto operator - (const vector_type& vec) const noexcept { return ToVector() - vec; }
	auto operator * (const vector_type& vec) const noexcept { return ToVector() * vec; }
	auto operator / (const vector_type& vec) const noexcept { return ToVector() / vec; }

	template<size_t M, size_t... Is, typename = std::enable_if_t<(sizeof...(Is) == Size)>>
	auto operator + (const VectorSwizzler<T, M, Is...>& vec) const noexcept
	{
		return ToVector() + vec;
	}

	template<size_t M, size_t... Is, typename = std::enable_if_t<(sizeof...(Is) == Size)>>
	auto operator - (const VectorSwizzler<T, M, Is...>& vec) const noexcept
	{
		return ToVector() - vec;
	}

	template<size_t M, size_t... Is, typename = std::enable_if_t<(sizeof...(Is) == Size)>>
	auto operator * (const VectorSwizzler<T, M, Is...>& vec) const noexcept
	{
		return ToVector() * vec;
	}

	template<size_t M, size_t... Is, typename = std::enable_if_t<(sizeof...(Is) == Size)>>
	auto operator / (const VectorSwizzler<T, M, Is...>& vec) const noexcept
	{
		return ToVector() / vec;
	}

	friend vector_type operator + (T value, VectorSwizzler vec) noexcept
	{
		return vector_type().Fill(std::move(value)) + vec.ToVector();
	}

	friend vector_type operator - (T value, VectorSwizzler vec) noexcept
	{
		return vector_type().Fill(std::move(value)) - vec.ToVector();
	}

	friend vector_type operator * (T value, VectorSwizzler vec) noexcept
	{
		return vector_type().Fill(std::move(value)) * vec.ToVector();
	}

	friend vector_type operator / (T value, VectorSwizzler vec) noexcept
	{
		return vector_type().Fill(std::move(value)) / vec.ToVector();
	}

	#pragma endregion

private:
	template<class, size_t, size_t...>
	friend class VectorSwizzler;
};

//////////////////////////////////////////////////////////////////////////////

// Friend Operators
namespace Epic::detail
{
	template<class T, size_t N, size_t... Indices>
	inline std::ostream& operator << (std::ostream& stream, const VectorSwizzler<T, N, Indices...>& vec)
	{
		return stream << vec();
	}

	template<class T, size_t N, size_t... Indices>
	inline std::istream& operator >> (std::istream& stream, VectorSwizzler<T, N, Indices...>& vec)
	{
		Vector<T, sizeof...(Indices)> temp;
		stream >> temp;

		vec.Assign(temp);

		return stream;
	}
}