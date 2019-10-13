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

#include "detail/Quaternion_impl.hpp"

//////////////////////////////////////////////////////////////////////////////

// Externs
namespace Epic
{
	extern template class Quaternion<float>;
	extern template class Quaternion<double>;
}

// Aliases
namespace Epic
{
	using Quaternionf = Quaternion<float>;
	using Quaterniond = Quaternion<double>;
}
