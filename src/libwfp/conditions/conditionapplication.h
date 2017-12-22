#pragma once

#include "../ifiltercondition.h"
#include <memory>
#include "libcommon/buffer.h"

namespace wfp {
namespace conditions {

class ConditionApplication : public IFilterCondition
{
public:

	ConditionApplication(const std::wstring &application);

	std::wstring toString() const override;
	const GUID &identifier() const override;
	const FWPM_FILTER_CONDITION0 &condition() const override;

private:

	std::wstring m_application;
	std::unique_ptr<common::Buffer> m_assembled;
};

}
}
