#pragma once

#include "cli/commands/icommand.h"
#include "cli/util.h"
#include "cli/iwfpctlcontext.h"
#include "cli/subcommanddispatcher.h"
#include "libcommon/string.h"

namespace commands::wfpctl
{

class Policy : public ICommand
{
public:

	Policy(MessageSink messageSink, IWfpctlContext *context);

	std::wstring name() override;
	std::wstring description() override;

	void handleRequest(const std::vector<std::wstring> &arguments) override;

private:

	MessageSink m_messageSink;
	IWfpctlContext *m_context;

	SubcommandDispatcher m_dispatcher;

	using KeyValuePairs = common::string::KeyValuePairs;

	void processConnecting(const KeyValuePairs &arguments);
	void processConnected(const KeyValuePairs &arguments);
	void processReset();
};

}
