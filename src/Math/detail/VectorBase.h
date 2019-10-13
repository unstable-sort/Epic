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

#include "VectorBase_impl.hpp"

//////////////////////////////////////////////////////////////////////////////

// Externs
namespace Epic::detail
{
	extern template class VectorBase<float, 1>;
	extern template class VectorBase<float, 2>;
	extern template class VectorBase<float, 3>;
	extern template class VectorBase<float, 4>;

	extern template class VectorBase<double, 1>;
	extern template class VectorBase<double, 2>;
	extern template class VectorBase<double, 3>;
	extern template class VectorBase<double, 4>;
}

