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

#include <array>
#include <type_traits>

#include "Vector_decl.h"
#include "VectorSwizzler_decl.h"

//////////////////////////////////////////////////////////////////////////////

namespace Epic::detail
{
	// SpanSizeOf
	template<class T>
	struct SpanSizeOf
		: std::integral_constant<size_t, 1> { };

	// SpanSizeOf<Epic::Vector>
	template<class T, size_t N>
	struct SpanSizeOf<Epic::Vector<T, N>>
		: std::integral_constant<size_t, N> { };

	// SpanSizeOf<Epic::VectorSwizzler>
	template<class T, size_t N, size_t... Indices>
	struct SpanSizeOf<Epic::detail::VectorSwizzler<T, N, Indices...>>
		: std::integral_constant<size_t, (sizeof...(Indices))> { };

	// SpanSizeOf<T[N]>
	template<class T, size_t N>
	struct SpanSizeOf<T[N]>
		: std::integral_constant<size_t, N> { };

	// SpanSizeOf<std::array>
	template<class T, size_t N>
	struct SpanSizeOf<std::array<T, N>>
		: std::integral_constant<size_t, N> { };
}

//////////////////////////////////////////////////////////////////////////////

namespace Epic::detail
{
	// Span<...>
	template<class... Ts>
	struct Span : std::integral_constant<size_t, 0> { };

	// Span_v<...>
	template<class... Ts>
	inline constexpr size_t Span_v = Span<Ts...>::value;

	// Span<T, ...>
	template<class T, class... Ts>
	struct Span<T, Ts...>
		: std::integral_constant<size_t, (
			SpanSizeOf<std::remove_reference_t<std::remove_cv_t<T>>>::value +
			Span<Ts...>::value)>
	{ };
}

//////////////////////////////////////////////////////////////////////////////

namespace Epic::detail
{
	// UnderlyingElement<T>
	template<class T>
	struct UnderlyingElement { using type = std::decay_t<T>; };

	// UnderlyingElement<Epic::Vector>
	template<class T, size_t N>
	struct UnderlyingElement<Epic::Vector<T, N>> { using type = std::decay_t<T>; };

	// UnderlyingElement<Epic::VectorSwizzler>
	template<class T, size_t N, size_t... Indices>
	struct UnderlyingElement<Epic::detail::VectorSwizzler<T, N, Indices...>> { using type = std::decay_t<T>; };

	// UnderlyingElement<T[N]>
	template<class T, size_t N>
	struct UnderlyingElement<T[N]> { using type = std::decay_t<T>; };

	// UnderlyingElement<std::array>
	template<class T, size_t N>
	struct UnderlyingElement<std::array<T, N>> { using type = std::decay_t<T>; };

	// SpanElement<...>
	template<class... Ts>
	struct SpanElement 
	{
		using type = std::common_type_t<typename UnderlyingElement<std::decay_t<Ts>>::type...>;
	};

	// SpanElement_t
	template<class... Ts>
	using SpanElement_t = typename SpanElement<Ts...>::type;
}

//////////////////////////////////////////////////////////////////////////////

namespace Epic::detail
{
	// SpanConstructor<...>
	template<class T>
	class SpanConstructor
	{
	public:
		template<class Iterator, class... Us>
		static void Construct(Iterator, Us&&...) noexcept { };

		template<class Iterator, class U, class... Us>
		static void Construct(Iterator iterator, U&& item, Us&&... rest) noexcept
		{
			Construct(Place(iterator, std::forward<U>(item)), std::forward<Us>(rest)...);
		}

	private:
		template<class Iterator, class U>
		static Iterator Place(Iterator iterator, U&& item) noexcept
		{
			*iterator = T(std::move(item));

			return std::next(iterator);
		}

		template<class Iterator, class U>
		static Iterator Place(Iterator iterator, U& item) noexcept
		{
			*iterator = static_cast<T>(item);

			return std::next(iterator);
		}

		template<class Iterator, class U>
		static Iterator Place(Iterator iterator, const U& item) noexcept
		{
			*iterator = static_cast<T>(item);

			return std::next(iterator);
		}

		template<class Iterator, class U, size_t N>
		static Iterator Place(Iterator iterator, Epic::Vector<U, N>&& item) noexcept
		{
			for (size_t n = 0; n < N; ++n)
			{
				*iterator = T(std::move(item[n]));
				iterator = std::next(iterator);
			}

			return iterator;
		}

		template<class Iterator, class U, size_t N>
		static Iterator Place(Iterator iterator, Epic::Vector<U, N>& item) noexcept
		{
			for (size_t n = 0; n < N; ++n)
			{
				*iterator = static_cast<T>(item[n]);
				iterator = std::next(iterator);
			}

			return iterator;
		}

		template<class Iterator, class U, size_t N>
		static Iterator Place(Iterator iterator, const Epic::Vector<U, N>& item) noexcept
		{
			for (size_t n = 0; n < N; ++n)
			{
				*iterator = static_cast<T>(item[n]);
				iterator = std::next(iterator);
			}

			return iterator;
		}

		template<class Iterator, class U, size_t N, size_t... Indices>
		static Iterator Place(Iterator iterator, Epic::detail::VectorSwizzler<U, N, Indices...>&& item) noexcept
		{
			return Place(iterator, item.ToVector());
		}

		template<class Iterator, class U, size_t N, size_t... Indices>
		static Iterator Place(Iterator iterator, Epic::detail::VectorSwizzler<U, N, Indices...>& item) noexcept
		{
			return Place(iterator, item.ToVector());
		}

		template<class Iterator, class U, size_t N, size_t... Indices>
		static Iterator Place(Iterator iterator, const Epic::detail::VectorSwizzler<U, N, Indices...>& item) noexcept
		{
			return Place(iterator, item.ToVector());
		}

		template<class Iterator, class U, size_t N>
		static Iterator Place(Iterator iterator, const U(&item)[N]) noexcept
		{
			for (size_t n = 0; n < N; ++n)
			{
				*iterator = static_cast<T>(item[n]);
				iterator = std::next(iterator);
			}

			return iterator;
		}

		template<class Iterator, class U, size_t N>
		static Iterator Place(Iterator iterator, std::array<U, N>&& item) noexcept
		{
			for (size_t n = 0; n < N; ++n)
			{
				*iterator = static_cast<T>(item[n]);
				iterator = std::next(iterator);
			}

			return iterator;
		}

		template<class Iterator, class U, size_t N>
		static Iterator Place(Iterator iterator, std::array<U, N>& item) noexcept
		{
			for (size_t n = 0; n < N; ++n)
			{
				*iterator = static_cast<T>(item[n]);
				iterator = std::next(iterator);
			}

			return iterator;
		}

		template<class Iterator, class U, size_t N>
		static Iterator Place(Iterator iterator, const std::array<U, N>& item) noexcept
		{
			for (size_t n = 0; n < N; ++n)
			{
				*iterator = static_cast<T>(item[n]);
				iterator = std::next(iterator);
			}

			return iterator;
		}
	};
}

//////////////////////////////////////////////////////////////////////////////

namespace Epic::detail
{
	constexpr size_t CalculateMatrixSize(size_t N, size_t estimate)
	{
		if (estimate * estimate == N)
			return estimate;

		return estimate * estimate > N
			? 0
			: CalculateMatrixSize(N, estimate + 1);
	}

	constexpr size_t CalculateMatrixSize(size_t N)
	{
		return CalculateMatrixSize(N, 0);
	}

	template<size_t N>
	struct IsMatrixSquare : std::bool_constant<(CalculateMatrixSize(N) != 0)> { };

	template<size_t N>
	static constexpr bool IsMatrixSquare_v = IsMatrixSquare<N>::value;
}