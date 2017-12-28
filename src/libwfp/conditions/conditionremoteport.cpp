#include "stdafx.h"
#include "conditionremoteport.h"
#include "libwfp/internal/conditionassembler.h"
#include "libcommon/error.h"
#include <guiddef.h>
#include <fwpmu.h>

using ConditionAssembler = ::wfp::internal::ConditionAssembler;

namespace wfp::conditions {

ConditionRemotePort::ConditionRemotePort(UINT16 port)
	: m_port(port)
{
	m_assembled = ConditionAssembler::Uint16(identifier(), FWP_MATCH_EQUAL, port);
}

std::wstring ConditionRemotePort::toString() const
{
	std::wstringstream ss;

	ss << L"remote port = " << m_port;

	return ss.str();
}

const GUID &ConditionRemotePort::identifier() const
{
	return FWPM_CONDITION_IP_REMOTE_PORT;
}

const FWPM_FILTER_CONDITION0 &ConditionRemotePort::condition() const
{
	return *reinterpret_cast<FWPM_FILTER_CONDITION0 *>(m_assembled->data);
}

}
