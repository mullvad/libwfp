#pragma once

#include <guiddef.h>
#include <fwpmu.h>
#include <windows.h>
#include <functional>
#include <string>

namespace wfp
{

//
// Note: This builder is incomplete!
//
// Creating a self-contained object is fairly complex so this is currently not being attempted.
// Use the builder for creating almost-complete filters and complement them once built.
//
// More methods could be added but all fields were not needed at this time.
//

typedef std::function<bool(FWPM_FILTER0 &)> FilterSink;

class FilterBuilder
{
public:

	FilterBuilder();

	FilterBuilder &key(const GUID &key);
	FilterBuilder &name(const std::wstring &name);
	FilterBuilder &description(const std::wstring &description);

	FilterBuilder &persistent();
	FilterBuilder &boottime();
	FilterBuilder &disabled();

	FilterBuilder &provider(const GUID &provider);
	FilterBuilder &layer(const GUID &layer);
	FilterBuilder &sublayer(const GUID &sublayer);

	FilterBuilder &weight(UINT64 weight);

	FilterBuilder &block();
	FilterBuilder &permit();

	bool build(FilterSink sink);

private:

	FilterBuilder(const FilterBuilder &);
	FilterBuilder &operator=(const FilterBuilder &);

	FWPM_FILTER0 m_filter;

	std::wstring m_name;
	std::wstring m_description;
	GUID m_providerKey;
	UINT64 m_weight;
};

}
