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

#include "detail/Matrix_impl.hpp"

//////////////////////////////////////////////////////////////////////////////

// Explicit Instantiations
namespace Epic
{
	template class Matrix<float, 2>;
	template class Matrix<float, 3>;
	template class Matrix<float, 4>;

	template class Matrix<double, 2>;
	template class Matrix<double, 3>;
	template class Matrix<double, 4>;
}
