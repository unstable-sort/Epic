//////////////////////////////////////////////////////////////////////////////
//
//            Copyright (c) 2019 Ronnie Brohn (EpicBrownie)      
//
//                Distributed under The MIT License (MIT).
//             (See accompanying file LICENSE or copy at 
//                 https://opensource.org/licenses/MIT)
//
//           Please report any bugs, typos, or suggestions to
//              https://github.com/epicbrownie/Epic/issues
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include <array>

#include "../Vector.h"

//////////////////////////////////////////////////////////////////////////////

namespace Epic::detail
{
	template<class T, size_t N>
	class MatrixBase;
}

//////////////////////////////////////////////////////////////////////////////

template<class T, size_t N>
class Epic::detail::MatrixBase
{
public:
	using value_type = T;
	using column_type = Epic::Vector<T, N>;
	using element_container_type = std::array<value_type, N * N>;
	using column_container_type = std::array<column_type, N>;

	static constexpr size_t ColumnCount = N;
	static constexpr size_t ElementCount = N * N;
	static constexpr size_t Size = N * N;

	union
	{
		element_container_type Values;
		column_container_type Columns;
	};
};

template<class T>
class Epic::detail::MatrixBase<T, 0>;

template<class T>
class Epic::detail::MatrixBase<T, 1>;

template<class T>
class Epic::detail::MatrixBase<T, 2>
{
public:
	using value_type = T;
	using column_type = Epic::Vector<T, 2>;
	using element_container_type = std::array<value_type, 4>;
	using column_container_type = std::array<column_type, 2>;

	static constexpr size_t ColumnCount = 2;
	static constexpr size_t ElementCount = 4;
	static constexpr size_t Size = 4;

	union
	{
		element_container_type Values;
		column_container_type Columns;

		struct
		{
			column_type cx;
			column_type cy;
		};
	};
};

template<class T>
class Epic::detail::MatrixBase<T, 3>
{
public:
	using value_type = T;
	using column_type = Epic::Vector<T, 3>;
	using element_container_type = std::array<value_type, 9>;
	using column_container_type = std::array<column_type, 3>;

	static constexpr size_t ColumnCount = 3;
	static constexpr size_t ElementCount = 9;
	static constexpr size_t Size = 9;

	union
	{
		element_container_type Values;
		column_container_type Columns;

		struct
		{
			column_type cx;
			column_type cy;
			column_type cz;
		};
	};
};

template<class T>
class Epic::detail::MatrixBase<T, 4>
{
public:
	using value_type = T;
	using column_type = Epic::Vector<T, 4>;
	using element_container_type = std::array<value_type, 16>;
	using column_container_type = std::array<column_type, 4>;

	static constexpr size_t ColumnCount = 4;
	static constexpr size_t ElementCount = 16;
	static constexpr size_t Size = 16;

	union
	{
		element_container_type Values;
		column_container_type Columns;

		struct
		{
			column_type cx;
			column_type cy;
			column_type cz;
			column_type cw;
		};
	};
};