#pragma once

#include "stdafx.h"
#include <objbase.h>
#include <Windows.h>
#include <string>
#include <vector>
#include <algorithm>

namespace common {
namespace string {

std::wstring FormatGuid(const GUID &guid);
std::wstring FormatSid(const SID &sid);
std::wstring Join(const std::vector<std::wstring> &parts);

template<typename T>
std::wstring FormatFlags(std::vector<std::pair<T, std::wstring> > &definitions, T flags)
{
	std::vector<std::wstring> present;
	T remaining = flags;

	std::for_each(definitions.begin(), definitions.end(), [&](const std::pair<T, std::wstring> &definition)
	{
		if ((flags & definition.first) != 0)
		{
			present.push_back(definition.second);
			remaining &= ~definition.first;
		}
	});

	if (remaining != 0)
	{
		present.push_back(L"[...]");
	}

	return Join(present);
}

}}
