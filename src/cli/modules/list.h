#pragma once

#include "module.h"
#include "cli/util.h"
#include "cli/commands/list/sessions.h"

namespace modules
{

class List : public Module
{
public:

	List(MessageSink messageSink)
		: Module(L"list", L"List various objects in the WFP universe.")
	{
		addCommand(std::make_unique<commands::list::Sessions>(messageSink));
	}
};

}
