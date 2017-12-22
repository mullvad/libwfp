#include "stdafx.h"
#include "ncat.h"
#include <stdexcept>

const wchar_t *Ncat::PATH = L"c:\\tools\\ncat.exe";

Ncat::Ncat(const std::wstring &args)
{
	m_nc = common::ApplicationRunner::StartDetached(PATH, args);
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
