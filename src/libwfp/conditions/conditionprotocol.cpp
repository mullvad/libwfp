#include "stdafx.h"
#include "conditionprotocol.h"
#include "libwfp/internal/conditionassembler.h"
#include <winsock2.h>

using ConditionAssembler = ::wfp::internal::ConditionAssembler;

namespace wfp::conditions {

ConditionProtocol::ConditionProtocol(Protocol protocol)
	: m_protocol(protocol)
{
	m_assembled = ConditionAssembler::Uint8
	(
		identifier(),
		FWP_MATCH_EQUAL,
		static_cast<UINT8>(Protocol::Tcp == m_protocol ? IPPROTO_TCP : IPPROTO_UDP)
	);
}

std::wstring ConditionProtocol::toString() const
{
	return
	(
		Protocol::Tcp == m_protocol
		? L"protocol = TCP"
		: L"protocol = UDP"
	);
}

const GUID &ConditionProtocol::identifier() const
{
	return FWPM_CONDITION_IP_PROTOCOL;
}

const FWPM_FILTER_CONDITION0 &ConditionProtocol::condition() const
{
	return *reinterpret_cast<FWPM_FILTER_CONDITION0 *>(m_assembled.data());
}

//static
ConditionProtocol *ConditionProtocol::Tcp()
{
	return new ConditionProtocol(Protocol::Tcp);
}

//static
ConditionProtocol *ConditionProtocol::Udp()
{
	return new ConditionProtocol(Protocol::Udp);
}

}
