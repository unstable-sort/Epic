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

#include <algorithm>
#include <functional>
#include <type_traits>
#include <vector>
#include <tuple>

#include "CHash.hpp"

//////////////////////////////////////////////////////////////////////////////

namespace Epic
{
	template<class... Args>
	class Immediate;

	template<class... Args>
	class ImmediateBroadcast;

	template<class... Args>
	class DeferredBroadcast;
}

//////////////////////////////////////////////////////////////////////////////

// Immediate
template<class... Args>
class Epic::Immediate
{
public:
	using type = Epic::Immediate<Args...>;
	using delegate_type = std::function<void(Args...)>;

public:
	Immediate() noexcept = default;
	Immediate(const Immediate&) noexcept = default;
	Immediate(Immediate&&) noexcept = default;

	~Immediate() noexcept { Unbind(); }

	Immediate& operator = (const Immediate&) = default;
	Immediate& operator = (Immediate&&) = default;

private:
	Epic::CHash m_Handle;
	delegate_type m_BoundHandler;
	const void* m_pBoundInstance;

public:
	explicit operator bool() const noexcept
	{
		return (bool)m_BoundHandler;
	}

protected:
	void Bind(delegate_type fn, Epic::CHash handle, const void* pInstance) noexcept
	{
		m_Handle = handle;
		m_BoundHandler = fn;
		m_pBoundInstance = pInstance;
	}

	void Unbind() noexcept
	{
		m_Handle = nullptr;
		m_BoundHandler = nullptr;
		m_pBoundInstance = nullptr;
	}

	void Unbind(Epic::CHash handle) noexcept
	{
		if (m_Handle == handle)
		{
			m_Handle = nullptr;
			m_BoundHandler = nullptr;
			m_pBoundInstance = nullptr;
		}
	}

	void Unbind(const void* pInstance) noexcept
	{
		if (m_pBoundInstance == pInstance)
		{
			m_Handle = nullptr;
			m_BoundHandler = nullptr;
			m_pBoundInstance = nullptr;
		}
	}

protected:
	void Dispatch(Args&&... args) const
	{
		if (m_BoundHandler)
			m_BoundHandler(std::forward<Args>(args)...);
	}
};

//////////////////////////////////////////////////////////////////////////////

// ImmediateBroadcast
template<class... Args>
class Epic::ImmediateBroadcast
{
public:
	using type = Epic::ImmediateBroadcast<Args...>;
	using delegate_type = std::function<void(Args...)>;

private:
	struct Binding
	{
		Epic::CHash Handle;
		delegate_type Handler;
		const void* pInstance;
	};

public:
	ImmediateBroadcast() noexcept = default;
	ImmediateBroadcast(const ImmediateBroadcast&) = default;
	ImmediateBroadcast(ImmediateBroadcast&&) noexcept = default;

	~ImmediateBroadcast() noexcept { Unbind(); }

	ImmediateBroadcast& operator = (const ImmediateBroadcast&) = default;
	ImmediateBroadcast& operator = (ImmediateBroadcast&&) noexcept = default;

private:
	using bindings_type = std::vector<Binding>;

private:
	bindings_type m_Bindings;

public:
	explicit operator bool() const noexcept
	{
		return !m_Bindings.empty();
	}

protected:
	void Bind(delegate_type fn, Epic::CHash handle, const void* pInstance) noexcept
	{
		if (handle)
			Erase(handle);

		m_Bindings.push_back({ handle, fn, pInstance });
	}

	void Unbind() noexcept
	{
		bindings_type().swap(m_Bindings);
	}

	void Unbind(Epic::CHash handle) noexcept
	{
		Erase(handle);
	}

	void Unbind(const void* pInstance) noexcept
	{
		Erase(pInstance);
	}

protected:
	void Dispatch(Args&&... args) const
	{
		for (const auto& binding : m_Bindings)
			binding.Handler(std::forward<Args>(args)...);
	}

private:
	void Erase(Epic::CHash handle) noexcept
	{
		const auto it = std::find_if(m_Bindings.begin(), m_Bindings.end(),
			[&](const auto& binding) -> bool { return handle == binding.Handle; });

		if (it != m_Bindings.end())
			m_Bindings.erase(it);
	}

	void Erase(const void* pInstance) noexcept
	{
		const auto it = std::find_if(m_Bindings.begin(), m_Bindings.end(),
			[&](const auto& binding) -> bool { return pInstance == binding.pInstance; });

		if (it != m_Bindings.end())
			m_Bindings.erase(it);
	}
};

//////////////////////////////////////////////////////////////////////////////

// DeferredBroadcast
template<class... Args>
class Epic::DeferredBroadcast
{
public:
	using type = Epic::DeferredBroadcast<Args...>;
	using delegate_type = std::function<void(Args...)>;

private:
	struct Binding
	{
		Epic::CHash Handle;
		delegate_type Handler;
		const void* pInstance;
	};

public:
	DeferredBroadcast() noexcept = default;
	DeferredBroadcast(const DeferredBroadcast&) = default;
	DeferredBroadcast(DeferredBroadcast&&) noexcept = default;

	~DeferredBroadcast() noexcept { Unbind(); }

	DeferredBroadcast& operator = (const DeferredBroadcast&) = default;
	DeferredBroadcast& operator = (DeferredBroadcast&&) noexcept = default;

private:
	using bindings_type = std::vector<Binding>;
	using invocation_type = std::tuple<Args...>;
	using ibuffer_type = std::vector<invocation_type>;

private:
	bindings_type m_Bindings;
	ibuffer_type m_Invocations;

public:
	explicit operator bool() const noexcept
	{
		return !m_Bindings.empty();
	}

protected:
	void Bind(delegate_type fn, Epic::CHash handle, const void* pInstance) noexcept
	{
		if (handle)
			Erase(handle);

		m_Bindings.push_back({ handle, fn, pInstance });
	}

	void Unbind() noexcept
	{
		bindings_type().swap(m_Bindings);
	}

	void Unbind(Epic::CHash handle) noexcept
	{
		Erase(handle);
	}

	void Unbind(const void* pInstance) noexcept
	{
		Erase(pInstance);
	}

protected:
	void Dispatch(Args&&... args)
	{
		m_Invocations.emplace_back(std::forward<Args>(args)...);
	}

public:
	void Broadcast()
	{
		for (auto& argPack : m_Invocations)
			Invoke(argPack, std::make_integer_sequence<std::size_t, sizeof...(Args)>());

		m_Invocations.clear();
	}

private:
	template<size_t... Is>
	void Invoke(const invocation_type& invocation, std::integer_sequence<std::size_t, Is...>)
	{
		for (const auto& binding : m_Bindings)
			binding.Handler(std::get<Is>(invocation)...);
	}

	void Erase(Epic::CHash handle) noexcept
	{
		const auto it = std::find_if(m_Bindings.begin(), m_Bindings.end(),
			[&](const auto& binding) -> bool { return handle == binding.Handle; });

		if (it != m_Bindings.end())
			m_Bindings.erase(it);
	}

	void Erase(const void* pInstance) noexcept
	{
		const auto it = std::find_if(m_Bindings.begin(), m_Bindings.end(),
			[&](const auto& binding) -> bool { return pInstance == binding.pInstance; });

		if (it != m_Bindings.end())
			m_Bindings.erase(it);
	}
};