#pragma once

#include <fwpmtypes.h>
#include <functional>
#include <memory>
#include "filterengine.h"
#include <windows.h>

namespace wfp
{

class ObjectEnumerator
{
	ObjectEnumerator();

public:

	static bool Sessions(HANDLE session, std::function<bool(const FWPM_SESSION0&)> callback);
	static bool Providers(HANDLE session, std::function<bool(const FWPM_PROVIDER0&)> callback);
	static bool Connections(HANDLE session, std::function<bool(const FWPM_CONNECTION0&)> callback);
	static bool Events(HANDLE session, std::function<bool(const FWPM_NET_EVENT0&)> callback);
	static bool Filters(HANDLE session, std::function<bool(const FWPM_FILTER0&)> callback);
	static bool Layers(HANDLE session, std::function<bool(const FWPM_LAYER0&)> callback);
	static bool ProviderContexts(HANDLE session, std::function<bool(const FWPM_PROVIDER_CONTEXT0&)> callback);
	static bool Sublayers(HANDLE session, std::function<bool(const FWPM_SUBLAYER0&)> callback);
};

} // namespace wfp
