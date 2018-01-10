#pragma once

#include "conditionbuilder.h"
#include "filterbuilder.h"
#include "filterengine.h"

namespace wfp
{

class ObjectInstaller
{
public:

	static bool AddFilter(FilterEngine &engine, FilterBuilder &filterBuilder, ConditionBuilder &conditionBuilder);
};

}
