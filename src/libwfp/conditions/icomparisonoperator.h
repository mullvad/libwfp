#pragma once

#include <fwpmu.h>
#include <string>

namespace wfp::conditions {

struct IComparisonOperator
{
	virtual FWP_MATCH_TYPE op() const = 0;
	virtual std::wstring toString() const = 0;
};

struct IStrictComparison : public IComparisonOperator
{
};

struct IRelaxedComparison : public IComparisonOperator
{
};

}
