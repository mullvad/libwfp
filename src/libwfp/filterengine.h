#pragma once

#include "stdafx.h"
#include <windows.h>
#include <fwpmtypes.h>

namespace wfp
{

class FilterEngine
{
	FilterEngine(const FilterEngine &);
	FilterEngine &operator=(const FilterEngine &);

	void new_internal(const FWPM_SESSION0 *sessionInfo);

	HANDLE m_session;

public:

	FilterEngine(bool dynamic);
	~FilterEngine();

	HANDLE session() const;
};

} // namespace wfp
