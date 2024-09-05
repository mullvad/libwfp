#pragma once

#include "ifiltercondition.h"

namespace wfp::conditions {

class ConditionL2Flags : public IFilterCondition
{
public:
	ConditionL2Flags();

	std::wstring toString() const override;
	const GUID &identifier() const override;
	const FWPM_FILTER_CONDITION0 &condition() const override;

	
  private:
	  FWPM_FILTER_CONDITION0 cond;
};

}
