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

#include <functional>

#include "Sequence.hpp"

//////////////////////////////////////////////////////////////////////////////

// VariadicPlaceholder
namespace Epic::Meta
{
	template<int>
	struct VariadicPlaceholder {};
}

//////////////////////////////////////////////////////////////////////////////

// std::is_placeholder<VariadicPlaceholder>
namespace std 
{
	template<int N>
	struct is_placeholder<Epic::Meta::VariadicPlaceholder<N>>
		: integral_constant<int, N + 1>
	{ 
	};
}

//////////////////////////////////////////////////////////////////////////////

// bind
namespace Epic::Meta
{
	namespace
	{
		template<class R, class TClass, class... Args, size_t... Is, class... Args2>
		auto bind(std::index_sequence<Is...>, R(TClass::*pMember)(Args...), Args2&&... args) 
		{
			return std::bind(pMember, std::forward<Args2>(args)..., VariadicPlaceholder<Is>{}...);
		}

		template<class R, class TClass, class... Args, class... Args2>
		auto bind(R(TClass::*pMember)(Args...), Args2&&... args) 
		{
			return Epic::Meta::bind(MakeSequence<sizeof...(Args) - sizeof...(Args2) + 1>{}, pMember, std::forward<Args2>(args)...);
		}

		template<class R, class TClass, class... Args, size_t... Is, class... Args2>
		auto bind(std::index_sequence<Is...>, R(TClass::*pMember)(Args...) const, Args2&&... args)
		{
			return std::bind(pMember, std::forward<Args2>(args)..., VariadicPlaceholder<Is>{}...);
		}

		template<class R, class TClass, class... Args, class... Args2>
		auto bind(R(TClass::*pMember)(Args...) const, Args2&&... args)
		{
			return Epic::Meta::bind(MakeSequence<sizeof...(Args) - sizeof...(Args2) + 1>{}, pMember, std::forward<Args2>(args)...);
		}
	}
}