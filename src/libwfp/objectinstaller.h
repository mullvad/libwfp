#pragma once

#include "conditionbuilder.h"
#include "filterbuilder.h"
#include "filterengine.h"
#include "providerbuilder.h"
#include "sublayerbuilder.h"

namespace wfp
{

class ObjectInstaller
{
public:

	static bool AddFilter(FilterEngine &engine, FilterBuilder &filterBuilder, ConditionBuilder &conditionBuilder);
	static bool AddProvider(FilterEngine &engine, ProviderBuilder &providerBuilder);
	static bool AddSublayer(FilterEngine &engine, SublayerBuilder &sublayerBuilder);
};

}
