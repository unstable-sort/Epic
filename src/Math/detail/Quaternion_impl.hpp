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

#include "Quaternion_decl.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <tuple>
#include <type_traits>

#include "../Angle.h"
#include "../Constants.h"
#include "../Tags.h"
#include "../Vector.h"

//////////////////////////////////////////////////////////////////////////////

// Quaternion
template<class T>
class Epic::Quaternion
{
public:
	using type = Epic::Quaternion<T>;
	using value_type = T;
	using container_type = std::array<T, 4>;

	static constexpr size_t Size = 4;

public:
	union
	{
		container_type Values;

		struct { value_type x, y, z, w; };
	};

public:
	Quaternion() noexcept = default;
	Quaternion(const Quaternion&) noexcept = default;
	Quaternion(Quaternion&&) noexcept = default;
	~Quaternion() noexcept = default;

	Quaternion(const T(&values)[Size]) noexcept
	{
		for (size_t i = 0; i < Size; ++i)
			Values[i] = values[i];
	}

	Quaternion(const IdentityTag&) noexcept
	{
		MakeIdentity();
	}

	Quaternion(const XRotationTag&, Radian<T> phi) noexcept
	{
		MakeXRotation(std::move(phi));
	}

	Quaternion(const YRotationTag&, Radian<T> theta) noexcept
	{
		MakeYRotation(std::move(theta));
	}

	Quaternion(const ZRotationTag&, Radian<T> psi) noexcept
	{
		MakeZRotation(std::move(psi));
	}

	Quaternion(Radian<T> pitch, Radian<T> heading, Radian<T> roll) noexcept
	{
		MakeRotation(std::move(pitch), std::move(heading), std::move(roll));
	}

	Quaternion(T xv, T yv, T zv, Radian<T> angle) noexcept
	{
		MakeRotation(std::move(xv), std::move(yv), std::move(zv), std::move(angle));
	}

	Quaternion(Vector<T, 3> axis, Radian<T> angle) noexcept
	{
		MakeRotation(std::move(axis[0]), std::move(axis[1]), std::move(axis[2]), std::move(angle));
	}

	Quaternion(Vector<T, 4> axis, Radian<T> angle) noexcept
	{
		MakeRotation(std::move(axis[0]), std::move(axis[1]), std::move(axis[2]), std::move(angle));
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
	type& Reset(T xv, T yv, T zv, T wv) noexcept
	{
		Values[0] = std::move(xv);
		Values[1] = std::move(yv);
		Values[2] = std::move(zv);
		Values[3] = std::move(wv);

		return *this;
	}

	type& MakeIdentity() noexcept
	{
		return Reset(T(0), T(0), T(0), T(1));
	}

	type& MakeXRotation(Radian<T> phi) noexcept
	{
		const auto[sPhi, cPhi] = (phi / T(2)).SinCos();
		
		return Reset(sPhi, T(0), T(0), cPhi);
	}

	type& MakeYRotation(Radian<T> theta) noexcept
	{
		const auto[sTheta, cTheta] = (theta / T(2)).SinCos();

		return Reset(T(0), sTheta, T(0), cTheta);
	}

	type& MakeZRotation(Radian<T> psi) noexcept
	{
		const auto[sPsi, cPsi] = (psi / T(2)).SinCos();

		return Reset(T(0), T(0), sPsi, cPsi);
	}

	type& MakeRotation(Radian<T> pitch, Radian<T> heading, Radian<T> roll) noexcept
	{
		const auto[sp, cp] = (pitch / T(2)).SinCos();
		const auto[sh, ch] = (heading / T(2)).SinCos();
		const auto[sr, cr] = (roll / T(2)).SinCos();

		return Reset
		(
			(cr * ch * sp) - (sr * sh * cp),
			(cr * sh * cp) + (sr * ch * sp),
			(sr * ch * cp) - (cr * sh * sp),
			(cr * ch * cp) + (sr * sh * sp)
		);
	}

	type& MakeRotation(T xv, T yv, T zv, Radian<T> angle) noexcept
	{
		auto t = xv * xv + yv * yv + zv * zv;
		if (t == T(0))
			return MakeIdentity();

		const auto[sAngle, cAngle] = (angle / T(2)).SinCos();
		t = sAngle / static_cast<T>(std::sqrt(t));

		return Reset(xv * t, yv * t, zv * t, cAngle);
	}

	type& MakeRotation(Vector<T, 3> axis, Radian<T> angle) noexcept
	{
		return MakeRotation(std::move(axis[0]), std::move(axis[1]), std::move(axis[2]), std::move(angle));
	}

	type& MakeRotation(Vector<T, 4> axis, Radian<T> angle) noexcept
	{
		return MakeRotation(std::move(axis[0]), std::move(axis[1]), std::move(axis[2]), std::move(angle));
	}

public:
	Vector<T, 3> Axis() const noexcept
	{
		T t = T(1) - Values[3] * Values[3];
		if (t <= T(0)) return Identity;

		t = T(1) / static_cast<T>(std::sqrt(t));
		return Vector<T, 3>(Values[0] * t, Values[1] * t, Values[2] * t);
	}

	Radian<T> Angle() const noexcept
	{
		return static_cast<T>(std::acos(Values[3])) * T(2);
	}

	Radian<T> Pitch() const noexcept
	{
		const T y = T(2) * (Values[1] * Values[2] + Values[3] * Values[0]);
		const T x = (Values[3] * Values[3]) - (Values[0] * Values[0]) -
					(Values[1] * Values[1]) + (Values[2] * Values[2]);

		if (y == T(0) && x == T(0))
			return Radian<T>(static_cast<T>(std::atan2(Values[0], Values[3])) * T(2));

		return Radian<T>(static_cast<T>(std::atan2(y, x)));
	}

	Radian<T> Heading() const noexcept
	{
		return Radian<T>(static_cast<T>(std::asin(T(-2) * (Values[0] * Values[2] - Values[3] * Values[1]))));
	}

	Radian<T> Roll() const noexcept
	{
		const T x = (Values[3] * Values[3]) + (Values[0] * Values[0]) -
					(Values[1] * Values[1]) - (Values[2] * Values[2]);
		const T y = T(2) * (Values[0] * Values[1] + Values[3] * Values[2]);

		return Radian<T>(static_cast<T>(std::atan2(y, x)));
	}

	std::tuple<Radian<T>, Radian<T>, Radian<T>> Euler() const noexcept
	{
		const T sqx = Values[0] * Values[0];
		const T sqy = Values[1] * Values[1];
		const T sqz = Values[2] * Values[2];
		const T sqw = Values[3] * Values[3];

		const T r11 = sqw + sqx - sqy - sqz;
		const T r21 = T(2) * (Values[0] * Values[1] + Values[3] * Values[2]);
		const T r31 = T(2) * (Values[0] * Values[2] - Values[3] * Values[1]);
		const T r32 = T(2) * (Values[1] * Values[2] + Values[3] * Values[0]);
		const T r33 = sqw - sqx - sqy + sqz;
		const T oneish = T(1) - Epsilon<T>;

		if (std::abs(r31) > oneish)
		{
			const T r12 = T(-2) * (Values[0] * Values[1] - Values[3] * Values[2]);
			const T r13 = T(-2) * (Values[0] * Values[2] + Values[3] * Values[1]);

			return std::make_tuple
			(
				Radian<T>(T(0)),
				Radian<T>(-HalfPi<T> * r31 / std::abs(r31)),
				Radian<T>(static_cast<T>(std::atan2(r12, r31 * r13)))
			);
		}

		return std::make_tuple
		(
			Radian<T>(static_cast<T>(std::atan2(r32, r33))),
			Radian<T>(static_cast<T>(std::asin(-r31))),
			Radian<T>(static_cast<T>(std::atan2(r21, r11)))
		);
	}

	void Euler(Radian<T>& pitch, Radian<T>& heading, Radian<T>& roll) const noexcept
	{
		const auto[p, h, r] = Euler();

		pitch = std::move(p);
		heading = std::move(h);
		roll = std::move(r);
	}

	void Euler(Degree<T>& pitch, Degree<T>& heading, Degree<T>& roll) const noexcept
	{
		const auto[p, h, r] = Euler();

		pitch = p;
		heading = h;
		roll = r;
	}

public:
	constexpr T Dot(type quat) const noexcept
	{
		return (Values[0] * quat.Values[0]) +
			   (Values[1] * quat.Values[1]) +
			   (Values[2] * quat.Values[2]) +
			   (Values[3] * quat.Values[3]);
	}

	constexpr T MagnitudeSq() const noexcept
	{
		return Dot(*this);
	}

	T Magnitude() const noexcept
	{
		return { static_cast<T>(std::sqrt(MagnitudeSq())) };
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

	type& Concatenate(type quat) noexcept
	{
		const auto tx = Values[0];
		const auto ty = Values[1];
		const auto tz = Values[2];

		Values[0] = (ty * quat[2]) - (tz * quat[1]) + (Values[3] * quat[0]) + (tx * quat[3]);
		Values[1] = (tz * quat[0]) - (tx * quat[2]) + (Values[3] * quat[1]) + (ty * quat[3]);
		Values[2] = (tx * quat[1]) - (ty * quat[0]) + (Values[3] * quat[2]) + (tz * quat[3]);
		Values[3] = (Values[3] * quat[3]) - ((tx * quat[0]) + (ty * quat[1]) + (tz * quat[2]));

		return *this;
	}

	type& Conjugate() noexcept
	{
		Values[0] = -Values[0];
		Values[1] = -Values[1];
		Values[2] = -Values[2];

		return *this;
	}

	type& Invert() noexcept
	{
		return (Conjugate() /= MagnitudeSq());
	}

	type Log() const noexcept
	{
		const T a = static_cast<T>(std::acos(Values[3]));
		const T sina = static_cast<T>(std::sin(a));
		
		type result(T(0), T(0), T(0), T(0));

		if (sina > z)
		{
			result[0] = a * Values[0] / sina;
			result[1] = a * Values[1] / sina;
			result[2] = a * Values[2] / sina;
		}

		return result;
	}

	type Exp() const noexcept
	{
		const T a = static_cast<T>(
			std::sqrt((Values[0] * Values[0]) +
					  (Values[1] * Values[1]) +
					  (Values[2] * Values[2])));

		const T sina = static_cast<T>(std::sin(a));
		const T cosa = static_cast<T>(std::cos(a));
		
		type result(T(0), T(0), T(0), cosa);

		if (a > T(0))
		{
			result[0] = sina * Values[0] / a;
			result[1] = sina * Values[1] / a;
			result[2] = sina * Values[2] / a;
		}

		return result;
	}

public:
	static type NormalOf(type quat) noexcept
	{
		return type(std::move(quat)).Normalize();
	}

	static type SafeNormalOf(type quat) noexcept
	{
		return type(std::move(quat)).NormalizeSafe();
	}

	static type ConcatenationOf(type q, type r) noexcept
	{
		return type(std::move(q)).Concatenate(std::move(r));
	}

	static type ConjugateOf(type quat) noexcept
	{
		return type(std::move(quat)).Conjugate();
	}

	static type InverseOf(type quat) noexcept
	{
		return type(std::move(quat)).Invert();
	}

public:
	static auto Lerp(type from, type to, T t) noexcept
	{
		return NormalOf((std::move(from) * (T(1) - t)) + (std::move(to) * t));
	}

	static auto SlerpSR(type from, type to, T t) noexcept
	{
		type qt = std::move(to);
		auto dot = from.Dot(qt);

		// When from and to > 90 deg apart, perform spin reduction
		if (dot < T(0))
		{
			qt.Conjugate();
			dot = -dot;
		}

		if (dot > T(1) - Epsilon<T>)
			return Lerp(std::move(from), std::move(to), std::move(t));

		Radian<T> theta = static_cast<T>(acos(dot));
		Radian<T> thetaFrom = theta.Value() * (T(1) - t);
		Radian<T> thetaTo = theta.Value() * t;

		return ((std::move(from) * thetaFrom.Sin()) + (std::move(qt) * thetaTo.Sin())) / theta.Sin();
	}

	static auto Slerp(type from, type to, T t) noexcept
	{
		auto dot = from.Dot(to);

		if (dot > T(1) - Epsilon<T>)
			return Lerp(std::move(from), std::move(to), std::move(t));

		Radian<T> theta = acos(dot);
		Radian<T> thetaFrom = theta.Value() * (T(1) - t);
		Radian<T> thetaTo = theta.Value() * t;

		return ((std::move(from) * thetaFrom.Sin()) + (std::move(to) * thetaTo.Sin())) / theta.Sin();
	}

	static auto Squad(type from, type to, type a, type b, T t) noexcept
	{
		return Slerp(Slerp(std::move(from), std::move(to), t), Slerp(std::move(a), std::move(b), t), T(2) * t * (T(1) - t));
	}

public:
	void Transform(Vector<T, 3>& vec) const noexcept
	{
		_Transform(vec);
	}

	void Transform(Vector<T, 4>& vec) const noexcept
	{
		_Transform(vec);
	}

public:
	type operator - () const noexcept
	{
		return type::ConjugateOf(*this);
	}

	type operator ~ () const noexcept
	{
		return type::InverseOf(*this);
	}

public:
	#pragma region Assignment Operators

	type& operator = (const IdentityTag&) noexcept
	{
		return MakeIdentity();
	}

	type& operator *= (type quat) noexcept
	{
		return Concatenate(std::move(quat));
	}

	type& operator /= (type quat) noexcept
	{
		// Concatenate(Type::InverseOf(quat))

		const auto invMag = T(1) / quat.MagnitudeSq();

		const auto tqx = -quat.Values[0] * invMag;
		const auto tqy = -quat.Values[1] * invMag;
		const auto tqz = -quat.Values[2] * invMag;
		const auto tqw =  quat.Values[3] * invMag;

		return *this =
		{
			(Values[1] * tqz) - (Values[2] * tqy) + (Values[3] * tqx) + (Values[0] * tqw),
			(Values[2] * tqx) - (Values[0] * tqz) + (Values[3] * tqy) + (Values[1] * tqw),
			(Values[0] * tqy) - (Values[1] * tqx) + (Values[3] * tqz) + (Values[2] * tqw),
			(Values[3] * tqw) - ((Values[0] * tqx) + (Values[1] * tqy) + (Values[2] * tqz))
		};
	}

	type& operator *= (T value) noexcept
	{
		for (size_t i = 0; i < Size; ++i)
			Values[i] *= value;

		return *this;
	}

	type& operator /= (T value) noexcept
	{
		for (size_t i = 0; i < Size; ++i)
			Values[i] /= value;

		return *this;
	}

	type& operator = (const T(&values)[Size]) noexcept
	{
		for (size_t i = 0; i < Size; ++i)
			Values[i] = values[i];

		return *this;
	}

	type& operator += (const T(&values)[Size]) noexcept
	{
		for (size_t i = 0; i < Size; ++i)
			Values[i] += values[i];

		return *this;
	}

	type& operator -= (const T(&values)[Size]) noexcept
	{
		for (size_t i = 0; i < Size; ++i)
			Values[i] -= values[i];

		return *this;
	}

	type& operator = (type quat) noexcept
	{
		for (size_t i = 0; i < Size; ++i)
			Values[i] = quat[i];

		return *this;
	}

	type& operator = (type&& quat) noexcept
	{
		for (size_t i = 0; i < Size; ++i)
			Values[i] = quat[i];

		return *this;
	}

	type& operator += (type quat) noexcept
	{
		for (size_t i = 0; i < Size; ++i)
			Values[i] += quat[i];

		return *this;
	}

	type& operator -= (type quat) noexcept
	{
		for (size_t i = 0; i < Size; ++i)
			Values[i] -= quat[i];

		return *this;
	}

	#pragma endregion

public:
	#pragma region Arithmetic Operators

	type operator * (type quat) const noexcept
	{
		return type(*this) *= std::move(quat);
	}

	type operator / (type quat) const noexcept
	{
		return type(*this) /= std::move(quat);
	}

	type operator * (T value) const noexcept
	{
		return type(*this) *= std::move(value);
	}

	type operator / (T value) const noexcept
	{
		return type(*this) /= std::move(value);
	}

	type operator + (const T(&values)[Size]) const noexcept
	{
		return type(*this) += values;
	}

	type operator - (const T(&values)[Size]) const noexcept
	{
		return type(*this) -= values;
	}

	type operator + (type quat) const noexcept
	{
		return type(*this) += std::move(quat);
	}

	type operator - (type quat) const noexcept
	{
		return type(*this) -= std::move(quat);
	}

	#pragma endregion

private:
	template<size_t N>
	inline void _Transform(Vector<T, N>& vec) const noexcept
	{
		// vec.xyz = (*this * Quaternion(vec.xyz, 0) * ConjugateOf(*this)).xyz

		const auto t1 = Values[0] * T(2);
		const auto t2 = Values[1] * T(2);
		const auto t3 = Values[2] * T(2);
		const auto t4 = Values[0] * t1;
		const auto t5 = Values[1] * t2;
		const auto t6 = Values[2] * t3;
		const auto t7 = Values[0] * t2;
		const auto t8 = Values[0] * t3;
		const auto t9 = Values[1] * t3;
		const auto t10 = Values[3] * t1;
		const auto t11 = Values[3] * t2;
		const auto t12 = Values[3] * t3;
		const auto s = vec;

		vec[0] = (T(1) - (t5 + t6)) * s.x + (t7 - t12) * s.y + (t8 + t11) * s.z;
		vec[1] = (t7 + t12) * s.x + (T(1) - (t4 + t6)) * s.y + (t9 - t10) * s.z;
		vec[2] = (t8 - t11) * s.x + (t9 + t10) * s.y + (T(1) - (t4 + t5)) * s.z;
	}
};

//////////////////////////////////////////////////////////////////////////////

// Friend Operators
namespace Epic
{
	template<class T>
	inline bool operator == (const Quaternion<T>& quatA, const Quaternion<T>& quatB) noexcept
	{
		return (quatA[0] == quatB[0]) && (quatA[1] == quatB[1]) && (quatA[2] == quatB[2]) && (quatA[3] == quatB[3]);
	}

	template<class T>
	inline bool operator != (const Quaternion<T>& quatA, const Quaternion<T>& quatB) noexcept
	{
		return !(quatA == quatB);
	}

	template<class T>
	inline std::ostream& operator << (std::ostream& stream, const Quaternion<T>& quat)
	{
		stream << '['
			   << quat[0] << ", "
			   << quat[1] << ", "
			   << quat[2] << ", "
			   << quat[3]
			   << ']';

		return stream;
	}

	template<class T>
	inline std::wostream& operator << (std::wostream& stream, const Quaternion<T>& quat)
	{
		stream << L'['
			   << quat[0] << L", "
			   << quat[1] << L", "
			   << quat[2] << L", "
			   << quat[3]
			   << L']';

		return stream;
	}

	template<class T>
	inline std::istream& operator >> (std::istream& stream, Quaternion<T>& quat)
	{
		if (stream.peek() == '[')
			stream.ignore(1);

		stream >> quat[0];
		if (stream.peek() == ',') stream.ignore(1);
		stream >> quat[1];
		if (stream.peek() == ',') stream.ignore(1);
		stream >> quat[2];
		if (stream.peek() == ',') stream.ignore(1);
		stream >> quat[3];

		if (stream.peek() == ']')
			stream.ignore(1);

		return stream;
	}

	template<class T>
	inline std::wistream& operator >> (std::wistream& stream, Quaternion<T>& quat)
	{
		if (stream.peek() == L'[')
			stream.ignore(1);

		stream >> quat[0];
		if (stream.peek() == L',') stream.ignore(1);
		stream >> quat[1];
		if (stream.peek() == L',') stream.ignore(1);
		stream >> quat[2];
		if (stream.peek() == L',') stream.ignore(1);
		stream >> quat[3];

		if (stream.peek() == L']')
			stream.ignore(1);

		return stream;
	}
}

//////////////////////////////////////////////////////////////////////////////

// Vector * Quaternion operators
namespace Epic
{
	template<class T, size_t N>
	inline Vector<T, N>& Epic::Vector<T, N>::operator *= (const Quaternion<T>& quat) noexcept
	{
		assert((N == 3 || N == 4) && "This operator is only available for Vectors of size 3 or 4.");
		
		if constexpr (N == 3 || N == 4)
			quat.Transform(*this);

		return *this;
	}

	template<class T, size_t N>
	inline Vector<T, N> operator * (Vector<T, N> vec, const Quaternion<T>& quat) noexcept
	{
		assert((N == 3 || N == 4) && "This operator is only available for Vectors of size 3 or 4.");

		auto result = std::move(vec);
		
		if constexpr (N == 3 || N == 4)
			quat.Transform(result);

		return result;
	}
}