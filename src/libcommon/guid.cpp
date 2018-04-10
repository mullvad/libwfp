#include "stdafx.h"
#include "guid.h"
#include "error.h"
#include <rpc.h>

namespace common
{

// static
GUID Guid::Generate()
{
	UUID u;

	const auto status = UuidCreate(&u);

	THROW_UNLESS(RPC_S_OK, status, "Generate GUID");

	return u;
}

// static
GUID Guid::GenerateQuick()
{
	UUID u;

	const auto status = UuidCreateSequential(&u);

	THROW_UNLESS(RPC_S_OK, status, "Generate GUID");

	return u;
}

// static
bool Guid::Empty(const GUID &candidate)
{
	auto data = reinterpret_cast<const uint64_t *>(&candidate);
	return 0 == (*data | *(data + 1));
}

}
