#include "stdafx.h"
#include "conditionloopback.h"
#include "libwfp/internal/conditionassembler.h"
#include <ipifcons.h>
#include <sstream>
#include <stdexcept>

using ConditionAssembler = ::wfp::internal::ConditionAssembler;

namespace wfp::conditions {

ConditionLoopback::ConditionLoopback(const IStrictComparison &comparison)
	: m_comparison(comparison)
{
	m_assembled = ConditionAssembler::Uint32(identifier(), m_comparison.op(), UINT32(IF_TYPE_SOFTWARE_LOOPBACK));
}

std::wstring ConditionLoopback::toString() const
{
	std::wstringstream ss;

	ss << L"interface " << m_comparison.toString() << L" loopback";

	return ss.str();
}

const GUID &ConditionLoopback::identifier() const
{
	return FWPM_CONDITION_INTERFACE_TYPE;
}

const FWPM_FILTER_CONDITION0 &ConditionLoopback::condition() const
{
	return *reinterpret_cast<FWPM_FILTER_CONDITION0 *>(m_assembled.data());
}

}
