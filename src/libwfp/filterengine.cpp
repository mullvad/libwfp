#include "stdafx.h"
#include "filterengine.h"
#include <libcommon/error.h>
#include <guiddef.h>
#include <fwpmu.h>
#include <windows.h>

namespace wfp
{

FilterEngine::FilterEngine(bool dynamic, uint32_t *timeout)
	: m_ownsSession(true)
{
	FWPM_SESSION0 sessionInfo = { 0 };

	// A timeout of 0 ms is interpreted by WFP to mean "system default timeout".
	sessionInfo.txnWaitTimeoutInMSec = (nullptr == timeout ? 0 : *timeout);

	if (dynamic)
	{
		sessionInfo.flags = FWPM_SESSION_FLAG_DYNAMIC;
	}

	HANDLE session = INVALID_HANDLE_VALUE;

	auto status = FwpmEngineOpen0(
		nullptr,
		RPC_C_AUTHN_DEFAULT,
		nullptr,
		&sessionInfo,
		&session
	);

	if (ERROR_SUCCESS != status)
	{
		THROW_WINDOWS_ERROR(status, "Connect to WFP");
	}

	m_session = session;
}

FilterEngine::FilterEngine(HANDLE session)
	: m_session(session)
	, m_ownsSession(false)
{
	if (nullptr == session || INVALID_HANDLE_VALUE == session)
	{
		THROW_ERROR("Invalid argument: session");
	}
}

//static
std::unique_ptr<FilterEngine> FilterEngine::DynamicSession()
{
	return std::unique_ptr<FilterEngine>(new FilterEngine(true, nullptr));
}

//static
std::unique_ptr<FilterEngine> FilterEngine::StandardSession()
{
	return std::unique_ptr<FilterEngine>(new FilterEngine(false, nullptr));
}

//static
std::unique_ptr<FilterEngine> FilterEngine::DynamicSession(uint32_t timeout)
{
	return std::unique_ptr<FilterEngine>(new FilterEngine(true, &timeout));
}

//static
std::unique_ptr<FilterEngine> FilterEngine::StandardSession(uint32_t timeout)
{
	return std::unique_ptr<FilterEngine>(new FilterEngine(false, &timeout));
}

//static
std::unique_ptr<FilterEngine> FilterEngine::BorrowedSession(HANDLE session)
{
	return std::unique_ptr<FilterEngine>(new FilterEngine(session));
}

FilterEngine::~FilterEngine()
{
	if (m_ownsSession)
	{
		FwpmEngineClose0(m_session);
	}
}

HANDLE FilterEngine::session() const
{
	return m_session;
}

} // namespace wfp
