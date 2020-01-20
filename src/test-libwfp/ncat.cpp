#include "stdafx.h"
#include "ncat.h"
#include <stdexcept>
#include <windows.h>
#include <libcommon/string.h>

Ncat::Ncat(const std::wstring &args)
{
	m_nc = common::process::ApplicationRunner::StartDetached(Path(), args);
}

bool Ncat::write(const std::string &data)
{
	return m_nc->write(data);
}

std::string Ncat::output()
{
	std::string data;

	if (m_nc->read(data, 1000, 1000))
	{
		return data;
	}

	throw std::runtime_error("Failed to read Ncat output");
}

DWORD Ncat::returnCode()
{
	DWORD returnCode;

	if (m_nc->join(returnCode, 1000))
	{
		return returnCode;
	}

	throw std::runtime_error("Failed to read Ncat return code");
}

// static
std::wstring Ncat::Path()
{
	//
	// Current process is started from
	// x:\foo\bar\libwfp\bin\<arch>-<target>\tests.exe
	//
	// From that, we need to construct:
	// x:\foo\bar\libwfp\thirdparty\ncat\ncat.exe
	//

	wchar_t rawPath[MAX_PATH];

	if (0 == GetModuleFileNameW(NULL, rawPath, _countof(rawPath)))
	{
		throw std::runtime_error("Failed to construct path for Ncat");
	}

	std::wstring path(rawPath);

	static const auto repositoryDir = L"libwfp\\";

	auto repositoryOffset = path.rfind(repositoryDir);

	if (repositoryOffset == std::wstring::npos)
	{
		throw std::runtime_error("Failed to construct path for Ncat");
	}

	return path.substr(0, repositoryOffset + wcslen(repositoryDir))
		.append(L"thirdparty\\ncat\\ncat.exe");
}
