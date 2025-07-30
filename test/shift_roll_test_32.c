#include "../include/log.h"

#define __STATIC__ extern
//#define __INLINE__ inline

#include <stdio.h>

#include "../include/shift_roll_32.h"

/* **** */

#include <assert.h>
#include <stdint.h>
#include <stdio.h>

/* **** */

#define LOG_ASSERT(_expect, _test, _action) \
	({ \
		typeof(_action) _result = _action; \
		unsigned fail = !(_expect _test _result); \
		const char* pass_fail[2] = { "PASS", "FAIL" }; \
		\
		LOG_START("[ %s ] -- ", pass_fail[fail]); \
		LOG_END(#_expect " " #_test " (0x%08x <-- " #_action ")", _result); \
		\
		if(fail) { \
			assert(_expect _test _result); \
		} \
	})

/* **** */

static void _test_asr32(void) {
	LOG("asr");
	LOG_ASSERT(0x00000001, ==, asr32(0x00000001, 0));
	LOG_ASSERT(0x00000000, ==, asr32(0x00000001, 1));
	LOG_ASSERT(0x20000000, ==, asr32(0x40000000, 1));
	LOG_ASSERT(0x08000000, ==, asr32(0x40000000, 3));
	LOG_ASSERT(0x00000001, ==, asr32(0x40000000, 30));
	LOG_ASSERT(0xc0000000, ==, asr32(0x80000000, 1));
	LOG_ASSERT(0xffff0000, ==, asr32(0x80000000, 15));
	LOG_ASSERT(0xfffffffe, ==, asr32(0x80000000, 30));
	LOG_ASSERT(0xffffffff, ==, asr32(0x80000000, 31));
	LOG_ASSERT(0xffffffff, ==, asr32(0x80000000, 32));
}

static void _test_asr32_vc(void) {
	int32_t out_c = 0;

	LOG("asr_c");
	LOG_ASSERT(0x00000001, ==, asr32_vc(0x00000001, 0, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);
	LOG_ASSERT(0xffffffff, ==, asr32_vc(0xffffffff, 0, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);
	LOG_ASSERT(0x00000000, ==, asr32_vc(0x00000001, 1, &out_c));
	LOG_ASSERT(0x00000001, ==, out_c);
	LOG_ASSERT(0x00000001, ==, asr32_vc(0x40000000, 30, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);
	LOG_ASSERT(0x00000000, ==, asr32_vc(0x40000000, 31, &out_c));
	LOG_ASSERT(0x00000001, ==, out_c);
	LOG_ASSERT(0x00000000, ==, asr32_vc(0x40000000, 32, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);
	LOG_ASSERT(0xffffffff, ==, asr32_vc(0x80000000, 31, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);
	LOG_ASSERT(0xffffffff, ==, asr32_vc(0x80000000, 32, &out_c));
	LOG_ASSERT(0x00000001, ==, out_c);

	LOG_ASSERT(0x10101010, ==, asr32_vc(0x10101010, 0, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);
	LOG_ASSERT(0x08080808, ==, asr32_vc(0x10101010, 1, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);
	LOG_ASSERT(0x04040404, ==, asr32_vc(0x10101010, 2, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);
	LOG_ASSERT(0x18080808, ==, asr32_vc(0x30101010, 1, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);
	LOG_ASSERT(0xc8080808, ==, asr32_vc(0x90101010, 1, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);
}

static void _test_lsl(void) {
	LOG("lsl");
	LOG_ASSERT(0x00000001, ==, lsl32(0x00000001, 0));
	LOG_ASSERT(0x00000002, ==, lsl32(0x00000001, 1));
	LOG_ASSERT(0x00010000, ==, lsl32(0x00000001, 16));
	LOG_ASSERT(0x40000000, ==, lsl32(0x00000001, 30));
	LOG_ASSERT(0x80000000, ==, lsl32(0x00000001, 31));
	LOG_ASSERT(0x00000000, ==, lsl32(0x00000001, 32));

	LOG_ASSERT(0x80000001, ==, lsl32(0x80000001, 0));
	LOG_ASSERT(0x00000002, ==, lsl32(0x80000001, 1));
	LOG_ASSERT(0x00000100, ==, lsl32(0x80000001, 8));
	LOG_ASSERT(0x00010000, ==, lsl32(0x80000001, 16));
	LOG_ASSERT(0x40000000, ==, lsl32(0x80000001, 30));
	LOG_ASSERT(0x80000000, ==, lsl32(0x80000001, 31));
	LOG_ASSERT(0x00000000, ==, lsl32(0x80000001, 32));

	LOG_ASSERT(0x80018001, ==, lsl32(0x80018001, 0));
	LOG_ASSERT(0x00030002, ==, lsl32(0x80018001, 1));
	LOG_ASSERT(0x01800100, ==, lsl32(0x80018001, 8));
	LOG_ASSERT(0x80010000, ==, lsl32(0x80018001, 16));
	LOG_ASSERT(0x40000000, ==, lsl32(0x80018001, 30));
	LOG_ASSERT(0x80000000, ==, lsl32(0x80018001, 31));
	LOG_ASSERT(0x00000000, ==, lsl32(0x80018001, 32));
}

static void	_test_lsl_vc(void) {
	uint32_t out_c = 0;

	LOG("lsl_c");
	LOG_ASSERT(0x80000001, ==, lsl32_vc(0x80000001, 0, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);
	LOG_ASSERT(0x00000002, ==, lsl32_vc(0x80000001, 1, &out_c));
	LOG_ASSERT(0x00000001, ==, out_c);
	LOG_ASSERT(0x80000000, ==, lsl32_vc(0x80000001, 31, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);
	LOG_ASSERT(0x00000000, ==, lsl32_vc(0x80000001, 32, &out_c));
	LOG_ASSERT(0x00000001, ==, out_c);
	LOG_ASSERT(0x00000000, ==, lsl32_vc(0x80000001, 33, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);

	LOG_ASSERT(0x80808080, ==, lsl32_vc(0x80808080, 0, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);
	LOG_ASSERT(0x01010100, ==, lsl32_vc(0x80808080, 1, &out_c));
	LOG_ASSERT(0x00000001, ==, out_c);
	LOG_ASSERT(0x02020200, ==, lsl32_vc(0x80808080, 2, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);
}

static void _test_lsr32(void) {
	LOG("lsr");
	LOG_ASSERT(0x00000001, ==, lsr32(0x00000001, 0));
	LOG_ASSERT(0x00000001, ==, lsr32(0x00000002, 1));
	LOG_ASSERT(0x00001000, ==, lsr32(0x10000000, 16));
	LOG_ASSERT(0x00000001, ==, lsr32(0x40000000, 30));
	LOG_ASSERT(0x00000001, ==, lsr32(0x80000000, 31));
	LOG_ASSERT(0x00000000, ==, lsr32(0x80000000, 32));

	LOG_ASSERT(0x80000001, ==, lsr32(0x80000001, 0));
	LOG_ASSERT(0x40000000, ==, lsr32(0x80000001, 1));
	LOG_ASSERT(0x00800000, ==, lsr32(0x80000001, 8));
	LOG_ASSERT(0x00008000, ==, lsr32(0x80000001, 16));
	LOG_ASSERT(0x00000002, ==, lsr32(0x80000001, 30));
	LOG_ASSERT(0x00000000, ==, lsr32(0x80000001, 32));

	LOG_ASSERT(0x80018001, ==, lsr32(0x80018001, 0));
	LOG_ASSERT(0x4000c000, ==, lsr32(0x80018001, 1));
	LOG_ASSERT(0x00800180, ==, lsr32(0x80018001, 8));
	LOG_ASSERT(0x00008001, ==, lsr32(0x80018001, 16));
	LOG_ASSERT(0x00000002, ==, lsr32(0x80018001, 30));
	LOG_ASSERT(0x00000001, ==, lsr32(0x80018001, 31));
	LOG_ASSERT(0x00000000, ==, lsr32(0x80018001, 32));
}

static void	_test_lsr32_vc(void) {
	uint32_t out_c = 0;

	LOG("lsr_c");
	LOG_ASSERT(0x80000001, ==, lsr32_vc(0x80000001, 0, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);
	LOG_ASSERT(0x40000000, ==, lsr32_vc(0x80000001, 1, &out_c));
	LOG_ASSERT(0x00000001, ==, out_c);
	LOG_ASSERT(0x00000001, ==, lsr32_vc(0x80000001, 31, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);
	LOG_ASSERT(0x00000000, ==, lsr32_vc(0x80000001, 32, &out_c));
	LOG_ASSERT(0x00000001, ==, out_c);
	LOG_ASSERT(0x00000000, ==, lsr32_vc(0x80000001, 33, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);

	LOG_ASSERT(0x00808080, ==, lsr32_vc(0x01010101, 1, &out_c));
	LOG_ASSERT(0x00000001, ==, out_c);
	LOG_ASSERT(0x00404040, ==, lsr32_vc(0x01010101, 2, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);
	LOG_ASSERT(0x00202020, ==, lsr32_vc(0x01010101, 3, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);
}

static void _test_rol32(void) {
	LOG("rol");
	LOG_ASSERT(0x80000001, ==, rol32(0x80000001, 0));
	LOG_ASSERT(0x00000003, ==, rol32(0x80000001, 1));
	LOG_ASSERT(0x00000006, ==, rol32(0x80000001, 2));
	LOG_ASSERT(0x0000000c, ==, rol32(0x80000001, 3));
	LOG_ASSERT(0x00000180, ==, rol32(0x80000001, 8));
	LOG_ASSERT(0x00018000, ==, rol32(0x80000001, 16));
	LOG_ASSERT(0x18000000, ==, rol32(0x80000001, 28));
	LOG_ASSERT(0x60000000, ==, rol32(0x80000001, 30));
	LOG_ASSERT(0xc0000000, ==, rol32(0x80000001, 31));
}

static void _test_ror32(void) {
	LOG("ror");
	LOG_ASSERT(0x80000001, ==, ror32(0x80000001, 0));
	LOG_ASSERT(0xc0000000, ==, ror32(0x80000001, 1));
	LOG_ASSERT(0x60000000, ==, ror32(0x80000001, 2));
	LOG_ASSERT(0x30000000, ==, ror32(0x80000001, 3));
	LOG_ASSERT(0x01800000, ==, ror32(0x80000001, 8));
	LOG_ASSERT(0x00018000, ==, ror32(0x80000001, 16));
	LOG_ASSERT(0x00000018, ==, ror32(0x80000001, 28));
	LOG_ASSERT(0x0000000c, ==, ror32(0x80000001, 29));
	LOG_ASSERT(0x00000006, ==, ror32(0x80000001, 30));
	LOG_ASSERT(0x00000003, ==, ror32(0x80000001, 31));
}

static uint32_t bstring(uint32_t data, char* p) {
	uint8_t bits = sizeof(data) << 3;
	char* dst = p;

	for(unsigned i = 1; i <= bits; i++) {
		uint8_t bit = (bits - i);
		*dst++ = ((data >> bit) & 1) ? '1' : '0';
	}

	*dst = 0;

	return(data);
}

#if 0
static void _test_ror32_c(void) {
	char bso[33];
	unsigned cout = 0;

	for(unsigned i = 0; i <= sizeof(uint32_t) << 3; i++) {
//		unsigned cin = (cout = 0 & i & 1);
		unsigned cin = i & 1;
//		LOG("%01u -- 0x%08x -- %s -- %01u", cin, bstring(ror32_c(-2, i, cin, &cout), bso), bso, cout);
//		LOG("%01u -- 0x%08x -- %s -- %01u", 1, bstring(ror32_c(0, i, 1, &cout), bso), bso, cout);
		LOG("%01u -- 0x%08x -- %s -- %01u", cin, bstring(ror32_vc(-2, i, cin, &cout), bso), bso, cout);
		LOG("%01u -- 0x%08x -- %s -- %01u", 1, bstring(ror32_vc(0, i, 1, &cout), bso), bso, cout);
	}
}
#endif

int main(void) {
	if(1) {
		_test_asr32();
		_test_asr32_vc();
		_test_lsl();
		_test_lsl_vc();
		_test_lsr32();
		_test_lsr32_vc();
		_test_rol32();
		_test_ror32();
	}

//	_test_ror32_c();
}
