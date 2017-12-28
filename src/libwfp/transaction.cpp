#include "stdafx.h"
#include "transaction.h"
#include "libcommon/error.h"
#include <guiddef.h>
#include <fwpmu.h>

namespace wfp
{

//static
bool Transaction::Execute(FilterEngine &engine, std::function<bool()> operation)
{
	return Execute(engine, operation, true);
}

//static
bool Transaction::ExecuteReadOnly(FilterEngine &engine, std::function<bool()> operation)
{
	return Execute(engine, operation, false);
}

//static
bool Transaction::Execute(FilterEngine &engine, std::function<bool()> operation, bool readWrite)
{
	auto status = FwpmTransactionBegin0(engine.session(), (readWrite ? 0 : FWPM_TXN_READ_ONLY));

	THROW_UNLESS(ERROR_SUCCESS, status, "Initiate WFP transaction");

	bool operationResult = false;

	try
	{
		operationResult = operation();
	}
	catch (...)
	{
		// Attemp to abort and throw with inner exception if it fails
		THROW_UNLESS(ERROR_SUCCESS, FwpmTransactionAbort0(engine.session()), "Abort WFP transaction");

		// Successfully aborted so rethrow original exception
		throw;
	}

	if (operationResult)
	{
		THROW_UNLESS(ERROR_SUCCESS, FwpmTransactionCommit0(engine.session()), "Commit WFP transaction");
	}
	else
	{
		THROW_UNLESS(ERROR_SUCCESS, FwpmTransactionAbort0(engine.session()), "Abort WFP transaction");
	}

	return operationResult;
}

} // namespace wfp
