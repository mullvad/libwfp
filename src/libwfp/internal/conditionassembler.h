#pragma once

#include <memory>
#include <guiddef.h>
#include <fwpmu.h>
#include "libcommon/buffer.h"

namespace wfp {
namespace internal {

class ConditionAssembler
{
public:

	static std::unique_ptr<common::Buffer> ByteBlob(const GUID &identifier, FWP_MATCH_TYPE matchType, const FWP_BYTE_BLOB &data);
	static std::unique_ptr<common::Buffer> Uint16(const GUID &identifier, FWP_MATCH_TYPE matchType, UINT16 value);
};

}}
