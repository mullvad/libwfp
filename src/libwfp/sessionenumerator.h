#pragma once

#include <fwpmtypes.h>
#include <functional>
#include <memory>
#include "filterengine.h"

class SessionEnumerator
{
	SessionEnumerator();

public:

	static bool enumerate(std::shared_ptr<FilterEngine> engine, std::function<bool(const FWPM_SESSION0&)> callback);
};
