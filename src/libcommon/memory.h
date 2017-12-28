#pragma once

#include "math.h"
#include <windows.h>
#include <algorithm>
#include <functional>
#include <memory>
#include <vector>

namespace common::memory {

struct HandleDeleter
{
	void operator()(HANDLE *h)
	{
		if (*h != 0 && *h != INVALID_HANDLE_VALUE)
		{
			CloseHandle(*h);
		}
	}
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

inline size_t AlignNative(size_t value)
{
	return ::common::math::RoundPowerTwo(value, sizeof(size_t));
}

}
