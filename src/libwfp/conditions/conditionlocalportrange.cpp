#include "stdafx.h"
#include "conditionlocalportrange.h"
#include "libwfp/internal/conditionassembler.h"
#include <sstream>

using ConditionAssembler = ::wfp::internal::ConditionAssembler;

namespace wfp::conditions {

ConditionLocalPortRange::ConditionLocalPortRange(uint16_t firstPort, uint16_t lastPort, const IStrictComparison &comparison)
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

std::wstring ConditionLocalPortRange::toString() const
{
	std::wstringstream ss;

	ss << L"local port " << (m_comparison.op() == FWP_MATCH_EQUAL ? L"inside" : L"outside")
		<< L" range " << m_firstPort << L"-" << m_lastPort;

	return ss.str();
}

const GUID &ConditionLocalPortRange::identifier() const
{
	return FWPM_CONDITION_IP_LOCAL_PORT;
}

const FWPM_FILTER_CONDITION0 &ConditionLocalPortRange::condition() const
{
	return *reinterpret_cast<FWPM_FILTER_CONDITION0 *>(m_assembled.data());
}

}
