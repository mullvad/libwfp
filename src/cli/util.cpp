#include "stdafx.h"
#include "util.h"
#include "inlineformatter.h"
#include <string>

void PrettyPrintProperties(MessageSink messageSink, PrettyPrintOptions options, const PropertyList &properties)
{
	size_t longestName = 0;

	for (auto &property : properties)
	{
		longestName = max(longestName, property.name.size());
	}

	//
	// Format is:
	// indent, name, [separator], tab, [tab, ...]
	//

	const auto separator = std::wstring(options.useSeparator ? L":" : L"");

	auto insert = options.indent + longestName + separator.size();

	if (0 == (insert % 8))
	{
		insert += 8;
	}
	else
	{
		insert = ((insert / 8) + 1) * 8;
	}

	std::wstring indenter(options.indent, L' ');
	InlineFormatter f;

	for (auto &property : properties)
	{
		auto at = options.indent + property.name.size() + separator.size();
		auto distance = insert - at;
		auto tabs = (0 == (distance % 8) ? distance / 8 : (distance / 8) + 1);

		messageSink((f << indenter << property.name << separator
			<< std::wstring(tabs, L'\t') << property.value).str());
	}
}
