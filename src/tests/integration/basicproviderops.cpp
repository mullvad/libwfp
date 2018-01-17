#include "stdafx.h"
#include "libwfp/filterengine.h"
#include "libwfp/objectexplorer.h"
#include "libwfp/objectdeleter.h"
#include "libwfp/objectinstaller.h"
#include "libwfp/providerbuilder.h"
#include "gtest/gtest.h"

TEST(IntegrationTest, BasicProviderOps)
{
	static const GUID ProviderKey = {
		0xa86fd1bf,
		0x21d0,
		0x6432,
		{ 0xa0, 0xbb, 0x17, 0x42, 0x5c, 0x88, 0x5c, 0x58 }
	};

	static const uint8_t ProviderData[] {
		0xaa, 0xbb, 0xcc, 0xdd, 0xee
	};

	wfp::ProviderBuilder providerBuilder;

	providerBuilder
		.key(ProviderKey)
		.name(L"BasicProviderOps")
		.description(L"Integration test: Dummy provider")
		.data(ProviderData, sizeof(ProviderData));

	auto engine = wfp::FilterEngine::DynamicSession();

	ASSERT_TRUE(wfp::ObjectInstaller::AddProvider(*engine, providerBuilder));

	ASSERT_TRUE(wfp::ObjectExplorer::GetProvider(*engine, ProviderKey, [](const FWPM_PROVIDER0 &provider)
	{
		return 0 == wcscmp(provider.displayData.name, L"BasicProviderOps")
			&& sizeof(ProviderData) == provider.providerData.size
			&& 0 == memcmp(provider.providerData.data, ProviderData, sizeof(ProviderData));
	}));

	ASSERT_NO_THROW(wfp::ObjectDeleter::DeleteProvider(*engine, ProviderKey));

	ASSERT_FALSE(wfp::ObjectExplorer::GetProvider(*engine, ProviderKey, [](const FWPM_PROVIDER0 &)
	{
		return true;
	}));
}
