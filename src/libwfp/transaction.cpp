#include "stdafx.h"
#include "transaction.h"
#include <fwpmu.h>
#include <stdexcept>

namespace wfp
{

Transaction::Transaction(std::shared_ptr<FilterEngine> engine, bool readWrite)
	: m_engine(engine)
	, m_aborted(false)
{
	auto status = FwpmTransactionBegin0((*engine).session(), (readWrite ? 0 : FWPM_TXN_READ_ONLY));

	if (ERROR_SUCCESS != status)
	{
		//
		// TODO: Add code that throws runtime error with message derived from "status"/GetLastError()
		//
		if (FWP_E_TXN_IN_PROGRESS == status)
		{
			throw std::runtime_error("Cannot begin new transaction, one is already in progress");
		}

		throw std::runtime_error("Cannot begin new transaction");
	}
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

	if (ERROR_SUCCESS != status)
	{
		//
		// TODO: Specific error message as above
		//
		throw std::runtime_error("Could not abort transaction");
	}

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
