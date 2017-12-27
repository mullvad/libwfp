#include "stdafx.h"
#include "filterinstaller.h"
#include "libcommon/error.h"
#include <guiddef.h>
#include <fwpmu.h>

namespace wfp
{

//static
bool FilterInstaller::Install(FilterEngine &engine, FilterBuilder &filterBuilder, ConditionBuilder &conditionBuilder)
{
	return conditionBuilder.build([&](FWPM_FILTER_CONDITION0 *conditions, size_t numConditions)
	{
		return filterBuilder.build([&](FWPM_FILTER0 &filter)
		{
			filter.filterCondition = conditions;
			filter.numFilterConditions = numConditions;

			auto status = FwpmFilterAdd0(
				engine.session(),
				&filter,
				nullptr,
				nullptr
			);

			THROW_UNLESS(ERROR_SUCCESS, status, "Register filter with BFE")

			return true;
		});
	});
}

}
