#include "stdafx.h"
#include "objectproperties.h"
#include "inlineformatter.h"
#include "propertylist.h"
#include "libcommon/string.h"
#include <string>
#include <utility>
#include <vector>

namespace detail
{

std::wstring SessionFlags(UINT32 flags)
{
	std::vector<std::pair<UINT32, std::wstring> > definitions =
	{
		std::make_pair(FWPM_SESSION_FLAG_DYNAMIC, L"FWPM_SESSION_FLAG_DYNAMIC"),
		std::make_pair(FWPM_SESSION_FLAG_RESERVED, L"FWPM_SESSION_FLAG_RESERVED")
	};

	return common::string::FormatFlags(definitions, flags);
}

std::wstring ProviderFlags(UINT32 flags)
{
	std::vector<std::pair<UINT32, std::wstring> > definitions =
	{
		std::make_pair(FWPM_PROVIDER_FLAG_PERSISTENT, L"FWPM_PROVIDER_FLAG_PERSISTENT"),
		std::make_pair(FWPM_PROVIDER_FLAG_DISABLED, L"FWPM_PROVIDER_FLAG_DISABLED")
	};

	return common::string::FormatFlags(definitions, flags);
}

std::wstring FormatIpProtocol(UINT8 protocol)
{
	switch (protocol)
	{
	case 0:		return L"IPPROTO_HOPOPTS";
	case 1:		return L"IPPROTO_ICMP";
	case 2:		return L"IPPROTO_IGMP";
	case 3:		return L"IPPROTO_GGP";
	case 4:		return L"IPPROTO_IPV4";
	case 5:		return L"IPPROTO_ST";
	case 6:		return L"IPPROTO_TCP";
	case 7:		return L"IPPROTO_CBT";
	case 8:		return L"IPPROTO_EGP";
	case 9:		return L"IPPROTO_IGP";
	case 12:	return L"IPPROTO_PUP";
	case 17:	return L"IPPROTO_UDP";
	case 22:	return L"IPPROTO_IDP";
	case 27:	return L"IPPROTO_RDP";
	case 41:	return L"IPPROTO_IPV6";
	case 43:	return L"IPPROTO_ROUTING";
	case 44:	return L"IPPROTO_FRAGMENT";
	case 50:	return L"IPPROTO_ESP";
	case 51:	return L"IPPROTO_AH";
	case 58:	return L"IPPROTO_ICMPV6";
	case 59:	return L"IPPROTO_NONE";
	case 60:	return L"IPPROTO_DSTOPTS";
	case 77:	return L"IPPROTO_ND";
	case 78:	return L"IPPROTO_ICLFXBM";
	case 103:	return L"IPPROTO_PIM";
	case 113:	return L"IPPROTO_PGM";
	case 115:	return L"IPPROTO_L2TP";
	case 132:	return L"IPPROTO_SCTP";
	case 255:	return L"IPPROTO_RAW";
	default:	return L"Unknown";
	};
}

std::wstring FilterFlags(UINT32 flags)
{
	std::vector<std::pair<UINT32, std::wstring> > definitions =
	{
		std::make_pair(FWPM_FILTER_FLAG_PERSISTENT, L"FWPM_FILTER_FLAG_PERSISTENT"),
		std::make_pair(FWPM_FILTER_FLAG_BOOTTIME, L"FWPM_FILTER_FLAG_BOOTTIME"),
		std::make_pair(FWPM_FILTER_FLAG_CLEAR_ACTION_RIGHT, L"FWPM_FILTER_FLAG_CLEAR_ACTION_RIGHT"),
		std::make_pair(FWPM_FILTER_FLAG_PERMIT_IF_CALLOUT_UNREGISTERED, L"FWPM_FILTER_FLAG_PERMIT_IF_CALLOUT_UNREGISTERED"),
		std::make_pair(FWPM_FILTER_FLAG_DISABLED, L"FWPM_FILTER_FLAG_DISABLED"),
		std::make_pair(FWPM_FILTER_FLAG_INDEXED, L"FWPM_FILTER_FLAG_INDEXED")
	};

	return common::string::FormatFlags(definitions, flags);
}

std::wstring LayerFlags(UINT32 flags)
{
	std::vector<std::pair<UINT32, std::wstring> > definitions =
	{
		std::make_pair(FWPM_LAYER_FLAG_KERNEL, L"FWPM_LAYER_FLAG_KERNEL"),
		std::make_pair(FWPM_LAYER_FLAG_BUILTIN, L"FWPM_LAYER_FLAG_BUILTIN"),
		std::make_pair(FWPM_LAYER_FLAG_CLASSIFY_MOSTLY, L"FWPM_LAYER_FLAG_CLASSIFY_MOSTLY"),
		std::make_pair(FWPM_LAYER_FLAG_BUFFERED, L"FWPM_LAYER_FLAG_BUFFERED")
	};

	return common::string::FormatFlags(definitions, flags);
}

std::wstring ProviderContextType(FWPM_PROVIDER_CONTEXT_TYPE type)
{
	switch (type)
	{
	case FWPM_IPSEC_KEYING_CONTEXT: return L"FWPM_IPSEC_KEYING_CONTEXT";
	case FWPM_IPSEC_IKE_QM_TRANSPORT_CONTEXT: return L"FWPM_IPSEC_IKE_QM_TRANSPORT_CONTEXT";
	case FWPM_IPSEC_IKE_QM_TUNNEL_CONTEXT: return L"FWPM_IPSEC_IKE_QM_TUNNEL_CONTEXT";
	case FWPM_IPSEC_AUTHIP_QM_TRANSPORT_CONTEXT: return L"FWPM_IPSEC_AUTHIP_QM_TRANSPORT_CONTEXT";
	case FWPM_IPSEC_AUTHIP_QM_TUNNEL_CONTEXT: return L"FWPM_IPSEC_AUTHIP_QM_TUNNEL_CONTEXT";
	case FWPM_IPSEC_IKE_MM_CONTEXT: return L"FWPM_IPSEC_IKE_MM_CONTEXT";
	case FWPM_IPSEC_AUTHIP_MM_CONTEXT: return L"FWPM_IPSEC_AUTHIP_MM_CONTEXT";
	case FWPM_CLASSIFY_OPTIONS_CONTEXT: return L"FWPM_CLASSIFY_OPTIONS_CONTEXT";
	case FWPM_GENERAL_CONTEXT: return L"FWPM_GENERAL_CONTEXT";
	case FWPM_IPSEC_IKEV2_QM_TUNNEL_CONTEXT: return L"FWPM_IPSEC_IKEV2_QM_TUNNEL_CONTEXT";
	case FWPM_IPSEC_IKEV2_MM_CONTEXT: return L"FWPM_IPSEC_IKEV2_MM_CONTEXT";
	case FWPM_IPSEC_DOSP_CONTEXT: return L"FWPM_IPSEC_DOSP_CONTEXT";
	case FWPM_IPSEC_IKEV2_QM_TRANSPORT_CONTEXT: return L"FWPM_IPSEC_IKEV2_QM_TRANSPORT_CONTEXT";
	default: return L"[Unknown]";
	}
}

std::wstring Direction(UINT32 direction)
{
	switch (direction)
	{
	case 0x3900: return L"In";
	case 0x3901: return L"Out";
	case 0x3902: return L"Forward";
	default: return L"[Unknown]";
	}
}

std::wstring FilterDecoration(IPropertyDecorator *decorator, UINT64 filterId)
{
	if (nullptr == decorator)
	{
		return L"";
	}

	return (InlineFormatter() << L" " << decorator->FilterDecoration(filterId)).str();
}

std::wstring LayerDecoration(IPropertyDecorator *decorator, UINT16 layerId)
{
	if (nullptr == decorator)
	{
		return L"";
	}

	return (InlineFormatter() << L" " << decorator->LayerDecoration(layerId)).str();
}

} // namespace detail

PropertyList SessionProperties(const FWPM_SESSION0 &session)
{
	PropertyList props;
	InlineFormatter f;

	props.add(L"key", common::string::FormatGuid(session.sessionKey));

	props.add(L"name", (session.displayData.name == nullptr
		? L"n/a" : session.displayData.name));

	props.add(L"description", (session.displayData.description == nullptr
		? L"n/a" : session.displayData.description));

	props.add(L"flags", (f << session.flags << L" = " << detail::SessionFlags(session.flags)).str());
	props.add(L"wait timeout", (f << session.txnWaitTimeoutInMSec).str());
	props.add(L"sid", common::string::FormatSid(*session.sid));
	props.add(L"username", session.username);
	props.add(L"kernel", (session.kernelMode ? L"true" : L"false"));

	return props;
}

PropertyList ProviderProperties(const FWPM_PROVIDER0 &provider)
{
	PropertyList props;
	InlineFormatter f;

	props.add(L"key", common::string::FormatGuid(provider.providerKey));

	props.add(L"name", (provider.displayData.name == nullptr
		? L"n/a" : provider.displayData.name));

	props.add(L"description", (provider.displayData.description == nullptr
		? L"n/a" : provider.displayData.description));

	props.add(L"flags", (f << provider.flags << L" = " << detail::ProviderFlags(provider.flags)).str());
	props.add(L"data length", (f << provider.providerData.size).str());

	props.add(L"service name", (provider.serviceName == nullptr
		? L"n/a" : provider.serviceName));

	return props;
}

PropertyList EventProperties(const FWPM_NET_EVENT0 &event, IPropertyDecorator *decorator)
{
	PropertyList props;
	InlineFormatter f;

	props.add(L"timestamp", common::string::FormatTime(event.header.timeStamp));

	if (0 != (event.header.flags & FWPM_NET_EVENT_FLAG_IP_PROTOCOL_SET))
	{
		props.add(L"protocol", detail::FormatIpProtocol(event.header.ipProtocol));
	}

	if (0 != (event.header.flags & FWPM_NET_EVENT_FLAG_IP_VERSION_SET)
		&& 0 != (event.header.flags & FWPM_NET_EVENT_FLAG_LOCAL_ADDR_SET))
	{
		if (event.header.ipVersion == FWP_IP_VERSION_V4)
		{
			props.add(L"local addr", common::string::FormatIpV4(event.header.localAddrV4));
		}
		else
		{
			props.add(L"local addr", common::string::FormatIpV6(event.header.localAddrV6.byteArray16));
		}
	}

	if (0 != (event.header.flags & FWPM_NET_EVENT_FLAG_IP_VERSION_SET)
		&& 0 != (event.header.flags & FWPM_NET_EVENT_FLAG_REMOTE_ADDR_SET))
	{
		if (event.header.ipVersion == FWP_IP_VERSION_V4)
		{
			props.add(L"remote addr", common::string::FormatIpV4(event.header.remoteAddrV4));
		}
		else
		{
			props.add(L"remote addr", common::string::FormatIpV6(event.header.remoteAddrV6.byteArray16));
		}
	}

	if (0 != (event.header.flags & FWPM_NET_EVENT_FLAG_LOCAL_PORT_SET))
	{
		props.add(L"local port", (f << event.header.localPort).str());
	}

	if (0 != (event.header.flags & FWPM_NET_EVENT_FLAG_REMOTE_PORT_SET))
	{
		props.add(L"remote port", (f << event.header.remotePort).str());
	}

	if (0 != (event.header.flags & FWPM_NET_EVENT_FLAG_APP_ID_SET))
	{
		auto begin = reinterpret_cast<wchar_t *>(event.header.appId.data);
		auto end = begin + (event.header.appId.size / sizeof(wchar_t));

		props.add(L"app id", std::wstring(begin, end));
	}

	if (0 != (event.header.flags & FWPM_NET_EVENT_FLAG_USER_ID_SET))
	{
		props.add(L"user id", common::string::FormatSid(*event.header.userId));
	}

	if (0 != (event.header.flags & FWPM_NET_EVENT_FLAG_SCOPE_ID_SET))
	{
		props.add(L"IPv6 scope id", (f << event.header.scopeId).str());
	}

	switch (event.type)
	{
	case FWPM_NET_EVENT_TYPE_IKEEXT_MM_FAILURE:
	{
		props.add(L"type", L"IKEEXT_MM_FAILURE");
		break;
	}
	case FWPM_NET_EVENT_TYPE_IKEEXT_QM_FAILURE:
	{
		props.add(L"type", L"IKEEXT_QM_FAILURE");
		break;
	}
	case FWPM_NET_EVENT_TYPE_IKEEXT_EM_FAILURE:
	{
		props.add(L"type", L"IKEEXT_EM_FAILURE");
		break;
	}
	case FWPM_NET_EVENT_TYPE_CLASSIFY_DROP:
	{
		props.add(L"type", L"CLASSIFY_DROP");

		props.add(L"filter id", (f << event.classifyDrop->filterId
			<< detail::FilterDecoration(decorator, event.classifyDrop->filterId)).str());

		props.add(L"layer id", (f << event.classifyDrop->layerId
			<< detail::LayerDecoration(decorator, event.classifyDrop->layerId)).str());

		break;
	}
	case FWPM_NET_EVENT_TYPE_IPSEC_KERNEL_DROP:
	{
		props.add(L"type", L"IPSEC_KERNEL_DROP");
		break;
	}
	case FWPM_NET_EVENT_TYPE_IPSEC_DOSP_DROP:
	{
		props.add(L"type", L"IPSEC_DOSP_DROP");
		break;
	}
	case FWPM_NET_EVENT_TYPE_CLASSIFY_ALLOW:
	{
		props.add(L"type", L"CLASSIFY_ALLOW");
		break;
	}
	case FWPM_NET_EVENT_TYPE_CAPABILITY_DROP:
	{
		props.add(L"type", L"CAPABILITY_DROP");
		break;
	}
	case FWPM_NET_EVENT_TYPE_CAPABILITY_ALLOW:
	{
		props.add(L"type", L"CAPABILITY_ALLOW");
		break;
	}
	case FWPM_NET_EVENT_TYPE_CLASSIFY_DROP_MAC:
	{
		props.add(L"type", L"CLASSIFY_DROP_MAC");
		break;
	}
	default:
	{
		props.add(L"type", L"Unknown");
	}
	};

	return props;
}

PropertyList EventProperties(const FWPM_NET_EVENT1 &event, IPropertyDecorator *decorator)
{
	//
	// TODO-MAYBE: Restructure code to operate on individual elements of the structure
	// then use upcasting and a single implementation for extracting the basic information.
	//

	PropertyList props;
	InlineFormatter f;

	props.add(L"timestamp", common::string::FormatTime(event.header.timeStamp));

	if (0 != (event.header.flags & FWPM_NET_EVENT_FLAG_IP_PROTOCOL_SET))
	{
		props.add(L"protocol", detail::FormatIpProtocol(event.header.ipProtocol));
	}

	if (0 != (event.header.flags & FWPM_NET_EVENT_FLAG_IP_VERSION_SET)
		&& 0 != (event.header.flags & FWPM_NET_EVENT_FLAG_LOCAL_ADDR_SET))
	{
		if (event.header.ipVersion == FWP_IP_VERSION_V4)
		{
			props.add(L"local addr", common::string::FormatIpV4(event.header.localAddrV4));
		}
		else
		{
			props.add(L"local addr", common::string::FormatIpV6(event.header.localAddrV6.byteArray16));
		}
	}

	if (0 != (event.header.flags & FWPM_NET_EVENT_FLAG_IP_VERSION_SET)
		&& 0 != (event.header.flags & FWPM_NET_EVENT_FLAG_REMOTE_ADDR_SET))
	{
		if (event.header.ipVersion == FWP_IP_VERSION_V4)
		{
			props.add(L"remote addr", common::string::FormatIpV4(event.header.remoteAddrV4));
		}
		else
		{
			props.add(L"remote addr", common::string::FormatIpV6(event.header.remoteAddrV6.byteArray16));
		}
	}

	if (0 != (event.header.flags & FWPM_NET_EVENT_FLAG_LOCAL_PORT_SET))
	{
		props.add(L"local port", (f << event.header.localPort).str());
	}

	if (0 != (event.header.flags & FWPM_NET_EVENT_FLAG_REMOTE_PORT_SET))
	{
		props.add(L"remote port", (f << event.header.remotePort).str());
	}

	if (0 != (event.header.flags & FWPM_NET_EVENT_FLAG_APP_ID_SET))
	{
		auto begin = reinterpret_cast<wchar_t *>(event.header.appId.data);
		auto end = begin + (event.header.appId.size / sizeof(wchar_t));

		props.add(L"app id", std::wstring(begin, end));
	}

	if (0 != (event.header.flags & FWPM_NET_EVENT_FLAG_USER_ID_SET))
	{
		props.add(L"user id", common::string::FormatSid(*event.header.userId));
	}

	if (0 != (event.header.flags & FWPM_NET_EVENT_FLAG_SCOPE_ID_SET))
	{
		props.add(L"IPv6 scope id", (f << event.header.scopeId).str());
	}

	switch (event.type)
	{
	case FWPM_NET_EVENT_TYPE_IKEEXT_MM_FAILURE:
	{
		props.add(L"type", L"IKEEXT_MM_FAILURE");
		break;
	}
	case FWPM_NET_EVENT_TYPE_IKEEXT_QM_FAILURE:
	{
		props.add(L"type", L"IKEEXT_QM_FAILURE");
		break;
	}
	case FWPM_NET_EVENT_TYPE_IKEEXT_EM_FAILURE:
	{
		props.add(L"type", L"IKEEXT_EM_FAILURE");
		break;
	}
	case FWPM_NET_EVENT_TYPE_CLASSIFY_DROP:
	{
		props.add(L"type", L"CLASSIFY_DROP");

		props.add(L"filter id", (f << event.classifyDrop->filterId
			<< detail::FilterDecoration(decorator, event.classifyDrop->filterId)).str());

		props.add(L"layer id", (f << event.classifyDrop->layerId
			<< detail::LayerDecoration(decorator, event.classifyDrop->layerId)).str());

		props.add(L"direction", detail::Direction(event.classifyDrop->msFwpDirection));

		if (1 == event.classifyDrop->isLoopback)
		{
			props.add(L"loopback", L"True");
		}

		break;
	}
	case FWPM_NET_EVENT_TYPE_IPSEC_KERNEL_DROP:
	{
		props.add(L"type", L"IPSEC_KERNEL_DROP");
		break;
	}
	case FWPM_NET_EVENT_TYPE_IPSEC_DOSP_DROP:
	{
		props.add(L"type", L"IPSEC_DOSP_DROP");
		break;
	}
	case FWPM_NET_EVENT_TYPE_CLASSIFY_ALLOW:
	{
		props.add(L"type", L"CLASSIFY_ALLOW");
		break;
	}
	case FWPM_NET_EVENT_TYPE_CAPABILITY_DROP:
	{
		props.add(L"type", L"CAPABILITY_DROP");
		break;
	}
	case FWPM_NET_EVENT_TYPE_CAPABILITY_ALLOW:
	{
		props.add(L"type", L"CAPABILITY_ALLOW");
		break;
	}
	case FWPM_NET_EVENT_TYPE_CLASSIFY_DROP_MAC:
	{
		props.add(L"type", L"CLASSIFY_DROP_MAC");
		break;
	}
	default:
	{
		props.add(L"type", L"Unknown");
	}
	};

	return props;
}

PropertyList FilterProperties(const FWPM_FILTER0 &filter)
{
	PropertyList props;
	InlineFormatter f;

	props.add(L"key", common::string::FormatGuid(filter.filterKey));

	props.add(L"name", (filter.displayData.name == nullptr
		? L"n/a" : filter.displayData.name));

	props.add(L"description", (filter.displayData.description == nullptr
		? L"n/a" : filter.displayData.description));

	props.add(L"flags", (f << filter.flags << L" = " << detail::FilterFlags(filter.flags)).str());

	if (filter.providerKey != nullptr)
	{
		props.add(L"provider key", common::string::FormatGuid(*filter.providerKey));
	}

	if (filter.providerData.data != nullptr)
	{
		props.add(L"provider data", L"Present");
	}

	props.add(L"layer key", common::string::FormatGuid(filter.layerKey));
	props.add(L"sublayer key", common::string::FormatGuid(filter.subLayerKey));

	if (FWP_UINT64 == filter.weight.type)
	{
		props.add(L"weight", (f << *filter.weight.uint64 << L" (exact)").str());
	}
	else if (FWP_UINT8 == filter.weight.type)
	{
		props.add(L"weight", (f << filter.weight.uint8 << L" (relative 0-15)").str());
	}
	else
	{
		props.add(L"weight", L"Automatic");
	}

	props.add(L"num conditions", (f << filter.numFilterConditions).str());
	props.add(L"conditions", L"TODO");

	if (FWP_ACTION_BLOCK == filter.action.type)
	{
		props.add(L"action", L"Block");
		props.add(L"filter type", common::string::FormatGuid(filter.action.filterType));
	}
	else if (FWP_ACTION_PERMIT == filter.action.type)
	{
		props.add(L"action", L"Permit");
		props.add(L"filter type", common::string::FormatGuid(filter.action.filterType));
	}
	else if (FWP_ACTION_CALLOUT_TERMINATING == filter.action.type)
	{
		props.add(L"action", L"Callout terminating");
		props.add(L"callout key", common::string::FormatGuid(filter.action.calloutKey));
	}
	else if (FWP_ACTION_CALLOUT_INSPECTION == filter.action.type)
	{
		props.add(L"action", L"Callout inspection");
		props.add(L"callout key", common::string::FormatGuid(filter.action.calloutKey));
	}
	else if (FWP_ACTION_CALLOUT_UNKNOWN == filter.action.type)
	{
		props.add(L"action", L"Callout unknown");
		props.add(L"callout key", common::string::FormatGuid(filter.action.calloutKey));
	}

	if (0 != (filter.flags & FWPM_FILTER_FLAG_HAS_PROVIDER_CONTEXT))
	{
		props.add(L"context", L"Provider context");
	}
	else
	{
		props.add(L"context", L"Raw context");
	}

	props.add(L"filter id", (f << filter.filterId).str());

	if (FWP_UINT64 == filter.effectiveWeight.type)
	{
		props.add(L"effective weight", (f << *filter.effectiveWeight.uint64 << L" (exact)").str());
	}
	else if (FWP_UINT8 == filter.effectiveWeight.type)
	{
		props.add(L"effective weight", (f << filter.effectiveWeight.uint8 << L" (relative 0-15)").str());
	}
	else
	{
		props.add(L"effective weight", L"Automatic");
	}

	return props;
}

PropertyList LayerProperties(const FWPM_LAYER0 &layer)
{
	PropertyList props;
	InlineFormatter f;

	props.add(L"key", common::string::FormatGuid(layer.layerKey));

	props.add(L"name", (layer.displayData.name == nullptr
		? L"n/a" : layer.displayData.name));

	props.add(L"description", (layer.displayData.description == nullptr
		? L"n/a" : layer.displayData.description));

	props.add(L"flags", (f << layer.flags << L" = " << detail::LayerFlags(layer.flags)).str());
	props.add(L"num fields", (f << layer.numFields).str());
	props.add(L"field array", L"TODO");
	props.add(L"default sublayer", common::string::FormatGuid(layer.defaultSubLayerKey));
	props.add(L"layer id", (f << layer.layerId).str());

	return props;
}

PropertyList ProviderContextProperties(const FWPM_PROVIDER_CONTEXT0 &context)
{
	PropertyList props;
	InlineFormatter f;

	props.add(L"key", common::string::FormatGuid(context.providerContextKey));

	props.add(L"name", (context.displayData.name == nullptr
		? L"n/a" : context.displayData.name));

	props.add(L"description", (context.displayData.description == nullptr
		? L"n/a" : context.displayData.description));

	if (0 != (context.flags & FWPM_PROVIDER_CONTEXT_FLAG_PERSISTENT))
	{
		props.add(L"flags", L"FWPM_PROVIDER_CONTEXT_FLAG_PERSISTENT");
	}
	else
	{
		props.add(L"flags", (f << context.flags).str());
	}

	props.add(L"provider key", (context.providerKey == nullptr
		? L"n/a" : common::string::FormatGuid(*context.providerKey)));

	if (context.providerData.data != nullptr)
	{
		props.add(L"provider data", L"Present");
	}

	props.add(L"context type", detail::ProviderContextType(context.type));
	props.add(L"id", (f << context.providerContextId).str());

	return props;
}

PropertyList SublayerProperties(const FWPM_SUBLAYER0 &sublayer)
{
	PropertyList props;
	InlineFormatter f;

	props.add(L"key", common::string::FormatGuid(sublayer.subLayerKey));

	props.add(L"name", (sublayer.displayData.name == nullptr
		? L"n/a" : sublayer.displayData.name));

	props.add(L"description", (sublayer.displayData.description == nullptr
		? L"n/a" : sublayer.displayData.description));

	if (0 != (sublayer.flags & FWPM_SUBLAYER_FLAG_PERSISTENT))
	{
		props.add(L"flags", L"FWPM_SUBLAYER_FLAG_PERSISTENT");
	}
	else
	{
		props.add(L"flags", (f << sublayer.flags).str());
	}

	props.add(L"provider key", (sublayer.providerKey == nullptr
		? L"n/a" : common::string::FormatGuid(*sublayer.providerKey)));

	if (sublayer.providerData.data != nullptr)
	{
		props.add(L"provider data", L"Present");
	}

	props.add(L"weight", (f << sublayer.weight).str());

	return props;
}
