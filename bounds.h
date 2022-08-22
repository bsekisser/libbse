#pragma once

#ifndef uint
	typedef unsigned int uint;
#endif

static inline int _in_bounds(uint check, uint size, uint min, uint max)
{
	return((check >= min) && (check <= (max - size)));
}

#define in_bounds(_check, _size, _min, _max) \
	_in_bounds((uint)_check, (uint)_size, (uint)_min, (uint)_max)
