#pragma once

#include <functional>
#include <memory>
#include "FilterEngine.h"

namespace wfp
{

class Transaction
{
public:

	Transaction(std::shared_ptr<FilterEngine> engine, bool readWrite);
	~Transaction();
	void abort();

	static bool RunReadWrite(std::shared_ptr<FilterEngine> engine, std::function<bool()> operation);
	static bool RunReadOnly(std::shared_ptr<FilterEngine> engine, std::function<bool()> operation);

private:

	static bool Run(std::shared_ptr<FilterEngine> engine, std::function<bool()> operation, bool readWrite);

	std::shared_ptr<FilterEngine> m_engine;
	bool m_aborted;
};

} // namespace wfp
