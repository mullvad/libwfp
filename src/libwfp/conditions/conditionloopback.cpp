#include "stdafx.h"
#include "conditionloopback.h"
#include "libwfp/internal/conditionassembler.h"
#include <sstream>
#include <stdexcept>

using ConditionAssembler = ::wfp::internal::ConditionAssembler;

namespace
{

FWP_MATCH_TYPE TranslateComparison(FWP_MATCH_TYPE op)
{
	switch (op)
	{
	case FWP_MATCH_EQUAL:		return FWP_MATCH_FLAGS_ALL_SET;
	case FWP_MATCH_NOT_EQUAL:	return FWP_MATCH_FLAGS_NONE_SET;
	};

	throw std::logic_error("Cannot translate comparison operator");
}

} // anonymous namespace

namespace wfp::conditions {

ConditionLoopback::ConditionLoopback(const IStrictComparison &comparison)
	: m_comparison(comparison)
{
	UINT32 flags = FWP_CONDITION_FLAG_IS_LOOPBACK;

	m_assembled = ConditionAssembler::Uint32(identifier(), TranslateComparison(m_comparison.op()), flags);
}

std::wstring ConditionLoopback::toString() const
{
	std::wstringstream ss;

	ss << L"interface " << m_comparison.toString() << L" loopback";

	return ss.str();
}

const GUID &ConditionLoopback::identifier() const
{
	return FWPM_CONDITION_FLAGS;
}

const FWPM_FILTER_CONDITION0 &ConditionLoopback::condition() const
{
	return *reinterpret_cast<FWPM_FILTER_CONDITION0 *>(m_assembled.data());
}

}
