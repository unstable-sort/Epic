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

#include "detail/Angle_impl.hpp"

//////////////////////////////////////////////////////////////////////////////

// Externs
namespace Epic
{
	extern template class Radian<float>;
	extern template class Radian<double>;
	extern template class Degree<float>;
	extern template class Degree<double>;
}

//////////////////////////////////////////////////////////////////////////////

// Aliases
namespace Epic
{
	using Radianf = Radian<float>;
	using Radiand = Radian<double>;

	using Degreef = Degree<float>;
	using Degreed = Degree<double>;
}
