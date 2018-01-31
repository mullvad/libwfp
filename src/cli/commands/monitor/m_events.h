#pragma once

#include "cli/commands/icommand.h"
#include "cli/util.h"
#include "libwfp/objectmonitor.h"
#include <memory>

namespace commands::monitor
{

class Events : public ICommand
{
public:

	Events(MessageSink messageSink);

	std::wstring name() override;
	std::wstring description() override;

	void handleRequest(const std::vector<std::wstring> &arguments) override;

private:

	MessageSink m_messageSink;
	std::unique_ptr<wfp::ObjectMonitor> m_objectMonitor;

	void eventCallback(const FWPM_NET_EVENT1 &event);
};

}
