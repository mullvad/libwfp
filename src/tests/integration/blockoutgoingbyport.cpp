#include "stdafx.h"
#include "libwfp/conditionbuilder.h"
#include "libwfp/conditions/conditionapplication.h"
#include "libwfp/conditions/conditionport.h"
#include "libwfp/filterbuilder.h"
#include "libwfp/filterengine.h"
#include "libwfp/objectinstaller.h"
#include "libwfp/providerbuilder.h"
#include "libwfp/sublayerbuilder.h"
#include "libcommon/string.h"
#include "tests/ncat.h"
#include "gtest/gtest.h"
#include <memory>

using namespace ::wfp::conditions;

TEST(IntegrationTest, BlockOutgoingByPort)
{
	static const GUID ProviderKey = {
		0xa86fd1bf,
		0x21d0,
		0x0000,
		{ 0xa0, 0xbb, 0x17, 0x42, 0x5c, 0x88, 0x5c, 0x58 }
	};

	static const uint8_t ProviderData[]{
		0xaa, 0xbb, 0xcc, 0xdd, 0xee
	};

	wfp::ProviderBuilder providerBuilder;

	providerBuilder
		.key(ProviderKey)
		.name(L"BlockOutgoingByPort")
		.description(L"Integration test: Block Ncat outgoing traffic with destination port 80")
		.data(ProviderData, sizeof(ProviderData));

	auto engine = wfp::FilterEngine::DynamicSession();

	ASSERT_TRUE(wfp::ObjectInstaller::AddProvider(*engine, providerBuilder));

	static const GUID SublayerKey = {
		0xa86fd1bf,
		0x21d0,
		0x0001,
		{ 0xa0, 0xbb, 0x17, 0x42, 0x5c, 0x88, 0x5c, 0x58 }
	};

	// Context data is always referred to as "provider data".
	static const uint8_t SublayerProviderData[]{
		0xaa, 0xbb, 0xcc, 0xdd, 0xef
	};

	wfp::SublayerBuilder sublayerBuilder;

	sublayerBuilder
		.key(SublayerKey)
		.name(L"BlockOutgoingByPort")
		.description(L"Integration test: Block Ncat outgoing traffic with destination port 80")
		.provider(ProviderKey)
		.data(SublayerProviderData, sizeof(SublayerProviderData))
		.weight(MAXUINT16);

	ASSERT_TRUE(wfp::ObjectInstaller::AddSublayer(*engine, sublayerBuilder));

	static const unsigned short PORT = 80;
	static const GUID LayerKey = FWPM_LAYER_ALE_FLOW_ESTABLISHED_V4;

	static const GUID FilterKey = {
		0xa86fd1bf,
		0x21d0,
		0x0002,
		{ 0xa0, 0xbb, 0x17, 0x42, 0x5c, 0x88, 0x5c, 0x58 }
	};

	wfp::ConditionBuilder conditionBuilder(LayerKey);

	conditionBuilder.add_condition(std::make_unique<ConditionApplication>(Ncat::PATH));
	conditionBuilder.add_condition(ConditionPort::Remote(PORT));

	wfp::FilterBuilder filterBuilder;

	filterBuilder
		.key(FilterKey)
		.name(L"BlockOutgoingByPort")
		.description(L"Integration test: Block Ncat outgoing traffic with destination port 80")
		.provider(ProviderKey)
		.layer(LayerKey)
		.sublayer(SublayerKey)
		.weight(MAXUINT64)
		.block();

	ASSERT_TRUE(wfp::ObjectInstaller::AddFilter(*engine, filterBuilder, conditionBuilder));

	Ncat ncat(L"-4 www.mullvad.net 80");

	// Verify error message was printed
	ASSERT_TRUE(common::string::BeginsWith(ncat.output(), std::string("Ncat:")));

	// Verify return code
	ASSERT_EQ(ncat.returnCode(), Ncat::ReturnCode::Error);
}
