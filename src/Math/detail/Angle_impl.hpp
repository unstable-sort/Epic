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

#include "Angle_decl.h"

#include <iostream>
#include <type_traits>
#include <utility>

#include "../Constants.h"

//////////////////////////////////////////////////////////////////////////////

// Conversions
namespace Epic
{
	namespace
	{
		template<class T>
		constexpr T DegreesToRadians(const T value) noexcept
		{
			return Epic::Pi<T> * value / T(180);
		}

		template<class T>
		constexpr T RadiansToDegrees(const T value) noexcept
		{
			return T(180) * value / Epic::Pi<T>;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////

// Radian
template<class T>
class Epic::Radian
{
public:
	using type = Epic::Radian<T>;
	using value_type = T;

private:
	value_type m_Value;

public:
	static const Radian Zero;
	static const Radian QuarterCircle;
	static const Radian HalfCircle;
	static const Radian ThreeQuarterCircle;
	static const Radian Circle;

public:
	constexpr Radian() noexcept = default;
	constexpr Radian(const Radian&) noexcept = default;
	Radian(Radian&&) noexcept = default;
	~Radian() = default;

	template<class U, typename = std::enable_if_t<!std::is_same_v<U, T> && std::is_convertible_v<U, T>>>
	constexpr explicit Radian(const Radian<U>& value) noexcept
		: m_Value{ static_cast<T>(value.Value()) }
	{ }

	constexpr Radian(T value) noexcept
		: m_Value(value)
	{ }

	template<class U, typename = std::enable_if_t<!std::is_same_v<U, T> && std::is_convertible_v<U, T>>>
	constexpr explicit Radian(U value) noexcept
		: m_Value(static_cast<T>(value))
	{ }

	constexpr Radian(Degree<T> value) noexcept
		: m_Value{ Epic::DegreesToRadians(value.Value()) }
	{ }

	template<class U, typename = std::enable_if_t<!std::is_same_v<U, T> && std::is_convertible_v<U, T>>>
	constexpr explicit Radian(Degree<U> value) noexcept
		: m_Value{ Epic::DegreesToRadians(static_cast<T>(value.Value())) }
	{ }

public:
	constexpr T Value() const noexcept { return m_Value; }
	T Sin() const noexcept { return static_cast<T>(std::sin(m_Value)); }
	T Cos() const noexcept { return static_cast<T>(std::cos(m_Value)); }
	T Tan() const noexcept { return static_cast<T>(std::tan(m_Value)); }
	auto SinCos() const noexcept { return std::make_pair(Sin(), Cos()); }

public:
	Radian& Normalize() noexcept
	{
		m_Value = std::remainder(m_Value, Epic::TwoPi<T>);
		m_Value += (m_Value < T(0)) ? Epic::TwoPi<T> : T(0);

		return *this;
	}

	static Radian NormalOf(Radian value) noexcept
	{
		return value.Normalize();
	}

public:
	Radian& operator = (Radian&& value) = default;

	constexpr Radian operator - () const { return { -m_Value }; }

	constexpr Radian& operator = (Radian value) noexcept { m_Value = value.Value(); return *this; }
	constexpr Radian& operator += (Radian value) noexcept { m_Value += value.Value(); return *this; }
	constexpr Radian& operator -= (Radian value) noexcept { m_Value -= value.Value(); return *this; }
	constexpr Radian& operator *= (Radian value) noexcept { m_Value *= value.Value(); return *this; }
	constexpr Radian& operator /= (Radian value) noexcept { m_Value /= value.Value(); return *this; }

	constexpr Radian& operator = (value_type value) noexcept { m_Value = value; return *this; }
	constexpr Radian& operator += (value_type value) noexcept { m_Value += value; return *this; }
	constexpr Radian& operator -= (value_type value) noexcept { m_Value -= value; return *this; }
	constexpr Radian& operator *= (value_type value) noexcept { m_Value *= value; return *this; }
	constexpr Radian& operator /= (value_type value) noexcept { m_Value /= value; return *this; }

	constexpr Radian& operator = (Degree<T> value) noexcept
	{
		m_Value = Epic::DegreesToRadians(value.Value());
		return *this;
	}

	constexpr Radian& operator += (Degree<T> value) noexcept
	{
		m_Value += Epic::DegreesToRadians(value.Value());
		return *this;
	}

	constexpr Radian& operator -= (Degree<T> value) noexcept
	{
		m_Value -= Epic::DegreesToRadians(value.Value());
		return *this;
	}

	constexpr Radian& operator *= (Degree<T> value) noexcept
	{
		m_Value *= Epic::DegreesToRadians(value.Value());
		return *this;
	}

	constexpr Radian& operator /= (Degree<T> value) noexcept
	{
		m_Value /= Epic::DegreesToRadians(value.Value());
		return *this;
	}

public:
	constexpr Radian operator + (Radian value) const noexcept { return { m_Value + value.Value() }; }
	constexpr Radian operator - (Radian value) const noexcept { return { m_Value - value.Value() }; }
	constexpr Radian operator * (Radian value) const noexcept { return { m_Value * value.Value() }; }
	constexpr Radian operator / (Radian value) const noexcept { return { m_Value / value.Value() }; }
	 
	constexpr Radian operator + (value_type value) const noexcept { return { m_Value + value }; }
	constexpr Radian operator - (value_type value) const noexcept { return { m_Value - value }; }
	constexpr Radian operator * (value_type value) const noexcept { return { m_Value * value }; }
	constexpr Radian operator / (value_type value) const noexcept { return { m_Value / value }; }

	constexpr Radian operator + (Degree<T> value) const noexcept
	{
		return { m_Value + Epic::DegreesToRadians(value.Value()) };
	}

	constexpr Radian operator - (Degree<T> value) const noexcept
	{
		return { m_Value - Epic::DegreesToRadians(value.Value()) };
	}

	constexpr Radian operator * (Degree<T> value) const noexcept
	{
		return { m_Value * Epic::DegreesToRadians(value.Value()) };
	}

	constexpr Radian operator / (Degree<T> value) const noexcept
	{
		return { m_Value / Epic::DegreesToRadians(value.Value()) };
	}

	friend constexpr Radian operator + (value_type value, Radian rad) noexcept
	{
		return { value + rad.Value() };
	}

	friend constexpr Radian operator - (value_type value, Radian rad) noexcept
	{
		return { value - rad.Value() };
	}

	friend constexpr Radian operator * (value_type value, Radian rad) noexcept
	{
		return { value * rad.Value() };
	}

	friend constexpr Radian operator / (value_type value, Radian rad) noexcept
	{
		return { value / rad.Value() };
	}

public:
	constexpr bool operator < (value_type value) const noexcept { return m_Value < value; }
	constexpr bool operator > (value_type value) const noexcept { return m_Value > value; }
	constexpr bool operator <= (value_type value) const noexcept { return m_Value <= value; }
	constexpr bool operator >= (value_type value) const noexcept { return m_Value >= value; }
	constexpr bool operator == (value_type value) const noexcept { return m_Value == value; }
	constexpr bool operator != (value_type value) const noexcept { return m_Value != value; }

	constexpr bool operator < (Radian value) const noexcept { return m_Value < value.Value(); }
	constexpr bool operator > (Radian value) const noexcept { return m_Value > value.Value(); }
	constexpr bool operator <= (Radian value) const noexcept { return m_Value <= value.Value(); }
	constexpr bool operator >= (Radian value) const noexcept { return m_Value >= value.Value(); }
	constexpr bool operator == (Radian value) const noexcept { return m_Value == value.Value(); }
	constexpr bool operator != (Radian value) const noexcept { return m_Value != value.Value(); }
};

//////////////////////////////////////////////////////////////////////////////

// Degree
template<class T>
class Epic::Degree
{
public:
	using type = Epic::Degree<T>;
	using value_type = T;

private:
	value_type m_Value;

public:
	static const Degree Zero;
	static const Degree QuarterCircle;
	static const Degree HalfCircle;
	static const Degree ThreeQuarterCircle;
	static const Degree Circle;

public:
	constexpr Degree() noexcept = default;
	constexpr Degree(const Degree&) noexcept = default;
	Degree(Degree&&) noexcept = default;
	~Degree() = default;

	template<class U, typename = std::enable_if_t<!std::is_same_v<U, T> && std::is_convertible_v<U, T>>>
	constexpr explicit Degree(const Degree<U>& value) noexcept
		: m_Value{ static_cast<T>(value.Value()) }
	{ }

	constexpr Degree(T value) noexcept
		: m_Value(value)
	{ }

	template<class U, typename = std::enable_if_t<!std::is_same_v<U, T> && std::is_convertible_v<U, T>>>
	constexpr explicit Degree(U value) noexcept
		: m_Value(static_cast<T>(value))
	{ }

	constexpr Degree(Radian<T> value) noexcept
		: m_Value{ Epic::RadiansToDegrees(value.Value()) }
	{ }

	template<class U, typename = std::enable_if_t<!std::is_same_v<U, T> && std::is_convertible_v<U, T>>>
	constexpr explicit Degree(Radian<U> value) noexcept
		: m_Value{ static_cast<T>(Epic::RadiansToDegrees(value.Value())) }
	{ }

public:
	constexpr T Value() const noexcept { return m_Value; }
	T Sin() const noexcept { return static_cast<value_type>(std::sin(Epic::DegreesToRadians(m_Value))); }
	T Cos() const noexcept { return static_cast<value_type>(std::cos(Epic::DegreesToRadians(m_Value))); }
	T Tan() const noexcept { return static_cast<value_type>(std::tan(Epic::DegreesToRadians(m_Value))); }
	auto SinCos() const noexcept { return std::make_pair(Sin(), Cos()); }

public:
	Degree& Normalize() noexcept
	{
		m_Value = std::remainder(m_Value, T(360));
		m_Value += (m_Value < T(0)) ? T(360) : T(0);

		return *this;
	}

	static Degree NormalOf(Degree value) noexcept
	{
		return value.Normalize();
	}

public:
	Degree& operator = (Degree&& value) = default;

	constexpr Degree operator - () const { return { -m_Value }; }

	constexpr Degree& operator = (Degree value) noexcept { m_Value = value.Value(); return *this; }
	constexpr Degree& operator += (Degree value) noexcept { m_Value += value.Value(); return *this; }
	constexpr Degree& operator -= (Degree value) noexcept { m_Value -= value.Value(); return *this; }
	constexpr Degree& operator *= (Degree value) noexcept { m_Value *= value.Value(); return *this; }
	constexpr Degree& operator /= (Degree value) noexcept { m_Value /= value.Value(); return *this; }

	constexpr Degree& operator = (value_type value) noexcept { m_Value = value; return *this; }
	constexpr Degree& operator += (value_type value) noexcept { m_Value += value; return *this; }
	constexpr Degree& operator -= (value_type value) noexcept { m_Value -= value; return *this; }
	constexpr Degree& operator *= (value_type value) noexcept { m_Value *= value; return *this; }
	constexpr Degree& operator /= (value_type value) noexcept { m_Value /= value; return *this; }

	constexpr Degree& operator = (Radian<T> value) noexcept
	{
		m_Value = Epic::RadiansToDegrees(value.Value());
		return *this;
	}

	constexpr Degree& operator += (Radian<T> value) noexcept
	{
		m_Value += Epic::RadiansToDegrees(value.Value());
		return *this;
	}

	constexpr Degree& operator -= (Radian<T> value) noexcept
	{
		m_Value -= Epic::RadiansToDegrees(value.Value());
		return *this;
	}

	constexpr Degree& operator *= (Radian<T> value) noexcept
	{
		m_Value *= Epic::RadiansToDegrees(value.Value());
		return *this;
	}

	constexpr Degree& operator /= (Radian<T> value) noexcept
	{
		m_Value /= Epic::RadiansToDegrees(value.Value());
		return *this;
	}

public:
	constexpr Degree operator + (Degree value) const noexcept { return { m_Value + value.Value() }; }
	constexpr Degree operator - (Degree value) const noexcept { return { m_Value - value.Value() }; }
	constexpr Degree operator * (Degree value) const noexcept { return { m_Value * value.Value() }; }
	constexpr Degree operator / (Degree value) const noexcept { return { m_Value / value.Value() }; }

	constexpr Degree operator + (value_type value) const noexcept { return { m_Value + value }; }
	constexpr Degree operator - (value_type value) const noexcept { return { m_Value - value }; }
	constexpr Degree operator * (value_type value) const noexcept { return { m_Value * value }; }
	constexpr Degree operator / (value_type value) const noexcept { return { m_Value / value }; }

	constexpr Degree operator + (Radian<T> value) const noexcept
	{
		return { m_Value + Epic::RadiansToDegrees(value.Value()) };
	}

	constexpr Degree operator - (Radian<T> value) const noexcept
	{
		return { m_Value - Epic::RadiansToDegrees(value.Value()) };
	}

	constexpr Degree operator * (Radian<T> value) const noexcept
	{
		return { m_Value * Epic::RadiansToDegrees(value.Value()) };
	}

	constexpr Degree operator / (Radian<T> value) const noexcept
	{
		return { m_Value / Epic::RadiansToDegrees(value.Value()) };
	}

	friend constexpr Degree operator + (value_type value, Degree deg) noexcept
	{
		return { value + deg.Value() };
	}

	friend constexpr Degree operator - (value_type value, Degree deg) noexcept
	{
		return { value - deg.Value() };
	}

	friend constexpr Degree operator * (value_type value, Degree deg) noexcept
	{
		return { value * deg.Value() };
	}

	friend constexpr Degree operator / (value_type value, Degree deg) noexcept
	{
		return { value / deg.Value() };
	}

public:
	constexpr bool operator < (value_type value) const noexcept { return m_Value < value; }
	constexpr bool operator > (value_type value) const noexcept { return m_Value > value; }
	constexpr bool operator <= (value_type value) const noexcept { return m_Value <= value; }
	constexpr bool operator >= (value_type value) const noexcept { return m_Value >= value; }
	constexpr bool operator == (value_type value) const noexcept { return m_Value == value; }
	constexpr bool operator != (value_type value) const noexcept { return m_Value != value; }

	constexpr bool operator < (Degree value) const noexcept { return m_Value < value.Value(); }
	constexpr bool operator > (Degree value) const noexcept { return m_Value > value.Value(); }
	constexpr bool operator <= (Degree value) const noexcept { return m_Value <= value.Value(); }
	constexpr bool operator >= (Degree value) const noexcept { return m_Value >= value.Value(); }
	constexpr bool operator == (Degree value) const noexcept { return m_Value == value.Value(); }
	constexpr bool operator != (Degree value) const noexcept { return m_Value != value.Value(); }
};

//////////////////////////////////////////////////////////////////////////////

// Static Initializers
namespace Epic
{
	template<class T>
	const Radian<T> Radian<T>::Zero = T(0);

	template<class T>
	const Radian<T> Radian<T>::QuarterCircle = Epic::HalfPi<T>;

	template<class T>
	const Radian<T> Radian<T>::HalfCircle = Epic::Pi<T>;

	template<class T>
	const Radian<T> Radian<T>::ThreeQuarterCircle = Epic::Pi<T> + Epic::HalfPi<T>;

	template<class T>
	const Radian<T> Radian<T>::Circle = Epic::TwoPi<T>;

	template<class T>
	const Degree<T> Degree<T>::Zero = T(0);

	template<class T>
	const Degree<T> Degree<T>::QuarterCircle = T(90);

	template<class T>
	const Degree<T> Degree<T>::HalfCircle = T(180);

	template<class T>
	const Degree<T> Degree<T>::ThreeQuarterCircle = T(270);

	template<class T>
	const Degree<T> Degree<T>::Circle = T(360);
}

//////////////////////////////////////////////////////////////////////////////

// Stream Operators
namespace Epic
{
	template<class Char, class Traits, class T>
	inline std::basic_ostream<Char, Traits>& operator << (std::basic_ostream<Char, Traits>& out, Epic::Radian<T> value)
	{
		return (out << value.Value());
	}

	template<class Char, class Traits, class T>
	inline std::basic_istream<Char, Traits>& operator >> (std::basic_istream<Char, Traits>& in, Epic::Radian<T>& value)
	{
		T a;
		in >> a;
		value = a;

		return in;
	}

	template<class Char, class Traits, class T>
	inline std::basic_ostream<Char, Traits>& operator << (std::basic_ostream<Char, Traits>& out, Epic::Degree<T> value)
	{
		return (out << value.Value());
	}

	template<class Char, class Traits, class T>
	inline std::basic_istream<Char, Traits>& operator >> (std::basic_istream<Char, Traits>& in, Epic::Degree<T>& value)
	{
		T a;
		in >> a;
		value = a;

		return in;
	}
}

//////////////////////////////////////////////////////////////////////////////

// UDLs
namespace Epic
{
	namespace UDL
	{
		constexpr Epic::Radian<float> operator "" _rad(long double value)
		{
			return{ float(value) };
		}

		constexpr Epic::Radian<double> operator "" _radd(long double value)
		{
			return{ double(value) };
		}

		constexpr Epic::Degree<float> operator "" _deg(unsigned long long value)
		{
			return{ float(value) };
		}

		constexpr Epic::Degree<float> operator "" _deg(long double value)
		{
			return{ float(value) };
		}

		constexpr Epic::Degree<double> operator "" _degd(unsigned long long value)
		{
			return{ double(value) };
		}

		constexpr Epic::Degree<double> operator "" _degd(long double value)
		{
			return{ double(value) };
		}
	}
}
