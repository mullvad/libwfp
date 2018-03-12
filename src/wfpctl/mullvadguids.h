#pragma once
#include <guiddef.h>

class MullvadGuids
{
public:

	MullvadGuids() = delete;

	static const GUID &Provider();

	static const GUID &SublayerBlocking();
	static const GUID &SublayerAllowing();
};
