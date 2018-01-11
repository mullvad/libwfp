#include "stdafx.h"
#include "filterengine.h"
#include "libcommon/error.h"
#include <guiddef.h>
#include <fwpmu.h>
#include <windows.h>

namespace wfp
{

//static
std::unique_ptr<FilterEngine> FilterEngine::DynamicSession()
{
	return std::make_unique<FilterEngine>(true, ctor_tag{});
}

//static
std::unique_ptr<FilterEngine> FilterEngine::StandardSession()
{
	return std::make_unique<FilterEngine>(false, ctor_tag{});
}

FilterEngine::FilterEngine(bool dynamic, ctor_tag)
{
	FWPM_SESSION0 sessionInfo = { 0 };

	// Wait indefinitely for transaction lock to become available.
	sessionInfo.txnWaitTimeoutInMSec = INFINITE;

	if (dynamic)
	{
		sessionInfo.flags = FWPM_SESSION_FLAG_DYNAMIC;
	}

	new_internal(sessionInfo);
}

void FilterEngine::new_internal(const FWPM_SESSION0 &sessionInfo)
{
	HANDLE session = INVALID_HANDLE_VALUE;

	auto status = FwpmEngineOpen0(
		nullptr,
		RPC_C_AUTHN_DEFAULT,
		nullptr,
		&sessionInfo,
		&session
	);

	THROW_UNLESS(ERROR_SUCCESS, status, "Connect to WFP");

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

} // namespace wfp
