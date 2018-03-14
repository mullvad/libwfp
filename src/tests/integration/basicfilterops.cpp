#include "stdafx.h"
#include "libwfp/conditionbuilder.h"
#include "libwfp/conditions/conditionremoteport.h"
#include "libwfp/filterbuilder.h"
#include "libwfp/filterengine.h"
#include "libwfp/objectexplorer.h"
#include "libwfp/objectdeleter.h"
#include "libwfp/objectinstaller.h"
#include "gtest/gtest.h"
#include <memory>

using namespace ::wfp::conditions;

TEST(IntegrationTest, BasicFilterOps)
{
	static const GUID Layer = FWPM_LAYER_ALE_FLOW_ESTABLISHED_V4;

	wfp::ConditionBuilder conditionBuilder(Layer);
	conditionBuilder.add_condition(std::make_unique<ConditionRemotePort>(uint16_t(5555)));

	wfp::FilterBuilder filterBuilder;

	static const GUID FilterKey = {
		0xa86fd1bf,
		0x21cd,
		0x6432,
		{ 0xa0, 0xbb, 0x17, 0x42, 0x5c, 0x88, 0x5c, 0x58 }
	};

	filterBuilder
		.key(FilterKey)
		.name(L"BasicFilterOps")
		.description(L"Integration test: Block outgoing traffic with destination port 5555")
		.layer(Layer)
		.weight(MAXUINT64)
		.block();

	auto engine = wfp::FilterEngine::DynamicSession();

	ASSERT_TRUE(wfp::ObjectInstaller::AddFilter(*engine, filterBuilder, conditionBuilder));

	ASSERT_TRUE(wfp::ObjectExplorer::GetFilter(*engine, FilterKey, [](const FWPM_FILTER0 &filter)
	{
		return 0 == wcscmp(filter.displayData.name, L"BasicFilterOps");
	}));

	ASSERT_NO_THROW(wfp::ObjectDeleter::DeleteFilter(*engine, FilterKey));

	ASSERT_FALSE(wfp::ObjectExplorer::GetFilter(*engine, FilterKey, [](const FWPM_FILTER0 &)
	{
		return true;
	}));
}
