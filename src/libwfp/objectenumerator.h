#pragma once

#include <fwpmtypes.h>
#include <functional>
#include <memory>
#include "filterengine.h"

namespace wfp
{

class ObjectEnumerator
{
	ObjectEnumerator();

public:

	static bool Sessions(std::shared_ptr<FilterEngine> engine, std::function<bool(const FWPM_SESSION0&)> callback);
	static bool Providers(std::shared_ptr<FilterEngine> engine, std::function<bool(const FWPM_PROVIDER0&)> callback);
};

} // namespace wfp
