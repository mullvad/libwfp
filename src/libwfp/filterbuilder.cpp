#include "stdafx.h"
#include "filterbuilder.h"
#include <memory.h>

namespace wfp
{

FilterBuilder::FilterBuilder()
{
	memset(&m_filter, 0, sizeof(m_filter));
	block();
}

FilterBuilder &FilterBuilder::key(const GUID &key)
{
	memcpy(&m_filter.filterKey, &key, sizeof(m_filter.filterKey));
	return *this;
}

FilterBuilder &FilterBuilder::name(const std::wstring &name)
{
	m_name = name;
	m_filter.displayData.name = const_cast<wchar_t *>(m_name.c_str());

	return *this;
}

FilterBuilder &FilterBuilder::description(const std::wstring &description)
{
	m_description = description;
	m_filter.displayData.description = const_cast<wchar_t *>(m_description.c_str());

	return *this;
}

FilterBuilder &FilterBuilder::persistent()
{
	m_filter.flags |= FWPM_FILTER_FLAG_PERSISTENT;
	return *this;
}

FilterBuilder &FilterBuilder::boottime()
{
	m_filter.flags |= FWPM_FILTER_FLAG_BOOTTIME;
	return *this;
}


FilterBuilder &FilterBuilder::disabled()
{
	m_filter.flags |= FWPM_FILTER_FLAG_DISABLED;
	return *this;
}

FilterBuilder &FilterBuilder::provider(const GUID &provider)
{
	memcpy(&m_providerKey, &provider, sizeof(m_providerKey));
	m_filter.providerKey = &m_providerKey;

	return *this;
}

FilterBuilder &FilterBuilder::layer(const GUID &layer)
{
	memcpy(&m_filter.layerKey, &layer, sizeof(m_filter.layerKey));
	return *this;
}

FilterBuilder &FilterBuilder::sublayer(const GUID &sublayer)
{
	memcpy(&m_filter.subLayerKey, &sublayer, sizeof(m_filter.subLayerKey));
	return *this;
}

FilterBuilder &FilterBuilder::weight(UINT64 weight)
{
	m_weight = weight;

	m_filter.weight.type = FWP_UINT64;
	m_filter.weight.uint64 = &m_weight;

	return *this;
}

FilterBuilder &FilterBuilder::block()
{
	m_filter.action.type = FWP_ACTION_BLOCK;
	return *this;
}

FilterBuilder &FilterBuilder::permit()
{
	m_filter.action.type = FWP_ACTION_PERMIT;
	return *this;
}

bool FilterBuilder::build(FilterSink sink)
{
	return sink(m_filter);
}

}
