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
	template<class T, T... Items>
	using Sequence = std::integer_sequence<T, Items...>;

	template<class T, T N>
	using MakeSequence = std::make_integer_sequence<T, N>;
}

//////////////////////////////////////////////////////////////////////////////

// ForEach - Iterate over a Sequence<T>
namespace Epic::Meta
{
	template<class Seq>
	struct ForEach;

	template<class T, T Item>
	struct ForEach<Sequence<T, Item>>
	{
		template<class Function, class... Args>
		static void Call(Function fn, Args&&... args)
		{
			fn(Item, std::forward<Args>(args)...);
		}
	};

	template<class T, T Item, T... Items>
	struct ForEach<Sequence<T, Item, Items...>>
	{
		template<class Function, class... Args>
		static void Call(Function fn, Args&&... args)
		{
			using Next = ForEach<Sequence<T, Items...>>;

			fn(Item, std::forward<Args>(args)...);

			Next::Call(fn, std::forward<Args>(args)...);
		}
	};

	template<size_t N>
	struct ForEachN
	{
		using Iter = ForEach<MakeSequence<size_t, N>>;

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

	template<class T, T Left, T Right, T... LeftRest, T... RightRest>
	struct ForEach2<Sequence<T, Left, LeftRest...>, Sequence<T, Right, RightRest...>>
	{
		template<class Function, class... Args>
		static void Call(Function fn, Args&&... args)
		{
			using Next = ForEach2<Sequence<T, LeftRest...>, Sequence<T, RightRest...>>;

			fn(Left, Right, std::forward<Args>(args)...);

			Next::Call(fn, std::forward<Args>(args)...);
		}
	};

	template<class T, T Left, T Right>
	struct ForEach2<Sequence<T, Left>, Sequence<T, Right>>
	{
		template<class Function, class... Args>
		static void Call(Function fn, Args&&... args)
		{
			fn(Left, Right, std::forward<Args>(args)...);
		}
	};

	template<class T, T... LeftRest>
	struct ForEach2<Sequence<T, LeftRest...>, Sequence<T>>
	{
		template<class Function, class... Args>
		static void Call(Function, Args&&...)
		{
			/* The left sequence is larger than the right sequence. */
		}
	};

	template<class T, T... RightRest>
	struct ForEach2<Sequence<T>, Sequence<T, RightRest...>>
	{
		template<class Function, class... Args>
		static void Call(Function, Args&&...)
		{
			/* The right sequence is larger than the left sequence. */
		}
	};
}

//////////////////////////////////////////////////////////////////////////////

// SequenceContains - Determine whether Query is contained within a Sequence<T>
namespace Epic::Meta
{
	template<class T, T Query, class Seq>
	struct SequenceContains : std::false_type { };

	template<class T, T Query, class Seq>
	inline constexpr bool SequenceContains_v = SequenceContains<T, Query, Seq>::value;

	template<class T, T Query, T... Items>
	struct SequenceContains<T, Query, Sequence<T, Items...>> 
		: std::bool_constant<((Query == Items) || ...)> { };
}

//////////////////////////////////////////////////////////////////////////////

// IsSequenceUnique - Determine whether every T within a Sequence<T> is unique
namespace Epic::Meta
{
	template<class Seq>
	struct IsSequenceUnique : std::true_type { };

	template<class Seq>
	inline constexpr bool IsSequenceUnique_v = IsSequenceUnique<Seq>::value;

	template<class T, T Item>
	struct IsSequenceUnique<Sequence<T, Item>> : std::true_type { };

	template<class T, T Item, T... Rest>
	struct IsSequenceUnique<Sequence<T, Item, Rest...>>
		: std::bool_constant<(!SequenceContains_v<T, Item, Sequence<T, Rest...>> && 
							  IsSequenceUnique_v<Sequence<T, Rest...>>)> { };
}
