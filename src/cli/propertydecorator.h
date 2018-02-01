#pragma once

#include "ipropertydecorator.h"
#include "libwfp/filterengine.h"
#include <memory>

class PropertyDecorator : public IPropertyDecorator
{
public:

	PropertyDecorator(std::shared_ptr<wfp::FilterEngine> engine);

	std::wstring FilterDecoration(UINT64 id) override;
	std::wstring LayerDecoration(UINT16 id) override;

private:

	std::shared_ptr<wfp::FilterEngine> m_engine;
};
