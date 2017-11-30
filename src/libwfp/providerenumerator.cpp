#include "stdafx.h"
#include "providerenumerator.h"
#include <stdexcept>
#include <fwpmu.h>

//static
bool ProviderEnumerator::enumerate(std::shared_ptr<FilterEngine> engine,
	std::function<bool(const FWPM_PROVIDER0&)> callback)
{
	HANDLE enumHandle = INVALID_HANDLE_VALUE;

	auto status = FwpmProviderCreateEnumHandle0(
		(*engine).session(),
		nullptr,
		&enumHandle
	);

	if (ERROR_SUCCESS != status)
	{
		throw new std::runtime_error("Unable to create enumeration context for providers");
	}

	FWPM_PROVIDER0** providers = nullptr;
	UINT32 providersReturned = 0;

	status = FwpmProviderEnum0(
		(*engine).session(),
		enumHandle,
		100,
		&providers,
		&providersReturned
	);

	if (ERROR_SUCCESS != status)
	{
		// TODO: Exception safety
		throw std::runtime_error("Unable to enumerate providers");
	}

	for (UINT32 i = 0; i < providersReturned - 1; ++i)
	{
		auto provider = *providers[i];

		if (callback(provider) == false)
		{
			return false;
		}
	}

	FwpmFreeMemory0((void**)&providers);
	FwpmProviderDestroyEnumHandle0((*engine).session(), enumHandle);

	return true;
}