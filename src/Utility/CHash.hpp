//////////////////////////////////////////////////////////////////////////////
//
//            Copyright (c) 2019 Ronnie Brohn (EpicBrownie)      
//
//                Distributed under The MIT License (MIT).
//             (See accompanying file LICENSE or copy at 
//                 https://opensource.org/licenses/MIT)
//
//           Please report any bugs, typos, or suggestions to
//             https://github.com/unstable-sort/Epic/issues
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>
#include <cstring>
#include <string>
#include <string_view>

//////////////////////////////////////////////////////////////////////////////

namespace Epic
{
	class CHash;
}

//////////////////////////////////////////////////////////////////////////////

/// CHash
class Epic::CHash
{
public:
	using hash_type = std::size_t;

public:
	static constexpr hash_type Seed{ 2166136261 };
	static constexpr hash_type Prime{ 16777619 };

private:
	hash_type m_Hash;

public:
	struct CStringWrapper
	{
		CStringWrapper() = delete;
		CStringWrapper(const CStringWrapper&) = default;
		CStringWrapper(CStringWrapper&&) = default;
		
		~CStringWrapper() = default;

		constexpr CStringWrapper(const char* cstr) : Str(cstr) { };

		CStringWrapper& operator = (const CStringWrapper&) = delete;
		CStringWrapper& operator = (CStringWrapper&&) = delete;

		const char* Str;
	};

public:
	constexpr CHash() noexcept : m_Hash{ Hash() } { }

	constexpr CHash(const CHash&) noexcept = default;
	constexpr CHash(CHash&&) noexcept = default;

	~CHash() noexcept = default;

	template<size_t N>
	constexpr CHash(const char(&cstr)[N]) noexcept
		: m_Hash{ Hash<N>(cstr) } { }

	constexpr CHash(CStringWrapper cstr) noexcept
		: m_Hash{ Hash(cstr.Str, std::strlen(cstr.Str)) } { }

	template<typename Traits>
	constexpr CHash(const std::basic_string_view<char, Traits> str) noexcept
		: m_Hash{ Hash(str.data(), str.length()) } { }

	template<typename Traits, typename Alloc>
	constexpr CHash(const std::basic_string<char, Traits, Alloc>& str) noexcept
		: m_Hash{ Hash(str.data(), str.length()) } { }

public:
	constexpr hash_type Value() const noexcept
	{
		return m_Hash;
	}

public:
	constexpr explicit operator bool() const
	{
		return m_Hash != Hash();
	}

	constexpr operator hash_type () const noexcept
	{
		return m_Hash;
	}

	constexpr CHash& operator = (const CHash&) noexcept = default;

	constexpr CHash& operator = (CHash&&) noexcept = default;

	constexpr CHash& operator = (std::nullptr_t) noexcept
	{
		m_Hash = Hash(nullptr, 0);
		return *this;
	}

	template<size_t N>
	constexpr CHash& operator = (const char(&cstr)[N]) noexcept
	{
		m_Hash = Hash(cstr);
		return *this;
	}

	constexpr CHash& operator = (CStringWrapper cstr) noexcept
	{
		m_Hash = Hash(cstr.Str, std::strlen(cstr.Str));
		return *this;
	}

	template<typename Traits>
	constexpr CHash& operator = (const std::basic_string_view<char, Traits> str) noexcept
	{
		m_Hash = Hash(str.data(), str.length());
		return *this;
	}

	template<typename Traits, typename Alloc>
	constexpr CHash& operator = (const std::basic_string<char, Traits, Alloc>& str) noexcept
	{
		m_Hash = Hash(str.data(), str.length());
		return *this;
	}

public:
	constexpr bool operator == (const CHash& other) const noexcept { return m_Hash == other.m_Hash; }
	constexpr bool operator != (const CHash& other) const noexcept { return m_Hash != other.m_Hash; }
	constexpr bool operator <= (const CHash& other) const noexcept { return m_Hash <= other.m_Hash; }
	constexpr bool operator >= (const CHash& other) const noexcept { return m_Hash >= other.m_Hash; }
	constexpr bool operator < (const CHash& other) const noexcept { return m_Hash < other.m_Hash; }
	constexpr bool operator > (const CHash& other) const noexcept { return m_Hash > other.m_Hash; }

private:
	static constexpr hash_type Hash()
	{
		return Seed;
	}

	static constexpr hash_type Hash(const char* const __restrict str, size_t length) noexcept
	{
		hash_type hash = Seed;

		for (size_t i = 0; i < length; ++i)
			hash = (hash ^ str[i]) * Prime;

		return hash;
	}

	template<size_t N, typename = std::enable_if_t<(N > 0)>>
	static constexpr hash_type Hash(const char(&str)[N]) noexcept
	{
		hash_type hash = Seed;

		for (size_t i = 0; i < N - 1; ++i)
			hash = (hash ^ str[i]) * Prime;

		return hash;
	}
};

//////////////////////////////////////////////////////////////////////////////

// UDLs
namespace Epic
{
	namespace UDL
	{
		constexpr Epic::CHash operator "" _hash(const char* literal)
		{
			return { literal };
		}

		constexpr Epic::CHash operator "" _hash(const char* literal, std::size_t length)
		{
			return { std::string_view(literal, length) };
		}
	}
}

//////////////////////////////////////////////////////////////////////////////

/// std::hash<CHash>
namespace std
{
	template<>
	struct hash<Epic::CHash>
	{
		constexpr hash() noexcept = default;

		constexpr size_t operator() (const Epic::CHash& value) const noexcept
		{
			return value.Value();
		}
	};
}
