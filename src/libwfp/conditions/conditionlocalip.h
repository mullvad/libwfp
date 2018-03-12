#pragma once

#include "comparison.h"
#include "ifiltercondition.h"
#include "libwfp/ipaddress.h"
#include "libcommon/buffer.h"

namespace wfp::conditions {

class ConditionLocalIp : public IFilterCondition
{
	enum class AddressType
	{
		Ipv4,
		Ipv4Network,
		Ipv6,
		Ipv6Network
	};

public:

	ConditionLocalIp(const IpAddress &netnode, const IStrictComparison &comparison = CompareEq());
	ConditionLocalIp(const IpAddress &network, uint8_t prefix, const IStrictComparison &comparison = CompareEq());

	std::wstring toString() const override;
	const GUID &identifier() const override;
	const FWPM_FILTER_CONDITION0 &condition() const override;

private:

	IpAddress m_net;
	uint8_t m_prefix;

	AddressType m_addressType;

	ComparisonSpecification m_comparison;
	common::Buffer m_assembled;
};

}
