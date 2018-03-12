#include "stdafx.h"
#include "conditionlocalip.h"
#include "libwfp/internal/conditionassembler.h"
#include "libcommon/network.h"
#include "libcommon/string.h"
#include <sstream>
#include <stdexcept>

using ConditionAssembler = ::wfp::internal::ConditionAssembler;

namespace wfp::conditions {

ConditionLocalIp::ConditionLocalIp(const IpAddress &netnode, const IStrictComparison &comparison)
	: m_net(netnode)
	, m_prefix(0)
	, m_comparison(comparison)
{
	switch (m_net.type())
	{
		case IpAddress::Type::Ipv4:
		{
			m_addressType = AddressType::Ipv4;
			m_assembled = ConditionAssembler::Uint32(identifier(), m_comparison.op(), m_net.addr());

			break;
		}
		case IpAddress::Type::Ipv6:
		{
			m_addressType = AddressType::Ipv6;
			m_assembled = ConditionAssembler::ByteArray16(identifier(), m_comparison.op(), m_net.addr6());

			break;
		}
		default:
		{
			throw std::logic_error("Missing case handler in switch clause");
		}
	}
}

ConditionLocalIp::ConditionLocalIp(const IpAddress &network, uint8_t prefix, const IStrictComparison &comparison)
	: m_net(network)
	, m_prefix(prefix)
	, m_comparison(comparison)
{
	switch (m_net.type())
	{
		case IpAddress::Type::Ipv4:
		{
			m_addressType = AddressType::Ipv4Network;

			FWP_V4_ADDR_AND_MASK netdef;
			netdef.addr = m_net.addr();
			netdef.mask = common::network::MaskFromRoutingPrefix(m_prefix);

			m_assembled = ConditionAssembler::Ipv4Network(identifier(), m_comparison.op(), netdef);

			break;
		}
		case IpAddress::Type::Ipv6:
		{
			m_addressType = AddressType::Ipv6Network;

			FWP_V6_ADDR_AND_MASK netdef;
			memcpy(netdef.addr, m_net.addr6().byteArray16, sizeof(netdef.addr));
			netdef.prefixLength = m_prefix;

			m_assembled = ConditionAssembler::Ipv6Network(identifier(), m_comparison.op(), netdef);

			break;
		}
		default:
		{
			throw std::logic_error("Missing case handler in switch clause");
		}
	}
}

std::wstring ConditionLocalIp::toString() const
{
	std::wstringstream ss;

	switch (m_addressType)
	{
		case AddressType::Ipv4:
		{
			ss << L"local ip " << m_comparison.toString() << L" " << common::string::FormatIpv4(m_net.addr());
			break;
		}
		case AddressType::Ipv4Network:
		{
			ss << L"local ip net " << m_comparison.toString() << L" " << common::string::FormatIpv4(m_net.addr(), m_prefix);
			break;
		}
		case AddressType::Ipv6:
		{
			ss << L"local ip " << m_comparison.toString() << L" " << common::string::FormatIpv6(m_net.addr6().byteArray16);
			break;
		}
		case AddressType::Ipv6Network:
		{
			ss << L"local ip net " << m_comparison.toString() << L" " << common::string::FormatIpv6(m_net.addr6().byteArray16, m_prefix);
			break;
		}
		default:
		{
			throw std::logic_error("Missing case handler in switch clause");
		}
	};

	return ss.str();
}

const GUID &ConditionLocalIp::identifier() const
{
	return FWPM_CONDITION_IP_LOCAL_ADDRESS;
}

const FWPM_FILTER_CONDITION0 &ConditionLocalIp::condition() const
{
	return *reinterpret_cast<FWPM_FILTER_CONDITION0 *>(m_assembled.data());
}

}
