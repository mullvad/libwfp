#include "stdafx.h"
#include "filters.h"
#include "cli/objectproperties.h"
#include "cli/filterengineprovider.h"
#include "libwfp/objectenumerator.h"

namespace commands::list
{

Filters::Filters(MessageSink messageSink)
	: m_messageSink(messageSink)
{
}

std::wstring Filters::name()
{
	return L"filters";

}

std::wstring Filters::description()
{
	return L"Provides a listing of all filters in the system.";
}

void Filters::handleRequest(const std::vector<std::wstring> &arguments)
{
	if (false == arguments.empty())
	{
		throw std::runtime_error("Unsupported argument(s). Cannot complete request.");
	}

	PrettyPrintOptions options;

	options.indent = 2;
	options.useSeparator = true;

	wfp::ObjectEnumerator::Filters(*FilterEngineProvider::Instance().get(), [&](const FWPM_FILTER0 &filter)
	{
		m_messageSink(L"Filter");

		PrettyPrintProperties(m_messageSink, options, FilterProperties(filter));

		return true;
	});
}

}
