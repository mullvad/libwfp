#pragma once

#include "comparison.h"
#include "ifiltercondition.h"
#include "libcommon/buffer.h"

namespace wfp::conditions {

class ConditionRemotePort : public IFilterCondition
{
public:

	ConditionRemotePort(uint16_t port, const IRelaxedComparison &comparison = CompareEq());

	std::wstring toString() const override;
	const GUID &identifier() const override;
	const FWPM_FILTER_CONDITION0 &condition() const override;

private:

	uint16_t m_port;
	ComparisonSpecification m_comparison;

	common::Buffer m_assembled;
};

}
