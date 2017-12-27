#pragma once

#include "ifiltercondition.h"
#include <guiddef.h>
#include <fwpmu.h>
#include <algorithm>
#include <functional>
#include <memory>
#include <vector>

namespace wfp
{

typedef std::function<bool(FWPM_FILTER_CONDITION0 *, size_t)> ConditionSink;

class ConditionBuilder
{
public:

	ConditionBuilder(const GUID &layer);

	ConditionBuilder &add_condition(IFilterCondition *condition);

	bool build(ConditionSink sink) const;

private:

	GUID m_layer;
	std::vector<std::unique_ptr<IFilterCondition> > m_conditions;
};

}
