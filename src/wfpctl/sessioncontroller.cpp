#include "stdafx.h"
#include "sessioncontroller.h"
#include "libwfp/objectinstaller.h"
#include "libwfp/objectdeleter.h"

namespace
{

template<typename T>
void RemoveElements(T &container, size_t count)
{
	if (container.size() == count)
	{
		container.clear();
		return;
	}

	auto end = container.begin();
	std::advance(end, count);

	container.erase(container.begin(), end);
}

} // anonymous namespace

bool SessionController::addProvider(wfp::FilterEngine &engine, wfp::ProviderBuilder &providerBuilder)
{
	GUID key;

	auto status = wfp::ObjectInstaller::AddProvider(engine, providerBuilder, &key);

	if (status)
	{
		m_providers.push_back(key);
	}

	return status;
}

bool SessionController::addSublayer(wfp::FilterEngine &engine, wfp::SublayerBuilder &sublayerBuilder)
{
	GUID key;

	auto status = wfp::ObjectInstaller::AddSublayer(engine, sublayerBuilder, &key);

	if (status)
	{
		m_sublayers.push_back(key);
	}

	return status;
}

bool SessionController::addFilter(wfp::FilterEngine &engine, wfp::FilterBuilder &filterBuilder, wfp::ConditionBuilder &conditionBuilder)
{
	UINT64 id;

	auto status = wfp::ObjectInstaller::AddFilter(engine, filterBuilder, conditionBuilder, &id);

	if (status)
	{
		m_filters.push_back(id);
	}

	return status;
}

void SessionController::resetSession(wfp::FilterEngine &engine)
{
	resetFilters(engine);
	resetSublayers(engine);
	resetProviders(engine);
}

void SessionController::resetFilters(wfp::FilterEngine &engine)
{
	auto deleted = 0;

	try
	{
		for (auto id : m_filters)
		{
			wfp::ObjectDeleter::DeleteFilter(engine, id);
			++deleted;
		}
	}
	catch (...)
	{
		RemoveElements(m_filters, deleted);
		throw;
	}

	RemoveElements(m_filters, deleted);
}

void SessionController::resetProviders(wfp::FilterEngine &engine)
{
	auto deleted = 0;

	try
	{
		for (const auto &id : m_providers)
		{
			wfp::ObjectDeleter::DeleteProvider(engine, id);
			++deleted;
		}
	}
	catch (...)
	{
		RemoveElements(m_providers, deleted);
		throw;
	}

	RemoveElements(m_providers, deleted);
}

void SessionController::resetSublayers(wfp::FilterEngine &engine)
{
	auto deleted = 0;

	try
	{
		for (const auto &id : m_sublayers)
		{
			wfp::ObjectDeleter::DeleteSublayer(engine, id);
			++deleted;
		}
	}
	catch (...)
	{
		RemoveElements(m_sublayers, deleted);
		throw;
	}

	RemoveElements(m_sublayers, deleted);
}
