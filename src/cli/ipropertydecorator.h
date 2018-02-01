#pragma once

//
// These methods should be used during property extraction in order to translate
// identifiers (references) into something more meaningful.
//
// Ideally we would nest a PropertyList inside a PropertyList, but that's a rather
// large update since each element in the PropertyList would need to be wrapped.
// If such an update is made one day, be sure to also add a "group" element so
// we can have better structuring within a PropertyList
//

#include <windows.h>
#include <string>

struct IPropertyDecorator
{
	// [name, first 50 chars of description]
	virtual std::wstring FilterDecoration(UINT64 id) = 0;

	// [name, first 50 chars of description]
	virtual std::wstring LayerDecoration(UINT16 id) = 0;

	virtual ~IPropertyDecorator() = 0
	{
	}
};
