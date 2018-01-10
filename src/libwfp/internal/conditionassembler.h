#pragma once

#include "libcommon/buffer.h"
#include <guiddef.h>
#include <fwpmu.h>

namespace wfp::internal {

class ConditionAssembler
{
public:

	static common::Buffer ByteBlob(const GUID &identifier, FWP_MATCH_TYPE matchType, const FWP_BYTE_BLOB &data);
	static common::Buffer Uint16(const GUID &identifier, FWP_MATCH_TYPE matchType, UINT16 value);
};

}
