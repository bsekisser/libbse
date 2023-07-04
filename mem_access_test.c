#include "mem_access_be.h"
#include "mem_access_le.h"

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
	test_mem_access_be();
	test_mem_access_le();

	return(0);
}
