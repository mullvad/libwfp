#pragma once

#include <objbase.h>
#include <windows.h>
#include <algorithm>
#include <string>
#include <vector>

namespace common::string {

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

std::wstring FormatIpV4(UINT32 ip);
std::wstring FormatIpV6(const UINT8 ip[16]);

std::wstring FormatTime(const FILETIME &filetime);
std::wstring FormatLocalTime(const FILETIME &filetime);

template<typename T>
bool BeginsWith(const std::basic_string<T> &hay, const std::basic_string<T> &needle)
{
	if (hay.size() < needle.size())
	{
		return false;
	}

	return 0 == hay.compare(0, needle.size(), needle);
}

std::wstring Lower(const std::wstring &str);
std::vector<std::wstring> Tokenize(const std::wstring &str, const std::wstring &delimiters);
std::string ToAnsi(const std::wstring &str);

}
