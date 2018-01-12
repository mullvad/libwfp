#pragma once

#include "filterengine.h"
#include <guiddef.h>
#include <fwpmu.h>
#include <functional>

namespace wfp
{

class ObjectExplorer
{
public:

	static bool GetFilter(FilterEngine &engine, const GUID &key, std::function<bool(const FWPM_FILTER0 &)> callback);
	static bool GetProvider(FilterEngine &engine, const GUID &key, std::function<bool(const FWPM_PROVIDER0 &)> callback);
	static bool GetSublayer(FilterEngine &engine, const GUID &key, std::function<bool(const FWPM_SUBLAYER0 &)> callback);
};

}
