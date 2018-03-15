#pragma once

#include "memory.h"
#include <windows.h>
#include <memory>
#include <string>

namespace common
{

class ApplicationRunner
{
	ApplicationRunner(const std::wstring &path, const std::wstring &args, DWORD creationFlags);

public:

	static std::unique_ptr<ApplicationRunner> StartDetached(const std::wstring &path, const std::wstring &args);
	static std::unique_ptr<ApplicationRunner> StartWithoutConsole(const std::wstring &path, const std::wstring &args);

	bool read(std::string &data, size_t maxChars, size_t timeout);
	bool write(const std::string &data);

	bool join(DWORD &status, size_t timeout);

private:

	ApplicationRunner(const ApplicationRunner &) = delete;
	ApplicationRunner &operator=(const ApplicationRunner &) = delete;

	static std::wstring CreateCommandLine(const std::wstring &path, const std::wstring &args);
	void createPipes();

	struct ReadThreadParameters
	{
		std::string &data;
		size_t maxChars;
		HANDLE stdOutRead;
		HANDLE readCompletedEvent;
	};

	static unsigned __stdcall ReadThread(void *p);

	typedef std::unique_ptr<HANDLE, memory::HandleDeleter> UniqueHandle;

	DWORD m_processId;
	UniqueHandle m_process;

	UniqueHandle m_stdInRead;
	UniqueHandle m_stdInWrite;
	UniqueHandle m_stdOutRead;
	UniqueHandle m_stdOutWrite;
};

}
