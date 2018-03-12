#pragma once

#include <windows.h>
#include <fwptypes.h>
#include <string>

namespace wfp
{

//
// Abstraction over a specific IPv4/IPv6 address.
// For IPv4, host byte order is used.
//
class IpAddr
{
public:

	IpAddr(const std::wstring &addrspec);
	IpAddr(UINT32 addrspec);
	IpAddr(const FWP_BYTE_ARRAY16 &addrspec);

	enum Type
	{
		IPv4,
		IPv6
	};

	Type type()
	{
		return m_type;
	}

	UINT32 addr()
	{
		return m_ipv4;
	}

	const FWP_BYTE_ARRAY16 &addr6()
	{
		return m_ipv6;
	}

private:

	UINT32 m_ipv4;
	FWP_BYTE_ARRAY16 m_ipv6;

	Type m_type;
};

}
