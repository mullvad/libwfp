#pragma once

#include "ifiltercondition.h"
#include "libcommon/buffer.h"
#include <memory>

namespace wfp::conditions {

class ConditionProtocol : public IFilterCondition
{
	enum class Protocol
	{
		Tcp,
		Udp
	};

	ConditionProtocol(Protocol protocol);

public:

	static std::unique_ptr<ConditionProtocol> Tcp();
	static std::unique_ptr<ConditionProtocol> Udp();

	std::wstring toString() const override;
	const GUID &identifier() const override;
	const FWPM_FILTER_CONDITION0 &condition() const override;

private:

	Protocol m_protocol;
	common::Buffer m_assembled;
};

}
