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

//////////////////////////////////////////////////////////////////////////////

namespace Epic
{
	struct NullMutex;
}

//////////////////////////////////////////////////////////////////////////////

// NullMutex
struct Epic::NullMutex
{
	void lock() noexcept { }
	bool try_lock() noexcept { return true; }
	void unlock() noexcept { }
};