#include "stdafx.h"
#include "inlineformatter.h"
#include "propertylist.h"
#include "libwfp/filterengine.h"
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

/*

std::wstring ProviderFlags(UINT32 flags)
{
	std::vector<std::pair<UINT32, std::wstring> > definitions =
	{
		std::make_pair(FWPM_PROVIDER_FLAG_PERSISTENT, L"FWPM_PROVIDER_FLAG_PERSISTENT"),
		std::make_pair(FWPM_PROVIDER_FLAG_DISABLED, L"FWPM_PROVIDER_FLAG_DISABLED")
	};

	return common::string::FormatFlags(definitions, flags);
}

bool ProviderCallback(const FWPM_PROVIDER0 &provider)
{
	std::wcout << L"Provider" << std::endl;

	std::wcout << L"  key:\t\t\t" << common::string::FormatGuid(provider.providerKey) << std::endl;
	std::wcout << L"  name:\t\t\t" <<
		(provider.displayData.name == nullptr ? L"n/a" : provider.displayData.name) << std::endl;
	std::wcout << L"  description:\t\t" <<
		(provider.displayData.description == nullptr ? L"n/a" : provider.displayData.description) << std::endl;
	std::wcout << L"  flags:\t\t" << provider.flags << L" = " << ProviderFlags(provider.flags) << std::endl;
	std::wcout << L"  data length:\t\t" << provider.providerData.size << std::endl;
	std::wcout << L"  service name:\t\t" <<
		(provider.serviceName == nullptr ? L"n/a" : provider.serviceName) << std::endl;

	return true;
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

bool EventCallback(const FWPM_NET_EVENT0 &event)
{
	std::wcout << L"Event" << std::endl;

	std::wcout << L"  timestamp:\t" << common::string::FormatTime(event.header.timeStamp) << std::endl;

	if (0 != (event.header.flags & FWPM_NET_EVENT_FLAG_IP_PROTOCOL_SET))
	{
		std::wcout << L"  ip proto:\t" << FormatIpProtocol(event.header.ipProtocol) << std::endl;
	}

	if (0 != (event.header.flags & FWPM_NET_EVENT_FLAG_IP_VERSION_SET)
		&& 0 != (event.header.flags & FWPM_NET_EVENT_FLAG_LOCAL_ADDR_SET))
	{
		if (event.header.ipVersion == FWP_IP_VERSION_V4)
		{
			std::wcout << L"  local addr:\t" << common::string::FormatIpV4(event.header.localAddrV4) << std::endl;
		}
		else
		{
			std::wcout << L"  local addr:\t" << common::string::FormatIpV6(event.header.localAddrV6.byteArray16) << std::endl;
		}
	}

	if (0 != (event.header.flags & FWPM_NET_EVENT_FLAG_IP_VERSION_SET)
		&& 0 != (event.header.flags & FWPM_NET_EVENT_FLAG_REMOTE_ADDR_SET))
	{
		if (event.header.ipVersion == FWP_IP_VERSION_V4)
		{
			std::wcout << L"  remote addr:\t" << common::string::FormatIpV4(event.header.remoteAddrV4) << std::endl;
		}
		else
		{
			std::wcout << L"  remote addr:\t" << common::string::FormatIpV6(event.header.remoteAddrV6.byteArray16) << std::endl;
		}
	}

	if (0 != (event.header.flags & FWPM_NET_EVENT_FLAG_LOCAL_PORT_SET))
	{
		std::wcout << L"  local port:\t" << event.header.localPort << std::endl;
	}

	if (0 != (event.header.flags & FWPM_NET_EVENT_FLAG_REMOTE_PORT_SET))
	{
		std::wcout << L"  remote port:\t" << event.header.remotePort << std::endl;
	}

	if (0 != (event.header.flags & FWPM_NET_EVENT_FLAG_APP_ID_SET))
	{
		std::wcout << L"  app id:\tPresent" << std::endl;
	}

	if (0 != (event.header.flags & FWPM_NET_EVENT_FLAG_USER_ID_SET))
	{
		std::wcout << L"  user id:\tPresent" << std::endl;
	}

	if (0 != (event.header.flags & FWPM_NET_EVENT_FLAG_SCOPE_ID_SET))
	{
		std::wcout << L"  scope id:\tPresent" << std::endl;
	}

	switch (event.type)
	{
	case FWPM_NET_EVENT_TYPE_IKEEXT_MM_FAILURE:
	{
		std::wcout << L"  type: IKEEXT_MM_FAILURE" << std::endl;
		break;
	}
	case FWPM_NET_EVENT_TYPE_IKEEXT_QM_FAILURE:
	{
		std::wcout << L"  type: IKEEXT_QM_FAILURE" << std::endl;
		break;
	}
	case FWPM_NET_EVENT_TYPE_IKEEXT_EM_FAILURE:
	{
		std::wcout << L"  type: IKEEXT_EM_FAILURE" << std::endl;
		break;
	}
	case FWPM_NET_EVENT_TYPE_CLASSIFY_DROP:
	{
		std::wcout << L"  type: CLASSIFY_DROP" << std::endl;
		break;
	}
	case FWPM_NET_EVENT_TYPE_IPSEC_KERNEL_DROP:
	{
		std::wcout << L"  type: IPSEC_KERNEL_DROP" << std::endl;
		break;
	}
	case FWPM_NET_EVENT_TYPE_IPSEC_DOSP_DROP:
	{
		std::wcout << L"  type: IPSEC_DOSP_DROP" << std::endl;
		break;
	}
	case FWPM_NET_EVENT_TYPE_CLASSIFY_ALLOW:
	{
		std::wcout << L"  type: CLASSIFY_ALLOW" << std::endl;
		break;
	}
	case FWPM_NET_EVENT_TYPE_CAPABILITY_DROP:
	{
		std::wcout << L"  type: CAPABILITY_DROP" << std::endl;
		break;
	}
	case FWPM_NET_EVENT_TYPE_CAPABILITY_ALLOW:
	{
		std::wcout << L"  type: CAPABILITY_ALLOW" << std::endl;
		break;
	}
	case FWPM_NET_EVENT_TYPE_CLASSIFY_DROP_MAC:
	{
		std::wcout << L"  type: CLASSIFY_DROP_MAC" << std::endl;
		break;
	}
	default:
	{
		std::wcout << L"  type: Unknown" << std::endl;
	}
	};

	return true;
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

bool FilterCallback(const FWPM_FILTER0 &filter)
{
	std::wcout << L"Filter" << std::endl;

	std::wcout << L"  key:\t\t\t" << common::string::FormatGuid(filter.filterKey) << std::endl;
	std::wcout << L"  name:\t\t\t" <<
		(filter.displayData.name == nullptr ? L"n/a" : filter.displayData.name) << std::endl;
	std::wcout << L"  description:\t\t" <<
		(filter.displayData.description == nullptr ? L"n/a" : filter.displayData.description) << std::endl;
	std::wcout << L"  flags:\t\t" << filter.flags << L" = " << FilterFlags(filter.flags) << std::endl;

	if (filter.providerKey != nullptr)
	{
		std::wcout << L"  provider key:\t\t" << common::string::FormatGuid(*filter.providerKey) << std::endl;
	}

	if (filter.providerData.data != nullptr)
	{
		std::wcout << L"  provider data:\tPresent" << std::endl;
	}

	std::wcout << L"  layer key:\t\t" << common::string::FormatGuid(filter.layerKey) << std::endl;
	std::wcout << L"  sublayer key:\t\t" << common::string::FormatGuid(filter.subLayerKey) << std::endl;

	if (FWP_UINT64 == filter.weight.type)
	{
		std::wcout << L"  weight:\t\t(Exact) " << *filter.weight.uint64 << std::endl;
	}
	else if (FWP_UINT8 == filter.weight.type)
	{
		std::wcout << L"  weight:\t\t(Relative 0-15) " << filter.weight.uint8 << std::endl;
	}
	else
	{
		std::wcout << L"  weight:\t\tAutomatic" << std::endl;
	}

	std::wcout << L"  number of conditions:\t" << filter.numFilterConditions << std::endl;
	std::wcout << L"  conditions:\t\tTODO" << std::endl;

	if (FWP_ACTION_BLOCK == filter.action.type)
	{
		std::wcout << L"  action:\t\tBlock" << std::endl;
		std::wcout << L"  filter type:\t\t" << common::string::FormatGuid(filter.action.filterType) << std::endl;
	}
	else if (FWP_ACTION_PERMIT == filter.action.type)
	{
		std::wcout << L"  action:\t\tPermit" << std::endl;
		std::wcout << L"  filter type:\t\t" << common::string::FormatGuid(filter.action.filterType) << std::endl;
	}
	else if (FWP_ACTION_CALLOUT_TERMINATING == filter.action.type)
	{
		std::wcout << L"  action:\t\tCallout terminating" << std::endl;
		std::wcout << L"  callout key:\t\t" << common::string::FormatGuid(filter.action.calloutKey) << std::endl;
	}
	else if (FWP_ACTION_CALLOUT_INSPECTION == filter.action.type)
	{
		std::wcout << L"  action:\t\tCallout inspection" << std::endl;
		std::wcout << L"  callout key:\t\t" << common::string::FormatGuid(filter.action.calloutKey) << std::endl;
	}
	else if (FWP_ACTION_CALLOUT_UNKNOWN == filter.action.type)
	{
		std::wcout << L"  action:\t\tCallout unknown" << std::endl;
		std::wcout << L"  callout key:\t\t" << common::string::FormatGuid(filter.action.calloutKey) << std::endl;
	}

	if (0 != (filter.flags & FWPM_FILTER_FLAG_HAS_PROVIDER_CONTEXT))
	{
		std::wcout << L"  context:\t\tProvider context" << std::endl;
	}
	else
	{
		std::wcout << L"  context:\t\tRaw context" << std::endl;
	}

	std::wcout << L"  filter id:\t\t" << filter.filterId << std::endl;

	if (FWP_UINT64 == filter.effectiveWeight.type)
	{
		std::wcout << L"  effective weight:\t(Exact) " << *filter.effectiveWeight.uint64 << std::endl;
	}
	else if (FWP_UINT8 == filter.effectiveWeight.type)
	{
		std::wcout << L"  effective weight:\t(Relative 0-15) " << filter.effectiveWeight.uint8 << std::endl;
	}
	else
	{
		std::wcout << L"  effective weight:\tAutomatic" << std::endl;
	}

	return true;
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

bool LayerCallback(const FWPM_LAYER0 &layer)
{
	std::wcout << L"Layer" << std::endl;

	std::wcout << L"  layer key:\t\t" << common::string::FormatGuid(layer.layerKey) << std::endl;
	std::wcout << L"  name:\t\t\t" <<
		(layer.displayData.name == nullptr ? L"n/a" : layer.displayData.name) << std::endl;
	std::wcout << L"  description:\t\t" <<
		(layer.displayData.description == nullptr ? L"n/a" : layer.displayData.description) << std::endl;

	std::wcout << L"  flags:\t\t" << layer.flags << L" = " << LayerFlags(layer.flags) << std::endl;
	std::wcout << L"  fields:\t\t" << layer.numFields << std::endl;
	std::wcout << L"  field array:\t\tTODO" << std::endl;
	std::wcout << L"  default sublayer:\t" << common::string::FormatGuid(layer.defaultSubLayerKey) << std::endl;
	std::wcout << L"  layer id:\t\t" << layer.layerId << std::endl;

	return true;
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

bool ProviderContextCallback(const FWPM_PROVIDER_CONTEXT0 &context)
{
	std::wcout << L"Provider context" << std::endl;

	std::wcout << L"  key:\t\t\t" << common::string::FormatGuid(context.providerContextKey) << std::endl;
	std::wcout << L"  name:\t\t\t" <<
		(context.displayData.name == nullptr ? L"n/a" : context.displayData.name) << std::endl;
	std::wcout << L"  description:\t\t" <<
		(context.displayData.description == nullptr ? L"n/a" : context.displayData.description) << std::endl;

	if (0 != (context.flags & FWPM_PROVIDER_CONTEXT_FLAG_PERSISTENT))
	{
		std::wcout << L"  flags:\t\tFWPM_PROVIDER_CONTEXT_FLAG_PERSISTENT" << std::endl;
	}
	else
	{
		std::wcout << L"  flags:\t\t0" << std::endl;
	}

	std::wcout << L"  provider key:\t\t" << (context.providerKey == nullptr ? L"n/a" :
		common::string::FormatGuid(*context.providerKey)) << std::endl;

	if (context.providerData.data != nullptr)
	{
		std::wcout << L"  provider data:\t\tPresent" << std::endl;
	}

	std::wcout << L"  context type:\t\t" << ProviderContextType(context.type) << std::endl;
	std::wcout << L"  id:\t\t\t" << context.providerContextId << std::endl;

	return true;
}

bool SublayerCallback(const FWPM_SUBLAYER0 &sublayer)
{
	std::wcout << L"Sublayer" << std::endl;

	std::wcout << L"  key:\t\t\t" << common::string::FormatGuid(sublayer.subLayerKey) << std::endl;
	std::wcout << L"  name:\t\t\t" <<
		(sublayer.displayData.name == nullptr ? L"n/a" : sublayer.displayData.name) << std::endl;
	std::wcout << L"  description:\t\t" <<
		(sublayer.displayData.description == nullptr ? L"n/a" : sublayer.displayData.description) << std::endl;

	if (0 != (sublayer.flags & FWPM_SUBLAYER_FLAG_PERSISTENT))
	{
		std::wcout << L"  flags:\t\tFWPM_SUBLAYER_FLAG_PERSISTENT" << std::endl;
	}
	else
	{
		std::wcout << L"  flags:\t\t0" << std::endl;
	}

	std::wcout << L"  provider key:\t\t" << (sublayer.providerKey == nullptr ? L"n/a" :
		common::string::FormatGuid(*sublayer.providerKey)) << std::endl;

	if (sublayer.providerData.data != nullptr)
	{
		std::wcout << L"  provider data:\t\tPresent" << std::endl;
	}

	std::wcout << L"  weight:\t\t" << sublayer.weight << std::endl;

	return true;
}

*/
