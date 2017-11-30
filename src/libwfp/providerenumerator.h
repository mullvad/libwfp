#pragma once

#include <fwpmtypes.h>
#include <functional>
#include <memory>
#include "filterengine.h"

class ProviderEnumerator
{
	ProviderEnumerator();

public:

	static bool enumerate(std::shared_ptr<FilterEngine> engine, std::function<bool(const FWPM_PROVIDER0&)> callback);
};
