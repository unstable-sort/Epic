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

#include "detail/Vector_impl.hpp"

//////////////////////////////////////////////////////////////////////////////

// Externs
namespace Epic
{
	extern template class Vector<float, 1>;
	extern template class Vector<float, 2>;
	extern template class Vector<float, 3>;
	extern template class Vector<float, 4>;

	extern template class Vector<double, 1>;
	extern template class Vector<double, 2>;
	extern template class Vector<double, 3>;
	extern template class Vector<double, 4>;
}

// Aliases
namespace Epic
{
	using Vector1f = Vector<float, 1>;
	using Vector2f = Vector<float, 2>;
	using Vector3f = Vector<float, 3>;
	using Vector4f = Vector<float, 4>;

	using Vector1d = Vector<double, 1>;
	using Vector2d = Vector<double, 2>;
	using Vector3d = Vector<double, 3>;
	using Vector4d = Vector<double, 4>;
}
