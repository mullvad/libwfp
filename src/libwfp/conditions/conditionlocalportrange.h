#pragma once

#include "comparison.h"
#include "ifiltercondition.h"
#include "libcommon/buffer.h"

namespace wfp::conditions {

class ConditionLocalPortRange : public IFilterCondition
{
public:

	ConditionLocalPortRange(uint16_t firstPort, uint16_t lastPort, const IStrictComparison &comparison = CompareEq());

	std::wstring toString() const override;
	const GUID &identifier() const override;
	const FWPM_FILTER_CONDITION0 &condition() const override;

private:

	uint16_t m_firstPort;
	uint16_t m_lastPort;
	ComparisonSpecification m_comparison;

	common::Buffer m_assembled;
};

}
