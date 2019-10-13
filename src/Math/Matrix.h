//////////////////////////////////////////////////////////////////////////////
//
//            Copyright (c) 2019 Ronnie Brohn (EpicBrownie)      
//
//                Distributed under The MIT License (MIT).
//              (See accompanying file LICENSE or copy at 
//                 https://opensource.org/licenses/MIT)
//
//           Please report any bugs, typos, or suggestions to
//             https://github.com/unstable-sort/Epic/issues
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "detail/Matrix_impl.hpp"

//////////////////////////////////////////////////////////////////////////////

// Externs
namespace Epic
{
	extern template class Matrix<float, 2>;
	extern template class Matrix<float, 3>;
	extern template class Matrix<float, 4>;
						  
	extern template class Matrix<double, 2>;
	extern template class Matrix<double, 3>;
	extern template class Matrix<double, 4>;
}

// Aliases
namespace Epic
{
	using Matrix2f = Matrix<float, 2>;
	using Matrix3f = Matrix<float, 3>;
	using Matrix4f = Matrix<float, 4>;

	using Matrix2d = Matrix<double, 2>;
	using Matrix3d = Matrix<double, 3>;
	using Matrix4d = Matrix<double, 4>;
}
