#include "stdafx.h"
#include "string.h"
#include <sddl.h>
#include <vector>
#include <algorithm>

namespace common {
namespace string {

std::wstring FormatGuid(const GUID &guid)
{
	LPOLESTR buffer;

	auto STATUS = StringFromCLSID(guid, &buffer);

	std::wstring formatted(buffer);

	CoTaskMemFree(buffer);

	return formatted;
}

std::wstring FormatSid(const SID &sid)
{
	LPWSTR buffer;

	auto STATUS = ConvertSidToStringSidW(const_cast<SID *>(&sid), &buffer);

	std::wstring formatted(buffer);

	LocalFree((HLOCAL)buffer);

	return formatted;
}

std::wstring Join(const std::vector<std::wstring> &parts)
{
	switch (parts.size())
	{
	case 0:
		return L"";
	case 1:
		return parts[0];
	default:
		{
			std::wstring joined;

			size_t reserveSize = 0;

			std::for_each(parts.begin(), parts.end(), [&reserveSize](const std::wstring &part)
			{
				reserveSize += (part.size() + 2);
			});

			joined.reserve(reserveSize);

			std::for_each(parts.begin(), parts.end(), [&joined](const std::wstring &part)
			{
				if (!joined.empty())
				{
					joined.append(L", ");
				}

				joined.append(part);
			});

			return joined;
		}
	};
}

}}
