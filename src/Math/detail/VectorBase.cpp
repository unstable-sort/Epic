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

#include "VectorBase_impl.hpp"

//////////////////////////////////////////////////////////////////////////////

// Explicit Instantiations
namespace Epic::detail
{
	template class VectorBase<float, 1>;
	template class VectorBase<float, 2>;
	template class VectorBase<float, 3>;
	template class VectorBase<float, 4>;

	template class VectorBase<double, 1>;
	template class VectorBase<double, 2>;
	template class VectorBase<double, 3>;
	template class VectorBase<double, 4>;
}
