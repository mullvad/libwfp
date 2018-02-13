#pragma once

#include "libwfp/conditionbuilder.h"
#include "libwfp/filterbuilder.h"
#include "libwfp/filterengine.h"
#include "libwfp/providerbuilder.h"
#include "libwfp/sublayerbuilder.h"
#include <vector>

class SessionController
{
public:

	SessionController() = default;

	bool addProvider(wfp::FilterEngine &engine, wfp::ProviderBuilder &providerBuilder);
	bool addSublayer(wfp::FilterEngine &engine, wfp::SublayerBuilder &sublayerBuilder);
	bool addFilter(wfp::FilterEngine &engine, wfp::FilterBuilder &filterBuilder, wfp::ConditionBuilder &conditionBuilder);

	//
	// This is the same as destroying and recreating the session
	// but can be completed inside a transaction
	//
	void resetSession(wfp::FilterEngine &engine);

	//
	// Only reset filters, leaving all other objects that have been
	// created in the current session
	//
	void resetFilters(wfp::FilterEngine &engine);

private:

	SessionController(const SessionController &);
	SessionController &operator=(const SessionController &);

	void resetProviders(wfp::FilterEngine &engine);
	void resetSublayers(wfp::FilterEngine &engine);

	std::vector<GUID> m_providers;
	std::vector<GUID> m_sublayers;
	std::vector<UINT64> m_filters;
};
