#include "stdafx.h"
#include "objectdeleter.h"
#include "libcommon/error.h"

namespace wfp
{

//static
void ObjectDeleter::DeleteFilter(FilterEngine &engine, const GUID &key)
{
	auto status = FwpmFilterDeleteByKey0(
		engine.session(),
		&key
	);

	if (ERROR_SUCCESS == status || FWP_E_FILTER_NOT_FOUND == status)
	{
		return;
	}

	::common::error::Throw("Delete filter", status);
}

//static
void ObjectDeleter::DeleteProvider(FilterEngine &engine, const GUID &key)
{
	auto status = FwpmProviderDeleteByKey0(
		engine.session(),
		&key
	);

	if (ERROR_SUCCESS == status || FWP_E_PROVIDER_NOT_FOUND == status)
	{
		return;
	}

	::common::error::Throw("Delete provider", status);
}

//static
void ObjectDeleter::DeleteSublayer(FilterEngine &engine, const GUID &key)
{
	auto status = FwpmSubLayerDeleteByKey0(
		engine.session(),
		&key
	);

	if (ERROR_SUCCESS == status || FWP_E_SUBLAYER_NOT_FOUND == status)
	{
		return;
	}

	::common::error::Throw("Delete sublayer", status);
}

}
