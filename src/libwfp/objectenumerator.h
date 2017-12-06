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
	static bool Connections(std::shared_ptr<FilterEngine> engine, std::function<bool(const FWPM_CONNECTION0&)> callback);
	static bool Events(std::shared_ptr<FilterEngine> engine, std::function<bool(const FWPM_NET_EVENT0&)> callback);
	static bool Filters(std::shared_ptr<FilterEngine> engine, std::function<bool(const FWPM_FILTER0&)> callback);
	static bool Layers(std::shared_ptr<FilterEngine> engine, std::function<bool(const FWPM_LAYER0&)> callback);
	static bool ProviderContexts(std::shared_ptr<FilterEngine> engine, std::function<bool(const FWPM_PROVIDER_CONTEXT0&)> callback);
};

} // namespace wfp
