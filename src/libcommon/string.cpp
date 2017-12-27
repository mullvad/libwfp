#include "stdafx.h"
#include "string.h"
#include <sddl.h>
#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace common {
namespace string {

std::wstring FormatGuid(const GUID &guid)
{
	LPOLESTR buffer;

	auto status = StringFromCLSID(guid, &buffer);

	if (status != S_OK)
	{
		throw std::runtime_error("Failed to format GUID");
	}

	std::wstring formatted(buffer);

	CoTaskMemFree(buffer);

	return formatted;
}

std::wstring FormatSid(const SID &sid)
{
	LPWSTR buffer;

	auto status = ConvertSidToStringSidW(const_cast<SID *>(&sid), &buffer);

	if (0 == status)
	{
		throw std::runtime_error("Failed to format SID");
	}

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

std::wstring FormatIpV4(UINT32 ip)
{
	std::wstringstream ss;

	ss	<< ((ip & 0xFF000000) >> 24) << L'.'
		<< ((ip & 0x00FF0000) >> 16) << L'.'
		<< ((ip & 0x0000FF00) >> 8) << L'.'
		<< ((ip & 0x000000FF));

	return ss.str();
}

std::wstring FormatIpV6(const UINT8 ip[16])
{
	//
	// TODO: Omit longest sequence of zeros to create compact representation
	//

	std::wstringstream ss;

	const UINT16 *wptr = (const UINT16 *)ip;

	//
	// Assume little endian words
	//

	ss	<< std::hex
		<< *(wptr + 0) << L':' << *(wptr + 1) << L':'
		<< *(wptr + 2) << L':' << *(wptr + 3) << L':'
		<< *(wptr + 4) << L':' << *(wptr + 5) << L':'
		<< *(wptr + 6) << L':' << *(wptr + 7);

	return ss.str();
}

std::wstring FormatTime(const FILETIME &filetime)
{
	FILETIME ft2;

	if (FALSE == FileTimeToLocalFileTime(&filetime, &ft2))
	{
		throw std::runtime_error("Failed to convert time");
	}

	return FormatLocalTime(ft2);
}

std::wstring FormatLocalTime(const FILETIME &filetime)
{
	SYSTEMTIME st;

	if (FALSE == FileTimeToSystemTime(&filetime, &st))
	{
		throw std::runtime_error("Failed to convert time");
	}

	std::wstringstream ss;

	ss << st.wYear << L'-'
		<< std::setw(2) << std::setfill(L'0') << st.wMonth << L'-'
		<< std::setw(2) << std::setfill(L'0') << st.wDay << L' '
		<< std::setw(2) << std::setfill(L'0') << st.wHour << L':'
		<< std::setw(2) << std::setfill(L'0') << st.wMinute << L':'
		<< std::setw(2) << std::setfill(L'0') << st.wSecond;

	return ss.str();
}

}}
