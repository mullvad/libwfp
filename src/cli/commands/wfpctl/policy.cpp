#include "stdafx.h"
#include "policy.h"
#include "libcommon/string.h"
#include "wfpctl/wfpctl.h"
#include <functional>

namespace commands::wfpctl
{

namespace detail
{

WfpctlSettings CreateSettings(const std::wstring &loopback, const std::wstring &dhcp, const std::wstring &lan)
{
	WfpctlSettings s;

	s.AllowLoopback = (0 == _wcsicmp(loopback.c_str(), L"yes"));
	s.AllowDhcp = (0 == _wcsicmp(dhcp.c_str(), L"yes"));
	s.AllowLan = (0 == _wcsicmp(lan.c_str(), L"yes"));

	return s;
}

} // namespace detail

Policy::Policy(MessageSink messageSink)
	: m_messageSink(messageSink)
{
	m_dispatcher.addSubcommand
	(
		L"connecting",
		std::bind(&Policy::processConnecting, this, std::placeholders::_1)
	);

	m_dispatcher.addSubcommand
	(
		L"connected",
		std::bind(&Policy::processConnected, this, std::placeholders::_1)
	);

	m_dispatcher.addSubcommand
	(
		L"reset",
		std::bind(&Policy::processReset, this)
	);
}

std::wstring Policy::name()
{
	return L"policy";
}

std::wstring Policy::description()
{
	return L"Activate and reset policies.";
}

void Policy::handleRequest(const std::vector<std::wstring> &arguments)
{
	if (arguments.empty())
	{
		throw std::runtime_error("Missing subcommand. Cannot complete request.");
	}

	auto subcommand = arguments[0];

	auto actualArguments(arguments);
	actualArguments.erase(actualArguments.begin());

	m_dispatcher.dispatch(subcommand, actualArguments);
}

void Policy::processConnecting(const KeyValuePairs &arguments)
{
	auto settings = detail::CreateSettings
	(
		GetArgumentValue(arguments, L"loopback"),
		GetArgumentValue(arguments, L"dhcp"),
		GetArgumentValue(arguments, L"lan")
	);

	auto success = Wfpctl_ApplyPolicyConnecting
	(
		settings,
		GetArgumentValue(arguments, L"relay").c_str()
	);

	m_messageSink((success
		? L"Successfully applied policy."
		: L"Failed to apply policy."));
}

void Policy::processConnected(const KeyValuePairs &arguments)
{
	auto settings = detail::CreateSettings
	(
		GetArgumentValue(arguments, L"loopback"),
		GetArgumentValue(arguments, L"dhcp"),
		GetArgumentValue(arguments, L"lan")
	);

	auto success = Wfpctl_ApplyPolicyConnected
	(
		settings,
		GetArgumentValue(arguments, L"relay").c_str(),
		GetArgumentValue(arguments, L"tunnel").c_str()
	);

	m_messageSink((success
		? L"Successfully applied policy."
		: L"Failed to apply policy."));
}

void Policy::processReset()
{
	auto success = Wfpctl_Reset();

	m_messageSink((success
		? L"Successfully reset policy."
		: L"Failed to reset policy."));
}

}
