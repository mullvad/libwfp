#include "stdafx.h"
#include "wfpctl.h"
#include <windows.h>

WFPCTL_LINKAGE
bool
WFPCTL_API
Wfpctl_Initialize()
{
	return true;
}

WFPCTL_LINKAGE
bool
WFPCTL_API
Wfpctl_Deinitialize()
{
	return true;
}

WFPCTL_LINKAGE
bool
WFPCTL_API
Wfpctl_ApplyPolicyConnecting(
	const WfpctlSettings &settings,
	const wchar_t *relayIp
)
{
	UNREFERENCED_PARAMETER(settings);
	UNREFERENCED_PARAMETER(relayIp);

	return true;
}

WFPCTL_LINKAGE
bool
WFPCTL_API
Wfpctl_ApplyPolicyConnected(
	const WfpctlSettings &settings,
	const wchar_t *relayIp,
	const wchar_t *tunnelIp
)
{
	UNREFERENCED_PARAMETER(settings);
	UNREFERENCED_PARAMETER(relayIp);
	UNREFERENCED_PARAMETER(tunnelIp);

	return true;
}

WFPCTL_LINKAGE
bool
WFPCTL_API
Wfpctl_Reset()
{
	return true;
}
