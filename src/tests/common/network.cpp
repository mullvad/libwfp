#include "stdafx.h"
#include "libcommon/network.h"
#include "gtest/gtest.h"

TEST(LibCommonNetwork, ConvertSlashEightPrefix)
{
	ASSERT_EQ(::common::network::MaskFromRoutingPrefix(8), 0xFF000000);
}

TEST(LibCommonNetwork, ConvertSlashTwelvePrefix)
{
	ASSERT_EQ(::common::network::MaskFromRoutingPrefix(12), 0xFFF00000);
}

TEST(LibCommonNetwork, ConvertSlashThirtyOnePrefix)
{
	ASSERT_EQ(::common::network::MaskFromRoutingPrefix(31), 0xFFFFFFFE);
}

TEST(LibCommonNetwork, ConvertSlashThirtyTwoPrefix)
{
	ASSERT_EQ(::common::network::MaskFromRoutingPrefix(32), 0xFFFFFFFF);
}

TEST(LibCommonNetwork, ConvertSlashZeroPrefix)
{
	ASSERT_EQ(::common::network::MaskFromRoutingPrefix(0), 0);
}
