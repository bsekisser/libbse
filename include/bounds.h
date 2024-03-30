#pragma once

static inline unsigned _in_bounds(unsigned check, unsigned size, unsigned min, unsigned max)
{
	return((check >= min) && (check <= (max - size)));
}

#define in_bounds(_check, _size, _min, _max) \
	_in_bounds((unsigned)_check, (unsigned)_size, (unsigned)_min, (unsigned)_max)
