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

// Sequence<T>
namespace Epic::Meta
{
	template<std::size_t... Items>
	using Sequence = std::integer_sequence<std::size_t, Items...>;

	template<std::size_t N>
	using MakeSequence = std::make_integer_sequence<std::size_t, N>;
}

//////////////////////////////////////////////////////////////////////////////

// ForEach - Iterate over a Sequence<T>
namespace Epic::Meta
{
	template<class Seq>
	struct ForEach;

	template<std::size_t Item>
	struct ForEach<Sequence<Item>>
	{
		template<class Function, class... Args>
		static void Call(Function fn, Args&&... args)
		{
			fn(Item, std::forward<Args>(args)...);
		}
	};

	template<std::size_t Item, std::size_t... Items>
	struct ForEach<Sequence<Item, Items...>>
	{
		template<class Function, class... Args>
		static void Call(Function fn, Args&&... args)
		{
			using Next = ForEach<Sequence<Items...>>;

			fn(Item, std::forward<Args>(args)...);

			Next::Call(fn, std::forward<Args>(args)...);
		}
	};

	template<std::size_t N>
	struct ForEachN
	{
		using Iter = ForEach<MakeSequence<N>>;

		template<class Function, class... Args>
		static void Call(Function fn, Args&&... args)
		{
			Iter::Call(fn, std::forward<Args>(args)...);
		}
	};
}

//////////////////////////////////////////////////////////////////////////////

// ForEach2 - Iterate over 2 Sequence<T> simultaneously
namespace Epic::Meta
{
	template<class LeftSeq, class RightSeq>
	struct ForEach2;

	template<std::size_t Left, std::size_t Right, std::size_t... LeftRest, std::size_t... RightRest>
	struct ForEach2<Sequence<Left, LeftRest...>, Sequence<Right, RightRest...>>
	{
		template<class Function, class... Args>
		static void Call(Function fn, Args&&... args)
		{
			using Next = ForEach2<Sequence<LeftRest...>, Sequence<RightRest...>>;

			fn(Left, Right, std::forward<Args>(args)...);

			Next::Call(fn, std::forward<Args>(args)...);
		}
	};

	template<std::size_t Left, std::size_t Right>
	struct ForEach2<Sequence<Left>, Sequence<Right>>
	{
		template<class Function, class... Args>
		static void Call(Function fn, Args&&... args)
		{
			fn(Left, Right, std::forward<Args>(args)...);
		}
	};

	template<std::size_t... LeftRest>
	struct ForEach2<Sequence<LeftRest...>, Sequence<>>
	{
		template<class Function, class... Args>
		static void Call(Function, Args&&...)
		{
			/* The left sequence is larger than the right sequence. */
		}
	};

	template<std::size_t... RightRest>
	struct ForEach2<Sequence<>, Sequence<RightRest...>>
	{
		template<class Function, class... Args>
		static void Call(Function, Args&&...)
		{
			/* The right sequence is larger than the left sequence. */
		}
	};
}

//////////////////////////////////////////////////////////////////////////////

// SequenceContains - Determine whether Query is contained within a Sequence
namespace Epic::Meta
{
	template<std::size_t Query, class Seq>
	struct SequenceContains : std::false_type { };

	template<std::size_t Query, class Seq>
	inline constexpr bool SequenceContains_v = SequenceContains<Query, Seq>::value;

	template<std::size_t Query, std::size_t... Items>
	struct SequenceContains<Query, Sequence<Items...>> 
		: std::bool_constant<((Query == Items) || ...)> { };
}

//////////////////////////////////////////////////////////////////////////////

// IsSequenceUnique - Determine whether every T within a Sequence is unique
namespace Epic::Meta
{
	template<class Seq>
	struct IsSequenceUnique : std::true_type { };

	template<class Seq>
	inline constexpr bool IsSequenceUnique_v = IsSequenceUnique<Seq>::value;

	template<std::size_t Item>
	struct IsSequenceUnique<Sequence<Item>> : std::true_type { };

	template<std::size_t Item, std::size_t... Rest>
	struct IsSequenceUnique<Sequence<Item, Rest...>>
		: std::bool_constant<(!SequenceContains_v<Item, Sequence<Rest...>> && 
							  IsSequenceUnique_v<Sequence<Rest...>>)> { };
}
