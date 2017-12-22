#include "stdafx.h"
#include "conditionbuilder.h"
#include "layerconditions.h"
#include <stdexcept>

namespace wfp
{

ConditionBuilder::ConditionBuilder(const GUID &layer)
{
	memcpy(&m_layer, &layer, sizeof(layer));
}

ConditionBuilder &ConditionBuilder::add_condition(IFilterCondition *condition)
{
	if (false == LayerConditions::IsCompatible(m_layer, condition->identifier()))
	{
		throw std::runtime_error("Condition is not compatible with layer");
	}

	m_conditions.push_back(std::unique_ptr<IFilterCondition>(condition));

	return *this;
}

bool ConditionBuilder::build(ConditionSink sink) const
{
	auto conditions = std::make_unique<FWPM_FILTER_CONDITION0[]>(m_conditions.size());

	//
	// Individual conditions must be kept around for the lifetime of 'conditions'
	// This is because individual conditions manage data pointed by entries in 'conditions'
	//

	auto index = 0;

	for (const std::unique_ptr<IFilterCondition> &condition : m_conditions)
	{
		memcpy(&conditions[index++], &condition->condition(), sizeof(FWPM_FILTER_CONDITION0));
	}

	return sink(conditions.get(), m_conditions.size());
}

}
