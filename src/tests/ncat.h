#pragma once

#include <libcommon/applicationrunner.h>
#include <memory>
#include <string>

class Ncat
{
public:

	enum ReturnCode
	{
		Ok = 0,
		Error = 1
	};

	static const wchar_t *PATH;

	Ncat(const std::wstring &args);
	bool write(const std::string &data);
	std::string output();
	DWORD returnCode();

private:

	std::unique_ptr<common::ApplicationRunner> m_nc;
};
