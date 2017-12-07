#include "stdafx.h"
#include "objectenumerator.h"
#include <stdexcept>
#include <fwpmu.h>
#include "libcommon/memory.h"
#include "libcommon/error.h"

namespace wfp
{

//static
bool ObjectEnumerator::Sessions(
	std::shared_ptr<FilterEngine> engine,
	std::function<bool(const FWPM_SESSION0&)> callback)
{
	HANDLE enumHandle = INVALID_HANDLE_VALUE;

	auto status = FwpmSessionCreateEnumHandle0(
		(*engine).session(),
		nullptr,
		&enumHandle
	);

	THROW_UNLESS(ERROR_SUCCESS, status, "Create enumeration context for WFP sessions")

	common::memory::ScopeDestructor scopeDestructor;

	scopeDestructor += [engine, &enumHandle]()
	{
		FwpmSessionDestroyEnumHandle0((*engine).session(), enumHandle);
	};

	FWPM_SESSION0** sessions = nullptr;
	UINT32 sessionsReturned = 0;

	static const UINT32 SESSIONS_REQUESTED = 100;

	do
	{
		status = FwpmSessionEnum0(
			(*engine).session(),
			enumHandle,
			SESSIONS_REQUESTED,
			&sessions,
			&sessionsReturned
		);

		THROW_UNLESS(ERROR_SUCCESS, status, "Enumerate WFP sessions")

		if (0 == sessionsReturned)
		{
			break;
		}

		#pragma warning(suppress: 4456)
		common::memory::ScopeDestructor scopeDestructor;

		scopeDestructor += [&sessions]()
		{
			FwpmFreeMemory0((void**)&sessions);
		};

		for (UINT32 i = 0; i < sessionsReturned; ++i)
		{
			auto session = *sessions[i];

			if (callback(session) == false)
			{
				return false;
			}
		}
	} while (SESSIONS_REQUESTED == sessionsReturned);

	return true;
}

//static
bool ObjectEnumerator::Providers(std::shared_ptr<FilterEngine> engine,
	std::function<bool(const FWPM_PROVIDER0&)> callback)
{
	HANDLE enumHandle = INVALID_HANDLE_VALUE;

	auto status = FwpmProviderCreateEnumHandle0(
		(*engine).session(),
		nullptr,
		&enumHandle
	);

	THROW_UNLESS(ERROR_SUCCESS, status, "Create enumeration context for WFP providers")

	common::memory::ScopeDestructor scopeDestructor;

	scopeDestructor += [engine, &enumHandle]()
	{
		FwpmProviderDestroyEnumHandle0((*engine).session(), enumHandle);
	};

	FWPM_PROVIDER0** providers = nullptr;
	UINT32 providersReturned = 0;

	static const UINT32 PROVIDERS_REQUESTED = 100;

	do
	{
		status = FwpmProviderEnum0(
			(*engine).session(),
			enumHandle,
			PROVIDERS_REQUESTED,
			&providers,
			&providersReturned
		);

		THROW_UNLESS(ERROR_SUCCESS, status, "Enumerate WFP providers")

		if (0 == providersReturned)
		{
			break;
		}

		#pragma warning(suppress: 4456)
		common::memory::ScopeDestructor scopeDestructor;

		scopeDestructor += [&providers]()
		{
			FwpmFreeMemory0((void**)&providers);
		};

		for (UINT32 i = 0; i < providersReturned; ++i)
		{
			auto provider = *providers[i];

			if (callback(provider) == false)
			{
				return false;
			}
		}
	} while (PROVIDERS_REQUESTED == providersReturned);

	return true;
}

//static
bool ObjectEnumerator::Connections(
	std::shared_ptr<FilterEngine> engine,
	std::function<bool(const FWPM_CONNECTION0&)> callback)
{
	HANDLE enumHandle = INVALID_HANDLE_VALUE;

	auto status = FwpmConnectionCreateEnumHandle0(
		(*engine).session(),
		nullptr,
		&enumHandle
	);

	THROW_UNLESS(ERROR_SUCCESS, status, "Create enumeration context for WFP connections")

	common::memory::ScopeDestructor scopeDestructor;

	scopeDestructor += [engine, &enumHandle]()
	{
		FwpmConnectionDestroyEnumHandle0((*engine).session(), enumHandle);
	};

	FWPM_CONNECTION0** connections = nullptr;
	UINT32 connectionsReturned = 0;

	static const UINT32 CONNECTIONS_REQUESTED = 100;

	do
	{
		status = FwpmConnectionEnum0(
			(*engine).session(),
			enumHandle,
			CONNECTIONS_REQUESTED,
			&connections,
			&connectionsReturned
		);
		
		THROW_UNLESS(ERROR_SUCCESS, status, "Enumerate WFP connections")

		if (0 == connectionsReturned)
		{
			break;
		}

		#pragma warning(suppress: 4456)
		common::memory::ScopeDestructor scopeDestructor;

		scopeDestructor += [&connections]()
		{
			FwpmFreeMemory0((void**)&connections);
		};

		for (UINT32 i = 0; i < connectionsReturned; ++i)
		{
			auto connection = *connections[i];

			if (callback(connection) == false)
			{
				return false;
			}
		}
	} while (CONNECTIONS_REQUESTED == connectionsReturned);

	return true;
}

//static
bool ObjectEnumerator::Events(
	std::shared_ptr<FilterEngine> engine,
	std::function<bool(const FWPM_NET_EVENT0&)> callback)
{
	HANDLE enumHandle = INVALID_HANDLE_VALUE;

	auto status = FwpmNetEventCreateEnumHandle0(
		(*engine).session(),
		nullptr,
		&enumHandle
	);

	THROW_UNLESS(ERROR_SUCCESS, status, "Create enumeration context for WFP events")

	common::memory::ScopeDestructor scopeDestructor;

	scopeDestructor += [engine, &enumHandle]()
	{
		FwpmNetEventDestroyEnumHandle0((*engine).session(), enumHandle);
	};

	FWPM_NET_EVENT0** events = nullptr;
	UINT32 eventsReturned = 0;

	static const UINT32 EVENTS_REQUESTED = 100;

	do
	{
		status = FwpmNetEventEnum0(
			(*engine).session(),
			enumHandle,
			EVENTS_REQUESTED,
			&events,
			&eventsReturned
		);

		THROW_UNLESS(ERROR_SUCCESS, status, "Enumerate WFP events")

		if (0 == eventsReturned)
		{
			break;
		}

		#pragma warning(suppress: 4456)
		common::memory::ScopeDestructor scopeDestructor;

		scopeDestructor += [&events]()
		{
			FwpmFreeMemory0((void**)&events);
		};

		for (UINT32 i = 0; i < eventsReturned; ++i)
		{
			auto event = *events[i];

			if (callback(event) == false)
			{
				return false;
			}
		}
	} while (EVENTS_REQUESTED == eventsReturned);

	return true;
}

//static
bool ObjectEnumerator::Filters(
	std::shared_ptr<FilterEngine> engine,
	std::function<bool(const FWPM_FILTER0&)> callback)
{
	HANDLE enumHandle = INVALID_HANDLE_VALUE;

	auto status = FwpmFilterCreateEnumHandle0(
		(*engine).session(),
		nullptr,
		&enumHandle
	);

	THROW_UNLESS(ERROR_SUCCESS, status, "Create enumeration context for WFP filters")

	common::memory::ScopeDestructor scopeDestructor;

	scopeDestructor += [engine, &enumHandle]()
	{
		FwpmFilterDestroyEnumHandle0((*engine).session(), enumHandle);
	};

	FWPM_FILTER0** filters = nullptr;
	UINT32 filtersReturned = 0;

	static const UINT32 FILTERS_REQUESTED = 100;

	do
	{
		status = FwpmFilterEnum0(
			(*engine).session(),
			enumHandle,
			FILTERS_REQUESTED,
			&filters,
			&filtersReturned
		);

		THROW_UNLESS(ERROR_SUCCESS, status, "Enumerate WFP filters")

		if (0 == filtersReturned)
		{
			break;
		}

		#pragma warning(suppress: 4456)
		common::memory::ScopeDestructor scopeDestructor;

		scopeDestructor += [&filters]()
		{
			FwpmFreeMemory0((void**)&filters);
		};

		for (UINT32 i = 0; i < filtersReturned; ++i)
		{
			auto filter = *filters[i];

			if (callback(filter) == false)
			{
				return false;
			}
		}
	} while (FILTERS_REQUESTED == filtersReturned);

	return true;
}

//static
bool ObjectEnumerator::Layers(
	std::shared_ptr<FilterEngine> engine,
	std::function<bool(const FWPM_LAYER0&)> callback)
{
	HANDLE enumHandle = INVALID_HANDLE_VALUE;

	auto status = FwpmLayerCreateEnumHandle0(
		(*engine).session(),
		nullptr,
		&enumHandle
	);

	THROW_UNLESS(ERROR_SUCCESS, status, "Create enumeration context for WFP layers")

	common::memory::ScopeDestructor scopeDestructor;

	scopeDestructor += [engine, &enumHandle]()
	{
		FwpmLayerDestroyEnumHandle0((*engine).session(), enumHandle);
	};

	FWPM_LAYER0** layers = nullptr;
	UINT32 layersReturned = 0;

	static const UINT32 LAYERS_REQUESTED = 100;

	do
	{
		status = FwpmLayerEnum0(
			(*engine).session(),
			enumHandle,
			LAYERS_REQUESTED,
			&layers,
			&layersReturned
		);

		THROW_UNLESS(ERROR_SUCCESS, status, "Enumerate WFP layers")

		if (0 == layersReturned)
		{
			break;
		}

		#pragma warning(suppress: 4456)
		common::memory::ScopeDestructor scopeDestructor;

		scopeDestructor += [&layers]()
		{
			FwpmFreeMemory0((void**)&layers);
		};

		for (UINT32 i = 0; i < layersReturned; ++i)
		{
			auto layer = *layers[i];

			if (callback(layer) == false)
			{
				return false;
			}
		}
	} while (LAYERS_REQUESTED == layersReturned);

	return true;
}

//static
bool ObjectEnumerator::ProviderContexts(
	std::shared_ptr<FilterEngine> engine,
	std::function<bool(const FWPM_PROVIDER_CONTEXT0&)> callback)
{
	HANDLE enumHandle = INVALID_HANDLE_VALUE;

	auto status = FwpmProviderContextCreateEnumHandle0(
		(*engine).session(),
		nullptr,
		&enumHandle
	);

	THROW_UNLESS(ERROR_SUCCESS, status, "Create enumeration context for WFP provider contexts")

	common::memory::ScopeDestructor scopeDestructor;

	scopeDestructor += [engine, &enumHandle]()
	{
		FwpmProviderContextDestroyEnumHandle0((*engine).session(), enumHandle);
	};

	FWPM_PROVIDER_CONTEXT0** contexts = nullptr;
	UINT32 contextsReturned = 0;

	static const UINT32 CONTEXTS_REQUESTED = 100;

	do
	{
		status = FwpmProviderContextEnum0(
			(*engine).session(),
			enumHandle,
			CONTEXTS_REQUESTED,
			&contexts,
			&contextsReturned
		);

		THROW_UNLESS(ERROR_SUCCESS, status, "Enumerate WFP provider contexts")

		if (0 == contextsReturned)
		{
			break;
		}

		#pragma warning(suppress: 4456)
		common::memory::ScopeDestructor scopeDestructor;

		scopeDestructor += [&contexts]()
		{
			FwpmFreeMemory0((void**)&contexts);
		};

		for (UINT32 i = 0; i < contextsReturned; ++i)
		{
			auto context = *contexts[i];

			if (callback(context) == false)
			{
				return false;
			}
		}
	} while (CONTEXTS_REQUESTED == contextsReturned);

	return true;
}

//static
bool ObjectEnumerator::Sublayers(
	std::shared_ptr<FilterEngine> engine,
	std::function<bool(const FWPM_SUBLAYER0&)> callback)
{
	HANDLE enumHandle = INVALID_HANDLE_VALUE;

	auto status = FwpmSubLayerCreateEnumHandle0(
		(*engine).session(),
		nullptr,
		&enumHandle
	);

	THROW_UNLESS(ERROR_SUCCESS, status, "Create enumeration context for WFP sublayers")

	common::memory::ScopeDestructor scopeDestructor;

	scopeDestructor += [engine, &enumHandle]()
	{
		FwpmSubLayerDestroyEnumHandle0((*engine).session(), enumHandle);
	};

	FWPM_SUBLAYER0** sublayers = nullptr;
	UINT32 sublayersReturned = 0;

	static const UINT32 SUBLAYERS_REQUESTED = 100;

	do
	{
		status = FwpmSubLayerEnum0(
			(*engine).session(),
			enumHandle,
			SUBLAYERS_REQUESTED,
			&sublayers,
			&sublayersReturned
		);

		THROW_UNLESS(ERROR_SUCCESS, status, "Enumerate WFP sublayers")

		if (0 == sublayersReturned)
		{
			break;
		}

		#pragma warning(suppress: 4456)
		common::memory::ScopeDestructor scopeDestructor;

		scopeDestructor += [&sublayers]()
		{
			FwpmFreeMemory0((void**)&sublayers);
		};

		for (UINT32 i = 0; i < sublayersReturned; ++i)
		{
			auto sublayer = *sublayers[i];

			if (callback(sublayer) == false)
			{
				return false;
			}
		}
	} while (SUBLAYERS_REQUESTED == sublayersReturned);

	return true;
}

} // namespace wfp
