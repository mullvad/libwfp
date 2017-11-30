#include "stdafx.h"
#include "sessionenumerator.h"
#include <stdexcept>
#include <fwpmu.h>

//static
bool SessionEnumerator::enumerate(
	std::shared_ptr<FilterEngine> engine,
	std::function<bool(const FWPM_SESSION0&)> callback)
{
	HANDLE enumHandle = INVALID_HANDLE_VALUE;

	auto status = FwpmSessionCreateEnumHandle0(
		(*engine).session(),
		nullptr,
		&enumHandle
	);

	if (ERROR_SUCCESS != status)
	{
		throw new std::runtime_error("Unable to create enumeration context for sessions");
	}

	FWPM_SESSION0** sessions = nullptr;
	UINT32 sessionsReturned = 0;

	status = FwpmSessionEnum0(
		(*engine).session(),
		enumHandle,
		100,
		&sessions,
		&sessionsReturned
	);

	if (ERROR_SUCCESS != status)
	{
		// TODO: Exception safety
		throw std::runtime_error("Unable to enumerate sessions");
	}

	for (UINT32 i = 0; i < sessionsReturned - 1; ++i)
	{
		auto session = *sessions[i];

		if (callback(session) == false)
		{
			return false;
		}
	}

	FwpmFreeMemory0((void**)&sessions);
	FwpmSessionDestroyEnumHandle0((*engine).session(), enumHandle);

	return true;
}
