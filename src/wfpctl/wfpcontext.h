#pragma once

#include "wfpctl.h"
#include "sessioncontroller.h"
#include "libwfp/ipaddr.h"
#include "libwfp/filterengine.h"
#include <cstdint>
#include <memory>

class WfpContext
{
public:

	WfpContext(uint32_t timeout);

	bool applyPolicyConnecting(const WfpctlSettings &settings, const wfp::IpAddr &relay);
	bool applyPolicyConnected(const WfpctlSettings &settings, const wfp::IpAddr &relay, const wfp::IpAddr &tunnel);

private:

	WfpContext(const WfpContext &);
	WfpContext &operator=(const WfpContext &);

	bool applyBaseConfiguration();

	std::unique_ptr<wfp::FilterEngine> m_engine;
	SessionController m_sessionController;
};
