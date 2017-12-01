// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "gtest/gtest.h"
#include "libcommon/string.h"
#include <algorithm>

int main(int argc, wchar_t **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(LibCommonString, JoinNothing)
{
	ASSERT_EQ(common::string::Join(std::vector<std::wstring>()), L"");
}

TEST(LibCommonString, JoinSingleElement)
{
	ASSERT_EQ(common::string::Join(std::vector<std::wstring>() = { L"foobar" }), L"foobar");
}

TEST(LibCommonString, JoinMultipleElements)
{
	ASSERT_EQ(common::string::Join(std::vector<std::wstring>() =
		{ L"foobar", L"foobear" }), L"foobar, foobear");
}

TEST(LibCommonString, FormatFlagsNoMatch)
{
	std::vector<std::pair<UINT32, std::wstring> > definitions =
	{
		std::make_pair(0x01, L"FLAG_ONE")
	};

	ASSERT_EQ(common::string::FormatFlags(definitions, (UINT32)0x02), L"[...]");
}

TEST(LibCommonString, FormatFlagsOneMatchOneFlag)
{
	std::vector<std::pair<UINT32, std::wstring> > definitions =
	{
		std::make_pair(0x01, L"FLAG_ONE")
	};

	ASSERT_EQ(common::string::FormatFlags(definitions, (UINT32)0x01), L"FLAG_ONE");
}

TEST(LibCommonString, FormatFlagsTwoMatchesTwoFlags)
{
	std::vector<std::pair<UINT32, std::wstring> > definitions =
	{
		std::make_pair(0x01, L"FLAG_ONE"),
		std::make_pair(0x02, L"FLAG_TWO")
	};

	ASSERT_EQ(common::string::FormatFlags(definitions, (UINT32)0x03), L"FLAG_ONE, FLAG_TWO");
}

TEST(LibCommonString, FormatFlagsOneMatchSeveralFlags)
{
	std::vector<std::pair<UINT32, std::wstring> > definitions =
	{
		std::make_pair(0x01, L"FLAG_ONE")
	};

	ASSERT_EQ(common::string::FormatFlags(definitions, (UINT32)0x03), L"FLAG_ONE, [...]");
}

TEST(LibCommonString, FormatFlagsOneMatchSeveralFlagsManyDefinitions)
{
	std::vector<std::pair<UINT32, std::wstring> > definitions =
	{
		std::make_pair(0x01, L"FLAG_ONE"),
		std::make_pair(0x04, L"FLAG_THREE"),
		std::make_pair(0x08, L"FLAG_FOUR")
	};

	ASSERT_EQ(common::string::FormatFlags(definitions, (UINT32)0x03), L"FLAG_ONE, [...]");
}

