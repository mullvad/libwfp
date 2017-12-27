#include "stdafx.h"
#include "gtest/gtest.h"
#include "libwfp/layerconditions.h"
#include <guiddef.h>
#include <fwpmu.h>

TEST(LibWfpLayerConditions, IsCompatibleWithCompatibleCondition)
{
	ASSERT_TRUE(wfp::LayerConditions::IsCompatible(FWPM_LAYER_OUTBOUND_TRANSPORT_V6, FWPM_CONDITION_IP_LOCAL_ADDRESS_TYPE));

	// Match last item in defined condition array, to ensure no off-by-one issues
	ASSERT_TRUE(wfp::LayerConditions::IsCompatible(FWPM_LAYER_OUTBOUND_TRANSPORT_V6, FWPM_CONDITION_CURRENT_PROFILE_ID));
}

TEST(LibWfpLayerConditions, IsNotCompatibleWithIncompatibleCondition)
{
	ASSERT_FALSE(wfp::LayerConditions::IsCompatible(FWPM_LAYER_OUTBOUND_TRANSPORT_V6, FWPM_CONDITION_DIRECTION));
}

TEST(LibWfpLayerConditions, IsCompatibleWithInvalidLayerThrows)
{
	static const GUID InvalidLayer = {
		0xa86fd1bf,
		0x21cd,
		0x497e,
		{ 0xa0, 0xbb, 0x17, 0x42, 0x5c, 0x88, 0x5c, 0x58 }
	};

	ASSERT_THROW(wfp::LayerConditions::IsCompatible(InvalidLayer, FWPM_CONDITION_DIRECTION), std::runtime_error);
}

