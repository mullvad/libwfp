#include "stdafx.h"
#include "conditionassembler.h"
#include "libcommon/binarycomposer.h"

using Buffer = ::common::Buffer;
using ConstBufferView = ::common::ConstBufferView;

#define MAKE_PTR(ptrbase, ptroffset, datatype) reinterpret_cast<datatype *>(reinterpret_cast<uint8_t *>(ptrbase) + ptroffset)

namespace wfp::internal {

//static
Buffer ConditionAssembler::ByteBlob(
	const GUID &identifier,
	FWP_MATCH_TYPE matchType,
	const FWP_BYTE_BLOB &blob)
{
	FWPM_FILTER_CONDITION0 definition;

	memcpy(&definition.fieldKey, &identifier, sizeof(identifier));
	definition.matchType = matchType;
	definition.conditionValue.type = FWP_BYTE_BLOB_TYPE;

	//
	// Goal, buffer with:
	//
	// FWPM_FILTER_CONDITION0
	// FWP_BYTE_BLOB
	// raw blob data
	//

	auto composer = ::common::BinaryComposer
	{
		ConstBufferView(&definition, sizeof(definition)),
		ConstBufferView(&blob, sizeof(blob)),
		ConstBufferView(blob.data, blob.size)
	};

	auto buffer = composer.buffer();
	auto offsets = composer.offsets();

	//
	// Correct stored pointers
	//

	auto finalDefinition = MAKE_PTR(buffer, offsets[0], FWPM_FILTER_CONDITION0);
	auto finalBlob = MAKE_PTR(buffer, offsets[1], FWP_BYTE_BLOB);
	auto finalData = MAKE_PTR(buffer, offsets[2], uint8_t);

	finalDefinition->conditionValue.byteBlob = finalBlob;
	finalBlob->data = finalData;

	return composer.acquire();
}

//static
Buffer ConditionAssembler::Uint16(
	const GUID &identifier,
	FWP_MATCH_TYPE matchType,
	UINT16 value)
{
	auto definition = std::make_unique<FWPM_FILTER_CONDITION0>();

	memcpy(&definition->fieldKey, &identifier, sizeof(identifier));
	definition->matchType = matchType;
	definition->conditionValue.type = FWP_UINT16;
	definition->conditionValue.uint16 = value;

	return Buffer(definition.release(), sizeof(FWPM_FILTER_CONDITION0));
}

}
