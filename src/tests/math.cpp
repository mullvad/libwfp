#include "stdafx.h"
#include "libcommon/math.h"
#include "gtest/gtest.h"

TEST(LibCommonMath, RoundNativeAlreadyEvenMultiple)
{
	ASSERT_EQ(common::math::RoundNative(sizeof(size_t)), sizeof(size_t));
}

TEST(LibCommonMath, RoundNativeToNextMultiple)
{
	ASSERT_EQ(common::math::RoundNative(sizeof(size_t) + 1), sizeof(size_t) * 2);
}

TEST(LibCommonMath, RoundNativeToNextMultipleAgain)
{
	ASSERT_EQ(common::math::RoundNative((sizeof(size_t) * 2) - 1), sizeof(size_t) * 2);
}
