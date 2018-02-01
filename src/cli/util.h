#pragma once

#include <functional>
#include <memory>
#include <string>
#include "propertylist.h"
#include "libwfp/filterengine.h"

typedef std::function<void(const std::wstring &)> MessageSink;

struct PrettyPrintOptions
{
	size_t indent;
	bool useSeparator;
};

void PrettyPrintProperties(MessageSink, PrettyPrintOptions options, const PropertyList &properties);
