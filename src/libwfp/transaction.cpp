#include "stdafx.h"
#include "transaction.h"
#include "libcommon/error.h"
#include <guiddef.h>
#include <fwpmu.h>

namespace wfp
{

Transaction::Transaction(std::shared_ptr<FilterEngine> engine, bool readWrite)
	: m_engine(engine)
	, m_aborted(false)
{
	auto status = FwpmTransactionBegin0((*engine).session(), (readWrite ? 0 : FWPM_TXN_READ_ONLY));

	THROW_UNLESS(ERROR_SUCCESS, status, "Initiate WFP transaction")
}

Transaction::~Transaction()
{
	if (m_aborted)
	{
		return;
	}

	FwpmTransactionCommit0((*m_engine).session());
}

void Transaction::abort()
{
	if (m_aborted)
	{
		return;
	}

	auto status = FwpmTransactionAbort0((*m_engine).session());

	THROW_UNLESS(ERROR_SUCCESS, status, "Abort WFP transaction")

	m_aborted = true;
}

//static
bool Transaction::RunReadWrite(std::shared_ptr<FilterEngine> engine, std::function<bool()> operation)
{
	return Run(engine, operation, true);
}

//static
bool Transaction::RunReadOnly(std::shared_ptr<FilterEngine> engine, std::function<bool()> operation)
{
	return Run(engine, operation, false);
}

//static
bool Transaction::Run(std::shared_ptr<FilterEngine> engine, std::function<bool()> operation, bool readWrite)
{
	Transaction t(engine, readWrite);

	auto status = operation();

	if (!operation())
	{
		t.abort();
	}

	return status;
}

} // namespace wfp
