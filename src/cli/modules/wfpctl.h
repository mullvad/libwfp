#pragma once

#include "module.h"
#include "cli/util.h"
#include "cli/iwfpctlcontext.h"
#include "cli/commands/wfpctl/policy.h"
#include "wfpctl/wfpctl.h"

namespace modules
{

class Wfpctl : public Module, public IWfpctlContext
{
public:

	Wfpctl(MessageSink messageSink)
		: Module(L"wfpctl", L"Exercise functionality provided by \"wfpctl.dll\".")
	{
		addCommand(std::make_unique<commands::wfpctl::Policy>(messageSink, this));
	}

	~Wfpctl()
	{
		deinitialize();
	}

	bool initialize() override
	{
		if (m_initialized)
		{
			return true;
		}

		return m_initialized = Wfpctl_Initialize();
	}

	bool deinitialize() override
	{
		if (!m_initialized)
		{
			return true;
		}

		auto status = Wfpctl_Deinitialize();
		m_initialized = !status;

		return status;
	}

private:

	bool m_initialized;
};

}
