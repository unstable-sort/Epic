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

#include <type_traits>
#include <tuple>

//////////////////////////////////////////////////////////////////////////////

namespace Epic::Meta
{
	template<class...> 
	struct List;
}

//////////////////////////////////////////////////////////////////////////////

// ListToTuple<> - Convert List to std::tuple
namespace Epic::Meta
{
	template<class ListType> 
	struct ListToTuple;

	template<class... Ts>
	struct ListToTuple<List<Ts...>>
	{
		using type = std::tuple<Ts...>;
	};
}

//////////////////////////////////////////////////////////////////////////////

// Concat<> - List Concatenation
namespace Epic::Meta
{
	template<class... Lists> 
	struct Concat;

	template<>
	struct Concat<>
	{
		using type = List<>;
	};

	template<class... Ts>
	struct Concat<List<Ts...>>
	{
		using type = List<Ts...>;
	};

	template<class... Ts, class... Us>
	struct Concat<List<Ts...>, List<Us...>>
	{
		using type = List<Ts..., Us...>;
	};

	template<class... Ts, class... Us, class... Rest>
	struct Concat<List<Ts...>, List<Us...>, Rest...>
	{
		using type = typename Concat<List<Ts..., Us...>, Rest...>::type;
	};
}

//////////////////////////////////////////////////////////////////////////////

// Filter<> - List Filtering
namespace Epic::Meta
{
	namespace detail
	{
		template<template<class> class Pred, class T>
		using FilterHelper = std::conditional_t<Pred<T>::value, List<T>, List<>>;
	}

	template<template<class> class Pred, class... Ts>
	using Filter = typename Concat<detail::FilterHelper<Pred, Ts>...>::type;
}
