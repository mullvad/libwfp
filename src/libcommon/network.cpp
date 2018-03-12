#include "stdafx.h"
#include "network.h"

namespace common::network {

uint32_t MaskFromRoutingPrefix(uint8_t prefix)
{
	if (0 == prefix)
	{
		return 0;
	}

	return ~((uint32_t(1) << (32 - prefix)) - 1);
}

}