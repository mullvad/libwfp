#pragma once

#include "ifiltercondition.h"
#include "libcommon/buffer.h"
#include <memory>

namespace wfp::conditions {

class ConditionDirection : public IFilterCondition
{
	struct ctor_tag { explicit ctor_tag() = default; };

	enum class Direction
	{
		Inbound,
		Outbound
	};

public:

	// Public but non-invokable
	ConditionDirection(Direction direction, ctor_tag);

	static std::unique_ptr<ConditionDirection> Inbound();
	static std::unique_ptr<ConditionDirection> Outbound();

	std::wstring toString() const override;
	const GUID &identifier() const override;
	const FWPM_FILTER_CONDITION0 &condition() const override;

private:

	Direction m_direction;
	common::Buffer m_assembled;
};

}
