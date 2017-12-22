#pragma once

#include "filterengine.h"
#include "filterbuilder.h"
#include "conditionbuilder.h"

namespace wfp
{

class FilterInstaller
{
public:

	static bool Install(FilterEngine &engine, FilterBuilder &filterBuilder, ConditionBuilder &conditionBuilder);
};

}
