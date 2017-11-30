#include "stdafx.h"
#include "filterengine.h"
#include <windows.h>
#include <fwpmu.h>
#include <stdexcept>

FilterEngine::FilterEngine(bool dynamic)
{
	if (dynamic)
	{
		FWPM_SESSION0 sessionInfo = { 0 };
		sessionInfo.flags = FWPM_SESSION_FLAG_DYNAMIC;

		new_internal(&sessionInfo);
	}
	else
	{
		new_internal(nullptr);
	}
}

void FilterEngine::new_internal(const FWPM_SESSION0 *sessionInfo)
{
	HANDLE session = INVALID_HANDLE_VALUE;

	auto status = FwpmEngineOpen0(
		nullptr,
		RPC_C_AUTHN_DEFAULT,
		nullptr,
		sessionInfo,
		&session
	);

	if (ERROR_SUCCESS != status)
	{
		throw new std::runtime_error("Unable to connect to WFP");
	}

	m_session = session;
}

FilterEngine::~FilterEngine()
{
	FwpmEngineClose0(m_session);
}

HANDLE FilterEngine::session() const
{
	return m_session;
}
