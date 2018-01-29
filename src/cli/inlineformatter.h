#pragma once

#include <sstream>
#include <utility>

class InlineFormatter
{
public:

	template<typename T>
	InlineFormatter &operator<<(const T &t)
	{
		m_ss << t;
		return *this;
	}

	//InlineFormatter &operator<<(std::basic_ostream &(*manip)(std::basic_ostream &))
	//{
	//	manip(m_ss);
	//	return *this;
	//}
		
	std::wstring str()
	{
		auto s = m_ss.str();

		m_ss.str(L"");
		m_ss.clear();

		return s;
	}

private:

	std::wstringstream m_ss;
};
