#include "stdafx.h"
#include "wfpcontext.h"
#include "mullvadobjects.h"
#include "libwfp/transaction.h"
#include <functional>
#include <stdexcept>

WfpContext::WfpContext(uint32_t timeout)
{
	m_engine = wfp::FilterEngine::DynamicSession(timeout);

	//
	// At present, it's simple to add any structural objects needed in WFP
	// at this point.
	//
	// This should be re-evaluated in the future in case new policies
	// require unique structural objects, or require otherwise complicated configuration
	//

	auto success = wfp::Transaction::Execute(*m_engine,
		std::bind(&WfpContext::applyBaseConfiguration, this));

	if (!success)
	{
		throw std::runtime_error("Failed to apply base configuration in BFE.");
	}
}

bool WfpContext::applyPolicyConnecting(const WfpctlSettings &settings, const wfp::IpAddr &relay)
{
	m_sessionController.resetFilters(*m_engine);

	return false;
}

bool WfpContext::applyPolicyConnected(const WfpctlSettings &settings, const wfp::IpAddr &relay, const wfp::IpAddr &tunnel)
{
	m_sessionController.resetFilters(*m_engine);

	return false;
}

bool WfpContext::applyBaseConfiguration()
{
	return m_sessionController.addProvider(*m_engine, *MullvadObjects::Provider())
		&& m_sessionController.addSublayer(*m_engine, *MullvadObjects::SublayerBlocking())
		&& m_sessionController.addSublayer(*m_engine, *MullvadObjects::SublayerAllowing());
}
