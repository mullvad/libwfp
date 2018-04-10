# Mullvad libwfp

libwfp is a C++ library for interacting with the Windows Filtering Platform (WFP). Notably, libwfp
provides builders for defining providers, filters and sets of conditions.

## Checking out the code

This repository contains a submodule, so clone it recursively:
```
git clone --recursive https://github.com/mullvad/libwfp.git
```

## Development environment

libwfp requires Visual Studio 2017. Any edition will work, e.g. Visual Studio Community 2017 is a
perfectly fine choice.

## Dependencies

The code has been implemented with minimal dependencies. The only external component (beyond what
is offered by Windows itself) is Google Test, and it's only required during development.

A forked version of Google Test is included as a submodule. There are no code changes in the fork,
only project settings have changed.

libwfp is targeted at Windows 7, 8 and 10.

## Example usage
### Fine-grained blocking of outgoing connections
``` cpp
#include "libwfp/filterengine.h"
#include "libwfp/sublayerbuilder.h"
#include "libwfp/objectinstaller.h"
#include "libwfp/conditionbuilder.h"
#include "libwfp/conditions/conditionapplication.h"
#include "libwfp/conditions/conditionportrange.h"
#include "libwfp/conditions/comparison.h"
#include "libwfp/filterbuilder.h"
#include <memory>

int main()
{
	auto engine = wfp::FilterEngine::DynamicSession();

	wfp::SublayerBuilder sublayer;

	sublayer
		.name(L"libwfp example layer")
		.weight(MAXUINT16);

	GUID sublayerGuid;

	wfp::ObjectInstaller::AddSublayer(*engine, sublayer, &sublayerGuid);

	// Conditions are checked against the specified layer
	// To verify that they're compatible
	wfp::ConditionBuilder conditions(FWPM_LAYER_ALE_AUTH_CONNECT_V4);

	// Match on application
	conditions.add_condition(std::make_unique<wfp::conditions::ConditionApplication>( \
		L"c:\\windows\\system32\\svchost.exe"));

	// Match remote ports outside given range
	conditions.add_condition(wfp::conditions::ConditionPortRange::Remote( \
		0, 1023, wfp::conditions::CompareNeq()));

	wfp::FilterBuilder filter;

	filter
		.name(L"Svchost peer filter")
		.description(L"Block comms with remote services outside the well-known port range")
		.layer(FWPM_LAYER_ALE_AUTH_CONNECT_V4)
		.sublayer(sublayerGuid)
		.weight(wfp::FilterBuilder::WeightClass::Max)
		.block();

	wfp::ObjectInstaller::AddFilter(*engine, filter, conditions);

	//
	// <More code here>
	//

    return 0;
}
```

# License

Copyright (C) 2018 Amagicom AB

Permission to use the code, documentation and contents is granted under the conditions of the MIT
license.

For the full license agreement, see the LICENSE.md file.
