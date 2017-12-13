#include "stdafx.h"
#include "gtest/gtest.h"
#include "libcommon/string.h"
#include <algorithm>

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

TEST(LibCommonString, FormatIpV4)
{
	ASSERT_EQ(common::string::FormatIpV4(0x7f000001), L"127.0.0.1");
}

TEST(LibCommonString, FormatIpV6)
{
	UINT8 ip[] =
	{
		0x10, 0x00, 0x20, 0x00, 0x30, 0x00, 0x40, 0x00,
		0x50, 0x00, 0x60, 0x00, 0x70, 0x00, 0x80, 0x00
	};

	ASSERT_EQ(common::string::FormatIpV6(ip), L"10:20:30:40:50:60:70:80");
}
