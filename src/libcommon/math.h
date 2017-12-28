#pragma once

namespace common::math {

inline size_t RoundNative(size_t s)
{
	// sizeof(size_t) is a multiple of 2
	return ((s + sizeof(size_t) - 1) & ~(sizeof(size_t) - 1));
}

}
