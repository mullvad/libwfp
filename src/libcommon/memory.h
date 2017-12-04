#pragma once
#include <functional>
#include <algorithm>
#include <vector>

namespace common {
namespace memory {

template<typename T>
class AutoResource
{
public:

	AutoResource(T resource, std::function<void(T)> deleter)
		: m_auto(true)
		, m_resource(resource)
		, m_deleter(deleter)
	{
	}

	~AutoResource()
	{
		if (m_auto)
		{
			deleter(m_resource);
		}
	}

	void detach()
	{
		m_auto = false;
	}

private:

	bool m_auto;

	T m_resource;
	std::function<void(T)> m_deleter;
};

class ScopeDestructor
{
public:

	ScopeDestructor()
	{
	}

	~ScopeDestructor()
	{
		std::for_each(m_operations.rbegin(), m_operations.rend(), [](std::function<void()> op)
		{
			op();
		});
	}

	ScopeDestructor &operator+=(std::function<void()> op)
	{
		m_operations.push_back(op);
		return *this;
	}

private:

	const ScopeDestructor(const ScopeDestructor &);
	ScopeDestructor &operator=(const ScopeDestructor &);

	std::vector<std::function<void()> > m_operations;
};

}}
