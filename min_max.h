#pragma once

#define MIN(_lsb, _msb) \
	({ \
		__typeof__(_lsb)__lsb = _lsb; \
		__typeof__(_msb)__msb = _msb; \
		\
		((__lsb < __msb) ? __lsb : __msb); \
	})

#define MAX(_lsb, _msb) \
	({ \
		__typeof__(_lsb)__lsb = _lsb; \
		__typeof__(_msb)__msb = _msb; \
		\
		((__lsb > __msb) ? __lsb : __msb); \
	})
