#include "stdafx.h"
#include "libcommon/string.h"
#include "libwfp/filterengine.h"
#include "libwfp/objectinstaller.h"
#include "libwfp/sublayerbuilder.h"
#include "gtest/gtest.h"

TEST(IntegrationTest, AddSublayer)
{
	static const GUID SublayerKey = {
		0xa86fd1bf,
		0x21ce,
		0x497e,
		{ 0xa0, 0xbb, 0x17, 0x42, 0x5c, 0x88, 0x5c, 0x58 }
	};

	static const uint8_t ProviderData[] = { 0xab, 0xbb, 0xcc, 0xdd, 0xee };

	wfp::SublayerBuilder sublayerBuilder;

	sublayerBuilder
		.key(SublayerKey)
		.name(L"Mullvad VPN outbound engaged")
		.description(L"Bucket for outbound filters when client is engaged")
		.data(ProviderData, sizeof(ProviderData))
		.weight(MAXUINT16);

	auto engine = wfp::FilterEngine::DynamicSession();

	ASSERT_TRUE(wfp::ObjectInstaller::AddSublayer(*engine.get(), sublayerBuilder));
}
