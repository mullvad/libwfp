#include "stdafx.h"
#include "string.h"
#include <sddl.h>

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

}}
