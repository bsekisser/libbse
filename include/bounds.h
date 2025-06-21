#pragma once

static inline
unsigned _in_bounds(const unsigned check, const unsigned size, const unsigned min, const unsigned max)
{
	return((check >= min) && (check <= (max - size)));
}

#define in_bounds(_check, _size, _min, _max) \
	_in_bounds((unsigned)_check, (unsigned)_size, (unsigned)_min, (unsigned)_max)
