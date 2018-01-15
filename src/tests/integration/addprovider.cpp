#include "stdafx.h"
#include "libwfp/providerbuilder.h"
#include "libwfp/filterengine.h"
#include "libwfp/objectinstaller.h"
#include "libcommon/string.h"
#include "gtest/gtest.h"


TEST(IntegrationTest, AddProvider)
{
	static const GUID ProviderKey = {
		0xa86fd1bf,
		0x21cd,
		0x497e,
		{ 0xa0, 0xbb, 0x17, 0x42, 0x5c, 0x88, 0x5c, 0x58 }
	};

	static const uint8_t ProviderData[] = { 0xaa, 0xbb, 0xcc, 0xdd, 0xee };

	wfp::ProviderBuilder providerBuilder;

	providerBuilder
		.key(ProviderKey)
		.name(L"Mullvad VPN")
		.description(L"Filters to support the various modes of operation of the Mullvad VPN App")
		.data(ProviderData, sizeof(ProviderData));

	auto engine = wfp::FilterEngine::DynamicSession();

	ASSERT_TRUE(wfp::ObjectInstaller::AddProvider(*engine.get(), providerBuilder));
}
