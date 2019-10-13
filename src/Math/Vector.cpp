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

#include "detail/Vector_impl.hpp"
#include "detail/Quaternion_impl.hpp"

//////////////////////////////////////////////////////////////////////////////

// Explicit Instantiations
namespace Epic
{
	template class Vector<float, 1>;
	template class Vector<float, 2>;
	template class Vector<float, 3>;
	template class Vector<float, 4>;

	template class Vector<double, 1>;
	template class Vector<double, 2>;
	template class Vector<double, 3>;
	template class Vector<double, 4>;
}
