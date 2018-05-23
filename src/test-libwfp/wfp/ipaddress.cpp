#include "stdafx.h"
#include "gtest/gtest.h"
#include "libwfp/ipaddress.h"

using IpAddress = ::wfp::IpAddress;

TEST(LibWfpIpAddr, ConstructIpv4)
{
	static const wchar_t *literalString = L"127.0.0.1";

	IpAddress ip_from_literal(IpAddress::Literal({ 127, 0, 0, 1 }));
	IpAddress ip_from_string(literalString);
	IpAddress ip_from_raw(0x7f000001);

	ASSERT_TRUE(ip_from_literal.type() == IpAddress::Type::Ipv4);
	ASSERT_TRUE(ip_from_string.type() == IpAddress::Type::Ipv4);
	ASSERT_TRUE(ip_from_raw.type() == IpAddress::Type::Ipv4);

	ASSERT_STREQ(ip_from_string.toString().c_str(), literalString);
	ASSERT_STREQ(ip_from_literal.toString().c_str(), literalString);
	ASSERT_STREQ(ip_from_raw.toString().c_str(), literalString);
}

TEST(LibWfpIpAddr, ConstructIpv6)
{
	static const wchar_t *literalString = L"1000:1100:1200:1300:1400:1500:1600:1700";

	IpAddress ip_from_literal(IpAddress::Literal6({ 0x1000, 0x1100, 0x1200, 0x1300, 0x1400, 0x1500, 0x1600, 0x1700 }));
	IpAddress ip_from_string(literalString);

	const uint8_t raw[16] = { 0x10, 00, 0x11, 00, 0x12, 00, 0x13, 00, 0x14, 00, 0x15, 00, 0x16, 00, 0x17, 00 };

	FWP_BYTE_ARRAY16 netnode;
	memcpy(netnode.byteArray16, raw, sizeof(netnode.byteArray16));

	IpAddress ip_from_raw(netnode);

	ASSERT_TRUE(ip_from_literal.type() == IpAddress::Type::Ipv6);
	ASSERT_TRUE(ip_from_string.type() == IpAddress::Type::Ipv6);
	ASSERT_TRUE(ip_from_raw.type() == IpAddress::Type::Ipv6);

	ASSERT_STREQ(ip_from_string.toString().c_str(), literalString);
	ASSERT_STREQ(ip_from_literal.toString().c_str(), literalString);
	ASSERT_STREQ(ip_from_raw.toString().c_str(), literalString);
}
