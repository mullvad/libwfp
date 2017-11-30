#pragma once

#include "stdafx.h"
#include <objbase.h>
#include <Windows.h>
#include <string>

namespace common {
namespace string {

std::wstring FormatGuid(const GUID &guid);
std::wstring FormatSid(const SID &sid);

}}
