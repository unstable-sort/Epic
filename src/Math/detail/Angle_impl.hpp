//////////////////////////////////////////////////////////////////////////////
//
//            Copyright (c) 2019 Ronnie Brohn (EpicBrownie)      
//
//                Distributed under The MIT License (MIT).
//             (See accompanying file License.txt or copy at 
//                 https://opensource.org/licenses/MIT)
//
//           Please report any bugs, typos, or suggestions to
//              https://github.com/epicbrownie/Epic2/issues
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
	static const Radian<T> Zero;
	static const Radian<T> QuarterCircle;
	static const Radian<T> HalfCircle;
	static const Radian<T> ThreeQuarterCircle;
	static const Radian<T> Circle;

public:
	constexpr Radian() noexcept = default;
	constexpr Radian(const Radian<T>&) noexcept = default;
	Radian(Radian<T>&&) noexcept = default;
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
	Radian<T>& Normalize(T min = T(0)) noexcept;

	static Radian<T> NormalOf(Radian<T> value, T min = T(0)) noexcept
	{
		return value.Normalize(min);
	}

public:
	Radian<T>& operator = (Radian<T>&& value) = default;

	constexpr Radian<T> operator - () const { return { -m_Value }; }

	constexpr explicit operator Degree<T>() const { return Degree<T>(RadiansToDegrees(m_Value)); }

	constexpr Radian<T>& operator = (Radian<T> value) noexcept { m_Value = value.Value(); return *this; }
	constexpr Radian<T>& operator += (Radian<T> value) noexcept { m_Value += value.Value(); return *this; }
	constexpr Radian<T>& operator -= (Radian<T> value) noexcept { m_Value -= value.Value(); return *this; }
	constexpr Radian<T>& operator *= (Radian<T> value) noexcept { m_Value *= value.Value(); return *this; }
	constexpr Radian<T>& operator /= (Radian<T> value) noexcept { m_Value /= value.Value(); return *this; }

	constexpr Radian<T>& operator = (value_type value) noexcept { m_Value = value; return *this; }
	constexpr Radian<T>& operator += (value_type value) noexcept { m_Value += value; return *this; }
	constexpr Radian<T>& operator -= (value_type value) noexcept { m_Value -= value; return *this; }
	constexpr Radian<T>& operator *= (value_type value) noexcept { m_Value *= value; return *this; }
	constexpr Radian<T>& operator /= (value_type value) noexcept { m_Value /= value; return *this; }

	constexpr Radian<T>& operator = (Degree<T> value) noexcept
	{
		m_Value = Epic::DegreesToRadians(value.Value());
		return *this;
	}

	constexpr Radian<T>& operator += (Degree<T> value) noexcept
	{
		m_Value += Epic::DegreesToRadians(value.Value());
		return *this;
	}

	constexpr Radian<T>& operator -= (Degree<T> value) noexcept
	{
		m_Value -= Epic::DegreesToRadians(value.Value());
		return *this;
	}

	constexpr Radian<T>& operator *= (Degree<T> value) noexcept
	{
		m_Value *= Epic::DegreesToRadians(value.Value());
		return *this;
	}

	constexpr Radian<T>& operator /= (Degree<T> value) noexcept
	{
		m_Value /= Epic::DegreesToRadians(value.Value());
		return *this;
	}

public:
	constexpr Radian<T> operator + (Radian<T> value) const noexcept { return { m_Value + value.Value() }; }
	constexpr Radian<T> operator - (Radian<T> value) const noexcept { return { m_Value - value.Value() }; }
	constexpr Radian<T> operator * (Radian<T> value) const noexcept { return { m_Value * value.Value() }; }
	constexpr Radian<T> operator / (Radian<T> value) const noexcept { return { m_Value / value.Value() }; }
	 
	constexpr Radian<T> operator + (value_type value) const noexcept { return { m_Value + value }; }
	constexpr Radian<T> operator - (value_type value) const noexcept { return { m_Value - value }; }
	constexpr Radian<T> operator * (value_type value) const noexcept { return { m_Value * value }; }
	constexpr Radian<T> operator / (value_type value) const noexcept { return { m_Value / value }; }

	constexpr Radian<T> operator + (Degree<T> value) const noexcept
	{
		return { m_Value + Epic::DegreesToRadians(value.Value()) };
	}

	constexpr Radian<T> operator - (Degree<T> value) const noexcept
	{
		return { m_Value - Epic::DegreesToRadians(value.Value()) };
	}

	constexpr Radian<T> operator * (Degree<T> value) const noexcept
	{
		return { m_Value * Epic::DegreesToRadians(value.Value()) };
	}

	constexpr Radian<T> operator / (Degree<T> value) const noexcept
	{
		return { m_Value / Epic::DegreesToRadians(value.Value()) };
	}

	friend constexpr Radian<T> operator + (value_type value, Radian<T> rad) noexcept
	{
		return { value + rad.Value() };
	}

	friend constexpr Radian<T> operator - (value_type value, Radian<T> rad) noexcept
	{
		return { value - rad.Value() };
	}

	friend constexpr Radian<T> operator * (value_type value, Radian<T> rad) noexcept
	{
		return { value * rad.Value() };
	}

	friend constexpr Radian<T> operator / (value_type value, Radian<T> rad) noexcept
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

	constexpr bool operator < (Radian<T> value) const noexcept { return m_Value < value.Value(); }
	constexpr bool operator > (Radian<T> value) const noexcept { return m_Value > value.Value(); }
	constexpr bool operator <= (Radian<T> value) const noexcept { return m_Value <= value.Value(); }
	constexpr bool operator >= (Radian<T> value) const noexcept { return m_Value >= value.Value(); }
	constexpr bool operator == (Radian<T> value) const noexcept { return m_Value == value.Value(); }
	constexpr bool operator != (Radian<T> value) const noexcept { return m_Value != value.Value(); }
};

//////////////////////////////////////////////////////////////////////////////

// Radian Implementation
template<class T>
Epic::Radian<T>& Epic::Radian<T>::Normalize(T min) noexcept
{
	m_Value = std::remainder(m_Value + min, Epic::TwoPi<T>);
	m_Value -= (m_Value < T(0)) ? min - Epic::TwoPi<T> : min;

	return *this;
}

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
	static const Degree<T> Zero;
	static const Degree<T> QuarterCircle;
	static const Degree<T> HalfCircle;
	static const Degree<T> ThreeQuarterCircle;
	static const Degree<T> Circle;

public:
	constexpr Degree() noexcept = default;
	constexpr Degree(const Degree<T>&) noexcept = default;
	Degree(Degree<T>&&) noexcept = default;
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
		: m_Value{ Epic::RadiansToDegrees(static_cast<T>(value.Value())) }
	{ }

public:
	constexpr T Value() const noexcept { return m_Value; }
	T Sin() const noexcept { return static_cast<value_type>(std::sin(m_Value)); }
	T Cos() const noexcept { return static_cast<value_type>(std::cos(m_Value)); }
	T Tan() const noexcept { return static_cast<value_type>(std::tan(m_Value)); }
	auto SinCos() const noexcept { return std::make_pair(Sin(), Cos()); }

public:
	Degree<T>& Normalize(T min = T(0)) noexcept;

	static Degree<T> NormalOf(Degree<T> value, T min = T(0)) noexcept
	{
		return value.Normalize(min);
	}

public:
	Degree<T>& operator = (Degree<T>&& value) = default;

	constexpr Degree<T> operator - () const { return { -m_Value }; }

	constexpr explicit operator Radian<T>() const { return Radian<T>(Epic::DegreesToRadians(m_Value)); }

	constexpr Degree<T>& operator = (Degree<T> value) noexcept { m_Value = value.Value(); return *this; }
	constexpr Degree<T>& operator += (Degree<T> value) noexcept { m_Value += value.Value(); return *this; }
	constexpr Degree<T>& operator -= (Degree<T> value) noexcept { m_Value -= value.Value(); return *this; }
	constexpr Degree<T>& operator *= (Degree<T> value) noexcept { m_Value *= value.Value(); return *this; }
	constexpr Degree<T>& operator /= (Degree<T> value) noexcept { m_Value /= value.Value(); return *this; }

	constexpr Degree<T>& operator = (value_type value) noexcept { m_Value = value; return *this; }
	constexpr Degree<T>& operator += (value_type value) noexcept { m_Value += value; return *this; }
	constexpr Degree<T>& operator -= (value_type value) noexcept { m_Value -= value; return *this; }
	constexpr Degree<T>& operator *= (value_type value) noexcept { m_Value *= value; return *this; }
	constexpr Degree<T>& operator /= (value_type value) noexcept { m_Value /= value; return *this; }

	constexpr Degree<T>& operator = (Radian<T> value) noexcept
	{
		m_Value = Epic::RadiansToDegrees(value.Value());
		return *this;
	}

	constexpr Degree<T>& operator += (Radian<T> value) noexcept
	{
		m_Value += Epic::RadiansToDegrees(value.Value());
		return *this;
	}

	constexpr Degree<T>& operator -= (Radian<T> value) noexcept
	{
		m_Value -= Epic::RadiansToDegrees(value.Value());
		return *this;
	}

	constexpr Degree<T>& operator *= (Radian<T> value) noexcept
	{
		m_Value *= Epic::RadiansToDegrees(value.Value());
		return *this;
	}

	constexpr Degree<T>& operator /= (Radian<T> value) noexcept
	{
		m_Value /= Epic::RadiansToDegrees(value.Value());
		return *this;
	}

public:
	constexpr Degree<T> operator + (Degree<T> value) const noexcept { return { m_Value + value.Value() }; }
	constexpr Degree<T> operator - (Degree<T> value) const noexcept { return { m_Value - value.Value() }; }
	constexpr Degree<T> operator * (Degree<T> value) const noexcept { return { m_Value * value.Value() }; }
	constexpr Degree<T> operator / (Degree<T> value) const noexcept { return { m_Value / value.Value() }; }

	constexpr Degree<T> operator + (value_type value) const noexcept { return { m_Value + value }; }
	constexpr Degree<T> operator - (value_type value) const noexcept { return { m_Value - value }; }
	constexpr Degree<T> operator * (value_type value) const noexcept { return { m_Value * value }; }
	constexpr Degree<T> operator / (value_type value) const noexcept { return { m_Value / value }; }

	constexpr Degree<T> operator + (Radian<T> value) const noexcept
	{
		return { m_Value + Epic::RadiansToDegrees(value.Value()) };
	}

	constexpr Degree<T> operator - (Radian<T> value) const noexcept
	{
		return { m_Value - Epic::RadiansToDegrees(value.Value()) };
	}

	constexpr Degree<T> operator * (Radian<T> value) const noexcept
	{
		return { m_Value * Epic::RadiansToDegrees(value.Value()) };
	}

	constexpr Degree<T> operator / (Radian<T> value) const noexcept
	{
		return { m_Value / Epic::RadiansToDegrees(value.Value()) };
	}

	friend constexpr Degree<T> operator + (value_type value, Degree<T> deg) noexcept
	{
		return { value + deg.Value() };
	}

	friend constexpr Degree<T> operator - (value_type value, Degree<T> deg) noexcept
	{
		return { value - deg.Value() };
	}

	friend constexpr Degree<T> operator * (value_type value, Degree<T> deg) noexcept
	{
		return { value * deg.Value() };
	}

	friend constexpr Degree<T> operator / (value_type value, Degree<T> deg) noexcept
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

	constexpr bool operator < (Degree<T> value) const noexcept { return m_Value < value.Value(); }
	constexpr bool operator > (Degree<T> value) const noexcept { return m_Value > value.Value(); }
	constexpr bool operator <= (Degree<T> value) const noexcept { return m_Value <= value.Value(); }
	constexpr bool operator >= (Degree<T> value) const noexcept { return m_Value >= value.Value(); }
	constexpr bool operator == (Degree<T> value) const noexcept { return m_Value == value.Value(); }
	constexpr bool operator != (Degree<T> value) const noexcept { return m_Value != value.Value(); }
};

//////////////////////////////////////////////////////////////////////////////

// Degree Implementation
template<class T>
Epic::Degree<T>& Epic::Degree<T>::Normalize(T min) noexcept
{
	m_Value = std::remainder(m_Value + min, Epic::TwoPi<T>);
	m_Value -= (m_Value < T(0)) ? min - Epic::TwoPi<T> : min;

	return *this;
}

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
	const Radian<T> Radian<T>::ThreeQuarterCircle = Epic::Pi<T> +Epic::HalfPi<T>;

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
