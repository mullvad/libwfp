#include "stdafx.h"
#include "binarycomposer.h"
#include "math.h"

namespace common
{

BinaryComposer::BinaryComposer(std::initializer_list<Element> elements)
{
	m_offsets.reserve(elements.size());
	m_bufferSize = 0;

	for (const Element &element: elements)
	{
		m_offsets.push_back(m_bufferSize);
		m_bufferSize += common::math::RoundNative(element.length);
	}

	// Intentionally clear buffer after allocating it
	m_buffer = std::make_unique<uint8_t[]>(m_bufferSize);

	auto raw = m_buffer.get();
	auto index = 0;

	for (const Element &element : elements)
	{
		auto offset = m_offsets[index];
		++index;

		memcpy(raw + offset, element.data, element.length);
	}
}

const std::vector<size_t> &BinaryComposer::offsets() const
{
	return m_offsets;
}

uint8_t *BinaryComposer::buffer()
{
	return m_buffer.get();
}

std::unique_ptr<Buffer> BinaryComposer::acquire()
{
	return std::unique_ptr<Buffer>(new Buffer(m_buffer.release(), m_bufferSize));
}

size_t BinaryComposer::size() const
{
	return m_bufferSize;
}

}
