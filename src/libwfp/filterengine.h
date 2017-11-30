#pragma once

#include "stdafx.h"
#include <windows.h>
#include <fwpmtypes.h>

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
