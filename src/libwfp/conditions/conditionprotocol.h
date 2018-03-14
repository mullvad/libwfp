#pragma once

#include "ifiltercondition.h"
#include "libcommon/buffer.h"
#include <memory>

namespace wfp::conditions {

class ConditionProtocol : public IFilterCondition
{
	struct ctor_tag { explicit ctor_tag() = default; };

	enum class Protocol
	{
		Tcp,
		Udp
	};

public:

	// Public but non-invokable
	ConditionProtocol(Protocol protocol, ctor_tag);

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
