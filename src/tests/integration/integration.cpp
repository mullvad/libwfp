#include "stdafx.h"
#include "gtest/gtest.h"
#include "libwfp/filterbuilder.h"
#include "libwfp/conditionbuilder.h"
#include "libwfp/conditions/conditionapplication.h"
#include "libwfp/conditions/conditionremoteport.h"
#include "libwfp/filterengine.h"
#include "libwfp/filterinstaller.h"
#include "libcommon/string.h"
#include "../ncat.h"

using namespace ::wfp::conditions;

TEST(IntegrationTest, BlockNcatOutgoingPort80)
{
	static const unsigned short PORT = 80;
	static const GUID Layer = FWPM_LAYER_ALE_FLOW_ESTABLISHED_V4;

	wfp::ConditionBuilder conditionBuilder(Layer);

	conditionBuilder.add_condition(new ConditionApplication(Ncat::PATH));
	conditionBuilder.add_condition(new ConditionRemotePort(PORT));

	wfp::FilterBuilder filterBuilder;

	filterBuilder
		.name(L"Block Ncat outgoing traffic with destination port 80")
		.description(L"Integration test")
		.layer(Layer)
		.weight(MAXUINT64)
		.block();

	auto engine = wfp::FilterEngine::DynamicSession();

	ASSERT_TRUE(wfp::FilterInstaller::Install(*engine.get(), filterBuilder, conditionBuilder));

	Ncat ncat(L"-4 www.mullvad.net 80");

	// Verify error message was printed
	ASSERT_TRUE(common::string::BeginsWith(ncat.output(), std::string("Ncat:")));

	// Verify return code
	ASSERT_EQ(ncat.returnCode(), Ncat::ReturnCode::Error);
}
