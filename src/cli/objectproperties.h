#pragma once

#include "propertylist.h"
#include "ipropertydecorator.h"
#include <windows.h>
#include <fwpmu.h>

PropertyList SessionProperties(const FWPM_SESSION0 &session);
PropertyList ProviderProperties(const FWPM_PROVIDER0 &provider);
PropertyList EventProperties(const FWPM_NET_EVENT0 &event);
PropertyList EventProperties(const FWPM_NET_EVENT1 &event, IPropertyDecorator *decorator = nullptr);
PropertyList FilterProperties(const FWPM_FILTER0 &filter);
PropertyList LayerProperties(const FWPM_LAYER0 &layer);
PropertyList ProviderContextProperties(const FWPM_PROVIDER_CONTEXT0 &context);
PropertyList SublayerProperties(const FWPM_SUBLAYER0 &sublayer);
