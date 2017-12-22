#pragma once

#include <initializer_list>
#include <memory>
#include <vector>
#include "buffer.h"

namespace common
{

class BinaryComposer
{
public:

	struct Element
	{
		const void *data;
		size_t length;
	};

	BinaryComposer(std::initializer_list<Element> elements);

	const std::vector<size_t> &offsets() const;

	uint8_t *buffer();

	std::unique_ptr<Buffer> acquire();

	size_t size() const;

private:

	std::vector<size_t> m_offsets;
	std::unique_ptr<uint8_t[]> m_buffer;
	size_t m_bufferSize;
};

}
