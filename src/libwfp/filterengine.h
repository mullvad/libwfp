#pragma once

#include "stdafx.h"
#include <fwpmtypes.h>
#include <windows.h>
#include <memory>

namespace wfp
{

class FilterEngine
{
	struct ctor_tag { explicit ctor_tag() = default; };

public:

	static std::unique_ptr<FilterEngine> DynamicSession();
	static std::unique_ptr<FilterEngine> StandardSession();

	// Public but non-invokable
	FilterEngine(bool dynamic, ctor_tag);

	~FilterEngine();

	HANDLE session() const;

private:

	FilterEngine(const FilterEngine &);
	FilterEngine &operator=(const FilterEngine &);

	void new_internal(const FWPM_SESSION0 &sessionInfo);

	HANDLE m_session;
};

} // namespace wfp
