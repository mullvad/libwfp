#pragma once

#include "libcommon/buffer.h"
#include "libwfp/ifiltercondition.h"
#include <memory>

namespace wfp {
namespace conditions {

class ConditionRemotePort : public IFilterCondition
{
public:

	ConditionRemotePort(UINT16 port);

	std::wstring toString() const override;
	const GUID &identifier() const override;
	const FWPM_FILTER_CONDITION0 &condition() const override;

private:

	UINT16 m_port;
	std::unique_ptr<common::Buffer> m_assembled;
};

}}
