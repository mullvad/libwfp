// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "gtest/gtest.h"

int main(int argc, wchar_t **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	auto status = RUN_ALL_TESTS();

	return status;
}

