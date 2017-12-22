#pragma once

#include <vector>
#include <algorithm>
#include <memory>
#include "ifiltercondition.h"
#include <functional>
#include <fwpmu.h>

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
