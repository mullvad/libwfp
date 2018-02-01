#include "stdafx.h"
#include "propertydecorator.h"
#include "libwfp/objectexplorer.h"
#include "libcommon/string.h"
#include "inlineformatter.h"

PropertyDecorator::PropertyDecorator(std::shared_ptr<wfp::FilterEngine> engine)
	: m_engine(engine)
{
}

std::wstring PropertyDecorator::FilterDecoration(UINT64 id)
{
	std::wstring brief = L"[n/a]";

	wfp::ObjectExplorer::GetFilter(*m_engine, id, [&brief](const FWPM_FILTER0 &filter)
	{
		std::wstring name = (nullptr == filter.displayData.name ? L"n/a" :
			filter.displayData.name);

		std::wstring desc = (nullptr == filter.displayData.description ? L"n/a" :
			common::string::Summary(filter.displayData.description, 50));

		brief = (InlineFormatter() << L"[" << name << L", " << desc << L"]").str();

		return true;
	});

	return brief;
}

std::wstring PropertyDecorator::LayerDecoration(UINT16 id)
{
	std::wstring brief = L"[n/a]";

	wfp::ObjectExplorer::GetLayer(*m_engine, id, [&brief](const FWPM_LAYER0 &layer)
	{
		std::wstring name = (nullptr == layer.displayData.name ? L"n/a" :
			layer.displayData.name);

		std::wstring desc = (nullptr == layer.displayData.description ? L"n/a" :
			common::string::Summary(layer.displayData.description, 50));

		brief = (InlineFormatter() << L"[" << name << L", " << desc << L"]").str();

		return true;
	});

	return brief;
}
