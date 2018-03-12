#pragma once

#include "comparison.h"
#include "ifiltercondition.h"
#include "libcommon/buffer.h"

namespace wfp::conditions {

//
// TODO: There is a potential problem lurking here.
//
// The current condition is implemented using the field key FWPM_CONDITION_FLAGS.
//
// For a given filter, if there are multiple consecutive conditions with the same key,
// the conditions are evaluated using the OR operator.
//
// Realistically, this means that a given filter can only contain a single
// condition with the key FWPM_CONDITION_FLAGS.
//
class ConditionLoopback : public IFilterCondition
{
public:

	ConditionLoopback(const IStrictComparison &comparison = CompareEq());

	std::wstring toString() const override;
	const GUID &identifier() const override;
	const FWPM_FILTER_CONDITION0 &condition() const override;

private:

	ComparisonSpecification m_comparison;
	common::Buffer m_assembled;
};

}
