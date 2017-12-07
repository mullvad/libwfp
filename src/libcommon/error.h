#pragma once

#include <string>
#include <Windows.h>
#include <stdexcept>
#include <sstream>

#define THROW_UNLESS(expected, actual, operation)\
if(actual != expected)\
{\
	std::stringstream ss;\
	ss << operation << ": " << common::error::FormatWindowsErrorPlain(actual);\
	throw std::runtime_error(ss.str());\
}\

#define THROW_GLE_UNLESS(expected, actual, operation)\
if(actual != expected)\
{\
	DWORD errorCode = GetLastError();\
	std::stringstream ss;\
	ss << operation << ": " << common::error::FormatWindowsErrorPlain(errorCode);\
	throw std::runtime_error(ss.str());\
}\

namespace common {
namespace error {

std::wstring FormatWindowsError(DWORD errorCode);
std::string FormatWindowsErrorPlain(DWORD errorCode);

}}
