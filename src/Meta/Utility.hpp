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

#include "List.hpp"

//////////////////////////////////////////////////////////////////////////////

// Literal
namespace Epic::Meta
{
	template<class T, T N>
	using Literal = std::integral_constant<T, N>;
}

//////////////////////////////////////////////////////////////////////////////

// IsVariadicTypeOf
namespace Epic::Meta
{
	template<class T, class... Args>
	inline constexpr bool IsVariadicTypeOf = std::is_same_v<List<T>, List<std::decay_t<Args>...>>;
}

//////////////////////////////////////////////////////////////////////////////

// VariadicContains
namespace Epic::Meta
{
	template<class T, class... Ts>
	struct VariadicContains : std::bool_constant<(std::is_same_v<T, Ts> || ...)> { };
}

//////////////////////////////////////////////////////////////////////////////

// GenIndexList
namespace Epic::Meta
{
	// GenIndexList<I> - Generates a List<> containing Literal<size_t> types from 0..I.
	template<size_t I>
	struct GenIndexList
	{
		using type = typename Concat<typename GenIndexList<I - 1>::type, List<Literal<size_t, I>>>::type;
	};

	template<> 
	struct GenIndexList<0>
	{
		using type = List<Literal<size_t, 0>>;
	};
	
	// IndexListFor<Ts...> - Invokes GenIndexList on the sizeof... Ts
	template<class... Ts>
	using IndexListFor = typename GenIndexList<sizeof...(Ts) - 1>::type;
}

//////////////////////////////////////////////////////////////////////////////

// DebugSwitch
namespace Epic::Meta
{
	template<class DebugType, class ReleaseType>
	struct DebugSwitch;

#ifdef NDEBUG
	template<class, class R>
	struct DebugSwitch
	{
		using type = R;
	};
#else
	template<class D, class> 
	struct DebugSwitch
	{
		using type = D;
	};
#endif
}

//////////////////////////////////////////////////////////////////////////////

// IsPowerOf2 / FloorPowerOf2 / CeilPowerOf2
namespace Epic::Meta
{
	template<size_t N>
	struct IsPowerOf2 : std::conditional_t<!(N & (N - 1)), std::true_type, std::false_type> { };

	template<> 
	struct IsPowerOf2<0> : std::false_type { };

	template<size_t N>
	struct FloorPowerOf2 : Literal<size_t, FloorPowerOf2<N / 2>::value * 2> { };

	template<> 
	struct FloorPowerOf2<1> : Literal<size_t, 1> { };
	
	template<> 
	struct FloorPowerOf2<0> : Literal<size_t, 0> { };

	template<size_t N>
	struct CeilPowerOf2 : Literal<size_t, IsPowerOf2<N>::value ? N : FloorPowerOf2<N>::value * 2> { };

	template<> 
	struct CeilPowerOf2<0> : Literal<size_t, 1> { };
}
