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

#include "EventDispatchers.hpp"
#include "CHash.hpp"

//////////////////////////////////////////////////////////////////////////////

namespace Epic
{
	template<class Signature, template<class...> class TDispatcher = Epic::ImmediateBroadcast>
	class Event;
}

//////////////////////////////////////////////////////////////////////////////

// Event
template<template<class...> class TDispatcher, class... Args>
class Epic::Event<void (Args...), TDispatcher> : public TDispatcher<Args...>
{
public:
	using type = Epic::Event<void (Args...), TDispatcher>;
	using dispatcher_type = TDispatcher<Args...>;
	using delegate_type = std::function<void (Args...)>;

public:
	void Connect(void(*pFn)(Args...), Epic::CHash handle = "") noexcept
	{
		dispatcher_type::Bind(delegate_type{ pFn }, handle, pFn);
	}

	template<class Function>
	void Connect(Function fn, Epic::CHash handle = "") noexcept
	{
		dispatcher_type::Bind(fn, handle, nullptr);
	}

	template<class TInstance, class TClass>
	void Connect(TInstance* pInstance, void (TClass::* pMember)(Args...), Epic::CHash handle = "") noexcept
	{
		const auto fn = [=](Args&&... args)
		{
			(pInstance->*pMember)(std::forward<Args>(args)...);
		};

		dispatcher_type::Bind(fn, handle, pInstance);
	}

	template<class TInstance, class TClass>
	void Connect(const TInstance* pInstance, void (TClass::* pMember)(Args...) const, Epic::CHash handle = "") noexcept
	{
		const auto fn = [=](Args&&... args)
		{
			(pInstance->*pMember)(std::forward<Args>(args)...);
		};

		dispatcher_type::Bind(fn, handle, pInstance);
	}

	template<template<class...> class UDispatcher>
	void Connect(Event<void(Args...), UDispatcher>& event, Epic::CHash handle = "") noexcept
	{
		const auto fn = [&](Args&&... args)
		{
			event.Invoke(std::forward<Args>(args)...);
		};

		dispatcher_type::Bind(fn, handle, &event);
	}

	void Disconnect()
	{
		dispatcher_type::Unbind();
	}

	void Disconnect(Epic::CHash handle) noexcept
	{
		dispatcher_type::Unbind(handle);
	}

	void Disconnect(const void* pInstance)
	{
		dispatcher_type::Unbind(pInstance);
	}

public:
	explicit operator bool() const noexcept
	{
		return dispatcher_type::operator bool();
	}

	void operator() (Args... args)
	{
		Invoke(std::forward<Args>(args)...);
	}

	Event& operator += (void(*pFn)(Args...)) noexcept
	{
		Connect(pFn);
		return *this;
	}

	template<class Function>
	Event& operator += (Function fn)
	{
		Connect(fn);
		return *this;
	}

	template<template<class...> class UDispatcher>
	Event& operator += (Event<void (Args...), UDispatcher>& event) noexcept
	{
		Connect(event);
		return *this;
	}

	Event& operator -= (void(*pFn)(Args...))
	{
		Disconnect(pFn);
		return *this;
	}

	template<template<class...> class UDispatcher>
	Event& operator -= (const Event<void(Args...), UDispatcher>& event)
	{
		Disconnect(&event);
		return *this;
	}

	Event& operator -= (Epic::CHash handle)
	{
		Disconnect(handle);
		return *this;
	}

	template<class T, typename = std::enable_if_t<std::is_class_v<T>>>
	Event& operator -= (const T* pInstance)
	{
		Disconnect(pInstance);
		return *this;
	}

	template<class T, typename = std::enable_if_t<std::is_class_v<T>>>
	Event& operator -= (const T& instance)
	{
		Disconnect(&instance);
		return *this;
	}

public:
	void Invoke(Args... args)
	{
		dispatcher_type::Dispatch(std::forward<Args>(args)...);
	}
};
