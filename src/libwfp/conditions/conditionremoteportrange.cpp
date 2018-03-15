#include "stdafx.h"
#include "conditionremoteportrange.h"
#include "libwfp/internal/conditionassembler.h"
#include <sstream>

using ConditionAssembler = ::wfp::internal::ConditionAssembler;

namespace wfp::conditions {

ConditionRemotePortRange::ConditionRemotePortRange(uint16_t firstPort, uint16_t lastPort, const IStrictComparison &comparison)
	: m_firstPort(firstPort)
	, m_lastPort(lastPort)
	, m_comparison(comparison)
{
	FWP_RANGE0 range;

	range.valueLow.type = FWP_UINT16;
	range.valueLow.uint16 = firstPort;
	range.valueHigh.type = FWP_UINT16;
	range.valueHigh.uint16 = lastPort;

	m_assembled = ConditionAssembler::Range(identifier(), m_comparison.op(), range);
}

std::wstring ConditionRemotePortRange::toString() const
{
	std::wstringstream ss;

	ss << L"remote port " << (m_comparison.op() == FWP_MATCH_EQUAL ? L"inside" : L"outside")
		<< L" range " << m_firstPort << L"-" << m_lastPort;

	return ss.str();
}

const GUID &ConditionRemotePortRange::identifier() const
{
	return FWPM_CONDITION_IP_REMOTE_PORT;
}

const FWPM_FILTER_CONDITION0 &ConditionRemotePortRange::condition() const
{
	return *reinterpret_cast<FWPM_FILTER_CONDITION0 *>(m_assembled.data());
}

}
