#pragma once

#include <cstdint>

namespace common
{

class Buffer
{
public:

	uint8_t *data;
	size_t size;

	Buffer(void *d, size_t s)
		: data(reinterpret_cast<uint8_t *>(d)), size(s)
	{
	}

	Buffer()
		: data(nullptr), size(0)
	{
	}

	Buffer(size_t s)
		: data(new uint8_t[s]), size(s)
	{
	}

	~Buffer()
	{
		delete[] data;
	}

private:

	Buffer(const Buffer &);
	Buffer &operator=(const Buffer &);
};

struct BorrowedBuffer
{
	uint8_t *data;
	size_t size;
};

}
