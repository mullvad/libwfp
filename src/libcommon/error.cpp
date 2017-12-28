#include "stdafx.h"
#include "error.h"
#include <iomanip>
#include <sstream>

namespace common::error {

std::wstring FormatWindowsError(DWORD errorCode)
{
	LPWSTR buffer;

	auto status = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		nullptr, errorCode, 0, (LPWSTR)&buffer, 0, nullptr);

	if (0 == status)
	{
		std::wstringstream ss;

		ss << L"System error 0x" << std::setw(8) << std::setfill(L'0') << std::hex << errorCode;

		return ss.str();
	}

	std::wstring result(buffer);
	LocalFree(buffer);

	return result;
}

std::string FormatWindowsErrorPlain(DWORD errorCode)
{
	//
	// Duplicated logic, but preferred to converting the string from
	// wide char to multibyte
	//

	LPSTR buffer;

	auto status = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		nullptr, errorCode, 0, (LPSTR)&buffer, 0, nullptr);

	if (0 == status)
	{
		std::stringstream ss;

		ss << "System error 0x" << std::setw(8) << std::setfill('0') << std::hex << errorCode;

		return ss.str();
	}

	std::string result(buffer);
	LocalFree(buffer);

	return result;
}

}
