#pragma once

#include "libcommon/buffer.h"
#include "libwfp/ifiltercondition.h"

namespace wfp::conditions {

class ConditionApplication : public IFilterCondition
{
public:

	ConditionApplication(const std::wstring &application);

	std::wstring toString() const override;
	const GUID &identifier() const override;
	const FWPM_FILTER_CONDITION0 &condition() const override;

private:

	std::wstring m_application;
	common::Buffer m_assembled;
};

}
