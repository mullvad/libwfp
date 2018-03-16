#pragma once

#include "comparison.h"
#include "ifiltercondition.h"
#include "libwfp/ipaddress.h"
#include "libcommon/buffer.h"
#include <memory>

namespace wfp::conditions {

class ConditionIp : public IFilterCondition
{
	enum class AddressType
	{
		Ipv4,
		Ipv4Network,
		Ipv6,
		Ipv6Network
	};

	ConditionIp(bool local, const IpAddress &netnode, const IStrictComparison &comparison);
	ConditionIp(bool local, const IpAddress &network, uint8_t prefix, const IStrictComparison &comparison);

public:

	static std::unique_ptr<ConditionIp> Local(const IpAddress &netnode, const IStrictComparison &comparison = CompareEq());
	static std::unique_ptr<ConditionIp> Local(const IpAddress &netnode, uint8_t prefix, const IStrictComparison &comparison = CompareEq());
	static std::unique_ptr<ConditionIp> Remote(const IpAddress &netnode, const IStrictComparison &comparison = CompareEq());
	static std::unique_ptr<ConditionIp> Remote(const IpAddress &netnode, uint8_t prefix, const IStrictComparison &comparison = CompareEq());

	std::wstring toString() const override;
	const GUID &identifier() const override;
	const FWPM_FILTER_CONDITION0 &condition() const override;

private:

	bool m_local;

	IpAddress m_net;
	uint8_t m_prefix;

	AddressType m_addressType;

	ComparisonSpecification m_comparison;
	common::Buffer m_assembled;
};

}
