#pragma once

#define MIN(_v1, _v2) ((_v1 < _v2) ? _v1 : _v2)
#define MAX(_v1, _v2) ((_v1 > _v2) ? _v1 : _v2)

#if 0
	#define MIN(_lsb, _msb) \
		do { \
			uint8_t __lsb = _lsb; \
			uint8_t __msb = _msb; \
			\
			uint32_t lvalue = ((__lsb < __msb) ? __lsb : __msb); \
			(void)lvalue; \
		}while(0);

	#define MAX(_lsb, _msb) \
		do { \
			uint8_t __lsb = _lsb; \
			uint8_t __msb = _msb; \
			\
			uint32_t lvalue = ((__lsb > __msb) ? __lsb : __msb); \
			(void)lvalue; \
		}while(0);
#endif
