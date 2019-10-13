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

#include <type_traits>

//////////////////////////////////////////////////////////////////////////////

namespace Epic
{
	namespace
	{
		template<class T, class F, typename EnabledForFloatingPoint = std::enable_if_t<std::is_floating_point_v<F>>>
		inline auto Lerp(const T& from, const T& to, const F t) noexcept
		{
			return from + ((to - from) * t);
		}
	}
}
