#pragma once

#include "conditionbuilder.h"
#include "filterbuilder.h"
#include "filterengine.h"
#include "sublayerbuilder.h"

namespace wfp
{

class ObjectInstaller
{
public:

	static bool AddFilter(FilterEngine &engine, FilterBuilder &filterBuilder, ConditionBuilder &conditionBuilder);
	static bool AddSublayer(FilterEngine &engine, SublayerBuilder &sublayerBuilder);
};

}
