#include "stdafx.h"
#include "ipaddr.h"
#include <ws2tcpip.h>
#include <winsock2.h>
#include <stdexcept>

namespace wfp
{

IpAddr::IpAddr(const std::wstring &addrspec)
{
	uint8_t buffer[sizeof(IN6_ADDR)];

	if (1 == InetPtonW(AF_INET, addrspec.c_str(), &buffer))
	{
		auto parsed = reinterpret_cast<const IN_ADDR *>(&buffer);

		m_ipv4 = ntohl(parsed->s_addr);
		m_type = Type::IPv4;

		memset(&m_ipv6, 0, sizeof(m_ipv6));
	}
	else if (1 == InetPtonW(AF_INET6, addrspec.c_str(), &buffer))
	{
		auto parsed = reinterpret_cast<const IN6_ADDR *>(&buffer);

		memcpy(m_ipv6.byteArray16, parsed->u.Byte, sizeof(m_ipv6.byteArray16));
		m_type = Type::IPv6;

		m_ipv4 = 0;
	}
	else
	{
		throw std::runtime_error("Parser failure: Invalid IP address.");
	}
}

IpAddr::IpAddr(UINT32 addr)
	: m_ipv4(addr)
	, m_type(Type::IPv4)
{
	memset(&m_ipv6, 0, sizeof(m_ipv6));
}

IpAddr::IpAddr(const FWP_BYTE_ARRAY16 &addr)
	: m_ipv4(0)
	, m_type(Type::IPv6)
{
	m_ipv6 = addr;
}

}
