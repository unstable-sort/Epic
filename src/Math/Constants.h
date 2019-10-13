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

#include <limits>

//////////////////////////////////////////////////////////////////////////////

namespace Epic
{
	template<typename T = float>
	constexpr static T Pi = T(3.1415926535897932385);

	template<typename T = float>
	constexpr static T PiSq = Pi<T> * Pi<T>;

	template<typename T = float>
	constexpr static T TwoPi = Pi<T> + Pi<T>;

	template<typename T = float>
	constexpr static T HalfPi = Pi<T> / T(2);

	template<typename T = float>
	constexpr static T InvPi = T(1) / Pi<T>;

	template<typename T = float>
	constexpr static T InvTwoPi = T(1) / TwoPi<T>;

	template<typename T = float>
	constexpr static T Epsilon = std::numeric_limits<T>::epsilon();

	template<typename T = float>
	constexpr static T MaxReal = std::numeric_limits<T>::max();

	template<typename T = float>
	constexpr static T MinReal = std::numeric_limits<T>::min();
}
