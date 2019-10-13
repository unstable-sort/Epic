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
#include <utility>

//////////////////////////////////////////////////////////////////////////////

namespace Epic::Meta
{
	/*	An implementation of the 'Detection Idiom' as seen in Marshall Clow's talk:
		C++Now 2017: Marshall Clow "The 'Detection Idiom:' A Better Way to SFINAE" */

	namespace detail
	{
		struct InvalidType
		{
			InvalidType() = delete;
			~InvalidType() = delete;
			InvalidType(const InvalidType&) = delete;
			void operator = (const InvalidType&) = delete;
		};

		template<class Default, class Void, template<class...> class Op, class... Args>
		struct Detector : std::false_type
		{
			using value_type = std::false_type;
			using type = Default;
		};

		template<class Default, template<class...> class Op, class... Args>
		struct Detector<Default, std::void_t<Op<Args...>>, Op, Args...>
		{
			using value_type = std::true_type;
			using type = Op<Args...>;
		};
	}

	template<template<class...> class Op, class... Args>
	using IsDetected = typename detail::Detector<detail::InvalidType, void, Op, Args...>::value_type;

	template<template<class...> class Op, class... Args>
	using DetectedT = typename detail::Detector<detail::InvalidType, void, Op, Args...>::type;

	template<class Default, template<class...> class Op, class... Args>
	using DetectedOrT = typename detail::Detector<Default, void, Op, Args...>::type;

	template<class Expected, template<class...> class Op, class... Args>
	using IsDetectedExact = std::is_same<Expected, DetectedT<Op, Args...>>;

	template<class To, template<class...> class Op, class... Args>
	using IsDetectedConvertible = std::is_convertible<DetectedT<Op, Args...>, To>;
}

//////////////////////////////////////////////////////////////////////////////

// IsExplicitlyConvertible
namespace Epic::Meta
{
	/*	value is true if From type is explicitly convertible to To type.
		That is, if To(From&) is valid, but an implicit conversion to To from From is not. */

	template<class From, class To>
	struct IsExplicitlyConvertible : std::conditional_t<
		std::is_constructible_v<To, From> && !std::is_convertible_v<From, To>, 
		std::true_type, 
		std::false_type>
	{ };

	template<class From, class To>
	static constexpr bool IsExplicitlyConvertible_v = IsExplicitlyConvertible<From, To>::value;
}
