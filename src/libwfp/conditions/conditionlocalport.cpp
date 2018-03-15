#include "stdafx.h"
#include "conditionlocalport.h"
#include "libwfp/internal/conditionassembler.h"
#include <sstream>

using ConditionAssembler = ::wfp::internal::ConditionAssembler;

namespace wfp::conditions {

ConditionLocalPort::ConditionLocalPort(uint16_t port, const IRelaxedComparison &comparison)
	: m_port(port)
	, m_comparison(comparison)
{
	m_assembled = ConditionAssembler::Uint16(identifier(), m_comparison.op(), port);
}

std::wstring ConditionLocalPort::toString() const
{
	std::wstringstream ss;

	ss << L"local port " << m_comparison.toString() << L" " << m_port;

	return ss.str();
}

const GUID &ConditionLocalPort::identifier() const
{
	return FWPM_CONDITION_IP_LOCAL_PORT;
}

const FWPM_FILTER_CONDITION0 &ConditionLocalPort::condition() const
{
	return *reinterpret_cast<FWPM_FILTER_CONDITION0 *>(m_assembled.data());
}

}
