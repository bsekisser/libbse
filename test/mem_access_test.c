#include "../mem_access_be.h"
#include "../mem_access_le.h"
#include "../mem_access.h"

/* **** */

#include <assert.h>
#include <endian.h>
#include <stdint.h>
#include <stdio.h>

/* **** */

#define STRINGIFY(_x) #_x
#define test_assert(_test) \
	{ \
		const char* pass_fail[2] = { "FAILED", " PASS " }; \
		const unsigned result  = _test; \
		\
		printf("[ %s ] var: 0x%08x, result: 0x%08x, expect: 0x%08x, %s\n", \
			pass_fail[result == expect], var, result, expect, STRINGIFY(_test)); \
	}

typedef unsigned char uint24_t[3];

/* **** */

void test_mem_access(void) {
	unsigned test = 0, var = 0, expect = 0, *p2var = &var;

	expect = (test = 0x12345678);
	
	mem_access(p2var, sizeof(uint32_t), &test);
	test_assert(mem_access(p2var, sizeof(uint32_t), 0));

	expect = test & 0xffff;
	test_assert(mem_32x_access(p2var, 0, sizeof(uint16_t), 0));
	
	expect = (test >> 8) & 0xffff;
	test_assert(mem_32x_access(p2var, 1, sizeof(uint16_t), 0));
	
	expect = (test >> 16) & 0xffff;
	test_assert(mem_32x_access(p2var, 2, sizeof(uint16_t), 0));

	expect = (test >> 24) & 0xffff;
	test_assert(mem_32x_access(p2var, 3, sizeof(uint16_t), 0));

	expect = test & 0xff;
	test_assert(mem_32x_access(p2var, 0, sizeof(uint8_t), 0));
	
	expect = (test >> 8) & 0xff;
	test_assert(mem_32x_access(p2var, 1, sizeof(uint8_t), 0));
	
	expect = (test >> 16) & 0xff;
	test_assert(mem_32x_access(p2var, 2, sizeof(uint8_t), 0));

	expect = (test >> 24) & 0xff;
	test_assert(mem_32x_access(p2var, 3, sizeof(uint8_t), 0));
	
	expect = (test = 0x0000beef);

	mem_access(p2var, sizeof(uint32_t), &test);
	test_assert(mem_32x_access(p2var, 0, sizeof(uint32_t), 0));

	expect |= (test = 0xdead) << 16;
	test_assert(mem_32x_access(p2var, 2, sizeof(uint16_t), &test));

	expect = (test = 0x0000beef);

	mem_access(p2var, sizeof(uint32_t), &test);
	test_assert(mem_32x_access(p2var, 0, sizeof(uint32_t), 0));

	expect |= (test = 0x34) << 16;
	test_assert(mem_32x_access(p2var, 2, sizeof(uint8_t), &test));
	
}

void test_mem_access_be(void) {
	uint32_t var = 0, expect = 0;

	expect = htobe32(var = htobe32(0x12345678));
	test_assert(mem_access_be(&var, sizeof(uint32_t), 0));

	expect >>= 8;
	test_assert(mem_access_be(&var, sizeof(uint24_t), 0));

	expect >>= 8;
	test_assert(mem_access_be(&var, sizeof(uint16_t), 0));
	
	expect >>= 8;
	test_assert(mem_access_be(&var, sizeof(uint8_t), 0));
}

void test_mem_access_le(void) {
	uint32_t var = 0, expect = 0;
	
	expect = htole32(var = htole32(0x12345678));
	test_assert(mem_access_le(&var, sizeof(uint32_t), 0));
	
	expect &= 0xffffff;
	test_assert(mem_access_le(&var, sizeof(uint24_t), 0));

	expect &= 0xffff;
	test_assert(mem_access_le(&var, sizeof(uint16_t), 0));

	expect &= 0xff;
	test_assert(mem_access_le(&var, sizeof(uint8_t), 0));
}

/* *** */

int main(void) {
	test_mem_access();
	test_mem_access_be();
	test_mem_access_le();

	return(0);
}
