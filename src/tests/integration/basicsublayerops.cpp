#include "stdafx.h"
#include "libwfp/filterengine.h"
#include "libwfp/objectexplorer.h"
#include "libwfp/objectdeleter.h"
#include "libwfp/objectinstaller.h"
#include "libwfp/sublayerbuilder.h"
#include "gtest/gtest.h"

TEST(IntegrationTest, BasicSublayerOps)
{
	static const GUID SublayerKey = {
		0xa86fd1bf,
		0x21d0,
		0x6433,
		{ 0xa0, 0xbb, 0x17, 0x42, 0x5c, 0x88, 0x5c, 0x58 }
	};

	// Context data is always referred to as "provider data".
	static const uint8_t ProviderData[]{
		0xaa, 0xbb, 0xcc, 0xdd, 0xee
	};

	wfp::SublayerBuilder sublayerBuilder;

	sublayerBuilder
		.key(SublayerKey)
		.name(L"BasicSublayerOps")
		.description(L"Integration test: Dummy sublayer")
		.data(ProviderData, sizeof(ProviderData));

	auto engine = wfp::FilterEngine::DynamicSession();

	ASSERT_TRUE(wfp::ObjectInstaller::AddSublayer(*engine, sublayerBuilder));

	ASSERT_TRUE(wfp::ObjectExplorer::GetSublayer(*engine, SublayerKey, [](const FWPM_SUBLAYER0 &sublayer)
	{
		return 0 == wcscmp(sublayer.displayData.name, L"BasicSublayerOps")
			&& sizeof(ProviderData) == sublayer.providerData.size
			&& 0 == memcmp(sublayer.providerData.data, ProviderData, sizeof(ProviderData));
	}));

	ASSERT_NO_THROW(wfp::ObjectDeleter::DeleteSublayer(*engine, SublayerKey));

	ASSERT_FALSE(wfp::ObjectExplorer::GetSublayer(*engine, SublayerKey, [](const FWPM_SUBLAYER0 &)
	{
		return true;
	}));
}
