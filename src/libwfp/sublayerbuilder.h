#pragma once

#include <guiddef.h>
#include <fwpmu.h>
#include <windows.h>
#include <functional>
#include <memory>
#include <string>

namespace wfp
{

typedef std::function<bool(FWPM_SUBLAYER0 &)> SublayerSink;

class SublayerBuilder
{
public:

	SublayerBuilder();

	SublayerBuilder &key(const GUID &key);
	SublayerBuilder &name(const std::wstring &name);
	SublayerBuilder &description(const std::wstring &description);

	SublayerBuilder &persistent();
	SublayerBuilder &provider(const GUID &provider);
	SublayerBuilder &data(const uint8_t *data, size_t size);
	SublayerBuilder &weight(UINT16 weight);

	bool build(SublayerSink sink);

private:

	SublayerBuilder(const SublayerBuilder &);
	SublayerBuilder &operator=(const SublayerBuilder &);

	FWPM_SUBLAYER0 m_sublayer;

	std::wstring m_name;
	std::wstring m_description;
	GUID m_providerKey;
	std::unique_ptr<uint8_t[]> m_data;
	size_t m_dataSize;
};

}

