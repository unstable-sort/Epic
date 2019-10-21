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

#include <vector>
#include <algorithm>
#include <mutex>

#include "NullMutex.hpp"

//////////////////////////////////////////////////////////////////////////////

namespace Epic
{
	enum AutoListIgnoreT { Ignore };
	enum AutoListUnsynchronizedT { Unsynchronized };
}

namespace Epic
{
	template<class CRTP, bool Sync = false>
	class AutoList;
}

//////////////////////////////////////////////////////////////////////////////

// AutoList
template<class CRTP, bool Sync>
class Epic::AutoList
{
	static_assert(std::is_class_v<std::remove_cv_t<CRTP>>, "AutoList can only store class types");

public:
	using type = Epic::AutoList<CRTP, Sync>;
	using pointer_type = std::add_pointer_t<CRTP>;
	using list_store_type = std::vector<pointer_type>;
	using mutex_type = std::conditional_t<Sync, std::recursive_mutex, Epic::NullMutex>;
	using lock_type = std::lock_guard<mutex_type>;

private:
	static mutex_type s_Mutex;
	static list_store_type s_AutoList;

protected:
	AutoList()
	{
		lock_type lock(s_Mutex);
		Insert(pointer_type(this));
	}

	AutoList(const AutoList&)
	{
		lock_type lock(s_Mutex);
		Insert(pointer_type(this));
	}

	AutoList(AutoList&& other)
	{
		lock_type lock(s_Mutex);
		Erase(pointer_type(&other));
		Insert(pointer_type(this));
	}

	explicit AutoList(AutoListIgnoreT) noexcept { }

	explicit AutoList(AutoListUnsynchronizedT) noexcept 
	{
		Insert(pointer_type(this));
	}

	~AutoList()
	{
		lock_type lock(s_Mutex);
		Erase(pointer_type(this));
	}

public:
	struct AutoListRange
	{
		list_store_type& list;

		AutoListRange(list_store_type& store) : list(store) { }

		AutoListRange() = delete;
		AutoListRange(const AutoListRange&) = delete;
		AutoListRange(AutoListRange&&) = delete;

		~AutoListRange() = default;

		AutoListRange& operator = (const AutoListRange&) = delete;
		AutoListRange& operator = (AutoListRange&&) = delete;

		auto begin()
		{
			return std::begin(list);
		}

		auto begin() const
		{
			return std::begin(list);
		}

		auto end()
		{
			return std::end(list);
		}

		auto end() const
		{
			return std::end(list);
		}

		const auto size() const noexcept
		{
			return std::size(list);
		}
	};

public:
	static AutoListRange Range()
	{
		return { s_AutoList };
	}

public:
	template<typename Function>
	static void Apply(Function fn)
	{
		lock_type lock(s_Mutex);

		for (auto pItem : Range())
			fn(pItem);
	}

private:
	static void Insert(pointer_type pItem)
	{
		s_AutoList.push_back(pItem);
	}

	static void Erase(pointer_type pItem)
	{
		auto it = std::find(std::begin(s_AutoList), std::end(s_AutoList), pItem);
		if (it != std::end(s_AutoList))
			s_AutoList.erase(it);
	}
};

//////////////////////////////////////////////////////////////////////////////

// Static Initializers
template<class T, bool Sync>
typename Epic::AutoList<T, Sync>::mutex_type Epic::AutoList<T, Sync>::s_Mutex;

template<class T, bool Sync>
typename Epic::AutoList<T, Sync>::list_store_type Epic::AutoList<T, Sync>::s_AutoList;
