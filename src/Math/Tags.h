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

#include <type_traits>

//////////////////////////////////////////////////////////////////////////////

namespace Epic
{
	namespace detail
	{
		struct Tag { };

		template<class... Ts>
		struct HasTag : std::bool_constant<(std::is_base_of_v<Tag, std::decay_t<Ts>> || ...)> { };
		
		template<class... Ts>
		static constexpr bool HasTag_v = HasTag<Ts...>::value;
	}

	struct OnesTag : detail::Tag { };
	struct ZeroesTag : detail::Tag { };
	struct IdentityTag : detail::Tag { };

	struct TranslationTag : detail::Tag { };
	struct ScaleTag : detail::Tag { };
	struct RotationTag : detail::Tag { };

	struct XRotationTag : detail::Tag { };
	struct YRotationTag : detail::Tag { };
	struct ZRotationTag : detail::Tag { };

	struct LookAtTag : detail::Tag { };
}

//////////////////////////////////////////////////////////////////////////////

namespace Epic
{
	static OnesTag			One;
	static ZeroesTag		Zero;
	static IdentityTag		Identity, Origin;

	static TranslationTag	Translation;
	static ScaleTag			Scale;
	static RotationTag		Rotation;

	static XRotationTag		XRotation;
	static YRotationTag		YRotation;
	static ZRotationTag		ZRotation;

	static LookAtTag		LookAt;
}
