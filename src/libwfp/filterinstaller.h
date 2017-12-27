#pragma once

#include "conditionbuilder.h"
#include "filterbuilder.h"
#include "filterengine.h"

namespace wfp
{

class FilterInstaller
{
public:

	static bool Install(FilterEngine &engine, FilterBuilder &filterBuilder, ConditionBuilder &conditionBuilder);
};

}
