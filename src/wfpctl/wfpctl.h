#pragma once

//
// WFPCTL public API
//

#ifdef WFPCTL_EXPORTS
#define WFPCTL_LINKAGE __declspec(dllexport)
#else
#define WFPCTL_LINKAGE __declspec(dllimport)
#endif

#define WFPCTL_API __stdcall

///////////////////////////////////////////////////////////////////////////////
// Structures
///////////////////////////////////////////////////////////////////////////////

#pragma pack(push, 1)

typedef struct tag_WfpctlSettings
{
	// Allow all traffic on loopback interface.
	bool AllowLoopback;

	// Allow DHCP requests and responses on all interfaces.
	bool AllowDhcp;

	// Allow all traffic to and from private address ranges.
	bool AllowLan;
}
WfpctlSettings;

#pragma pack(pop)

///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////

//
// Initialize:
//
// Call this function once at startup, to register the provider etc.
//
WFPCTL_LINKAGE
bool
WFPCTL_API
Wfpctl_Initialize();

//
// Deinitialize:
//
// Call this function once before unloading WFPCTL or exiting the process.
//
WFPCTL_LINKAGE
bool
WFPCTL_API
Wfpctl_Deinitialize();

//
// ApplyPolicyConnecting:
//
// Apply restrictions in the firewall that blocks most traffic, except:
// - What is specified by settings
// - Communication with the relay server
//
WFPCTL_LINKAGE
bool
WFPCTL_API
Wfpctl_ApplyPolicyConnecting(
	const WfpctlSettings &settings,
	const wchar_t *relayIp
);

//
// ApplyPolicyConnected:
//
// Apply restrictions in the firewall that blocks most traffic, except:
// - What is specified by settings
// - Communication with the relay server
// - Communication with the tunnel endpoint
//
WFPCTL_LINKAGE
bool
WFPCTL_API
Wfpctl_ApplyPolicyConnected(
	const WfpctlSettings &settings,
	const wchar_t *relayIp,
	const wchar_t *tunnelIp
);

//
// Reset:
//
// Clear the policy in effect, if any.
//
WFPCTL_LINKAGE
bool
WFPCTL_API
Wfpctl_Reset();
