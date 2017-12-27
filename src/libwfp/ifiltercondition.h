#pragma once

#include <guiddef.h>
#include <fwpmu.h>
#include <windows.h>
#include <string>

namespace wfp
{

struct IFilterCondition
{
	virtual std::wstring toString() const = 0;
	virtual const GUID &identifier() const = 0;
	virtual const FWPM_FILTER_CONDITION0 &condition() const = 0;
};

}
