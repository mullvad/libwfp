#pragma once

struct IWfpctlContext
{
	virtual bool initialize() = 0;
	virtual bool deinitialize() = 0;
};
