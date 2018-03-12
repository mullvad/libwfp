#pragma once

#include "ifiltercondition.h"
#include "libcommon/buffer.h"

namespace wfp::conditions {

class ConditionDirection : public IFilterCondition
{
	enum class Direction
	{
		Inbound,
		Outbound
	};

	ConditionDirection(Direction direction);

public:

	static ConditionDirection *Inbound();
	static ConditionDirection *Outbound();

	std::wstring toString() const override;
	const GUID &identifier() const override;
	const FWPM_FILTER_CONDITION0 &condition() const override;

private:

	Direction m_direction;
	common::Buffer m_assembled;
};

}
