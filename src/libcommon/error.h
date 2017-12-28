#pragma once

#include <windows.h>
#include <string>

#define THROW_UNLESS(expected, actual, operation)\
if(actual != expected)\
{\
	::common::error::Throw(operation, actual);\
}\

#define THROW_GLE_UNLESS(expected, actual, operation)\
if(actual != expected)\
{\
	::common::error::Throw(operation, GetLastError());\
}\

#define THROW_GLE_IF(unwanted, actual, operation)\
if(actual == unwanted)\
{\
	::common::error::Throw(operation, GetLastError());\
}\

#define THROW_GLE(operation)\
{\
	::common::error::Throw(operation, GetLastError());\
}\

namespace common::error {

std::wstring FormatWindowsError(DWORD errorCode);
std::string FormatWindowsErrorPlain(DWORD errorCode);

void Throw(const char *operation, DWORD errorCode);
void Throw(const std::string &operation, DWORD errorCode);

}
