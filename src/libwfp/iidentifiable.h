#pragma once

#include <guiddef.h>

namespace wfp
{

struct IIdentifiable
{
	virtual ~IIdentifiable() = 0
	{
	}

	virtual const GUID &id() const = 0;
	virtual const GUID &providerId() const = 0;
};

}
