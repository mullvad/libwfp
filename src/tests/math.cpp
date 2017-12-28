#include "stdafx.h"
#include "libcommon/math.h"
#include "gtest/gtest.h"

TEST(LibCommonMath, RoundPowerTwoAlreadyEvenMultiple)
{
	ASSERT_EQ(::common::math::RoundPowerTwo(sizeof(size_t), sizeof(size_t)), sizeof(size_t));
}

TEST(LibCommonMath, RoundPowerTwoToNextMultiple)
{
	ASSERT_EQ(::common::math::RoundPowerTwo(sizeof(size_t) + 1, sizeof(size_t)), sizeof(size_t) * 2);
}

TEST(LibCommonMath, RoundPowerTwoToNextMultipleAgain)
{
	ASSERT_EQ(::common::math::RoundPowerTwo((sizeof(size_t) * 2) - 1, sizeof(size_t)), sizeof(size_t) * 2);
}
