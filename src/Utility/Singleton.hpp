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

#include <type_traits>

//////////////////////////////////////////////////////////////////////////////

namespace Epic
{
	struct SingletonInstanceTag;

	template<class T, class Tag = SingletonInstanceTag>
	class Singleton;

	namespace detail
	{
		template<class T, class Tag>
		struct SingletonCreator;
	}
}

//////////////////////////////////////////////////////////////////////////////

// SingletonCreator
template<class T, class Tag>
struct Epic::detail::SingletonCreator
{
	SingletonCreator() noexcept { Singleton<T, Tag>::Instance(); }

	inline void DoNothing() const noexcept { }
};

//////////////////////////////////////////////////////////////////////////////

// Singleton
template<class T, class Tag>
class Epic::Singleton
{
public:
	using singleton_type = std::decay_t<T>;
	using tag_type = Tag;

	static_assert(std::is_class<singleton_type>::value, "Singleton type must be a class Type.");
	static_assert(std::is_default_constructible<singleton_type>::value, "Singleton type must be default constructible.");

private:
	static detail::SingletonCreator<T, Tag> s_Creator;

public:
	Singleton() = delete;
	Singleton(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;

	~Singleton() = default;

	Singleton& operator = (const Singleton&) = delete;
	Singleton& operator = (Singleton&&) = delete;

public:
	static singleton_type& Instance() noexcept
	{
		// The singleton instance
		// C++ guarantees that s_Instance is created in a thread-safe manner
		static singleton_type s_Instance;

		// Calling DoNothing forcibly instantiates
		// and initializes the object prior to main()
		s_Creator.DoNothing();

		return s_Instance;
	}
};

//////////////////////////////////////////////////////////////////////////////

// Static Initialization
template<class T, class Tag>
Epic::detail::SingletonCreator<T, Tag> Epic::Singleton<T, Tag>::s_Creator;
