#include "stdafx.h"
#include "conditionbuilder.h"
#include "layerconditions.h"
#include <stdexcept>

using IFilterCondition = wfp::conditions::IFilterCondition;

namespace wfp
{

ConditionBuilder::ConditionBuilder(const GUID &layer)
{
	memcpy(&m_layer, &layer, sizeof(layer));
}

ConditionBuilder &ConditionBuilder::add_condition(IFilterCondition *condition)
{
	auto managedCondition = std::unique_ptr<IFilterCondition>(condition);

	if (false == LayerConditions::IsCompatible(m_layer, managedCondition->identifier()))
	{
		throw std::runtime_error("Condition is not compatible with layer");
	}

	m_conditions.insert(std::move(managedCondition));

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
