#include "stdafx.h"
#include <sstream>
#include "conditionl2flags.h"

namespace wfp::conditions {

  ConditionL2Flags::ConditionL2Flags() {
	    
	  // Condition: Request must be targeting the TUN interface
	  cond.fieldKey = FWPM_CONDITION_L2_FLAGS;
	  cond.matchType = FWP_MATCH_EQUAL;
	  cond.conditionValue.type = FWP_UINT32;
	  cond.conditionValue.uint32 = FWP_CONDITION_L2_IS_VM2VM;
  }

  std::wstring ConditionL2Flags::toString() const {
	  std::wstringstream ss;
	  ss << L"TODO L2 condition flags";
	  return ss.str();
  }
  const GUID &ConditionL2Flags::identifier() const {
    return FWPM_CONDITION_L2_FLAGS;
  }

  const FWPM_FILTER_CONDITION0 &ConditionL2Flags::condition() const
	{
		return cond;
	}

} // namespace wfp::conditions
