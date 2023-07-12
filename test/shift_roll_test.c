#include "../log.h"

#define __STATIC__ extern
//#define __INLINE__ inline

#include <stdio.h>

#include "../shift_roll.h"

/* **** */

#include <assert.h>
#include <stdint.h>
#include <stdio.h>

/* **** */

#define LOG_ASSERT(_expect, _test, _action) \
	({ \
		unsigned _result = _action; \
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

static void _test_asr(void) {
	LOG("asr");
	LOG_ASSERT(0x00000001, ==, _asr(0x00000001, 0));
	LOG_ASSERT(0x00000000, ==, _asr(0x00000001, 1));
	LOG_ASSERT(0x20000000, ==, _asr(0x40000000, 1));
	LOG_ASSERT(0x08000000, ==, _asr(0x40000000, 3));
	LOG_ASSERT(0x00000001, ==, _asr(0x40000000, 30));
	LOG_ASSERT(0xc0000000, ==, _asr(0x80000000, 1));
	LOG_ASSERT(0xffff0000, ==, _asr(0x80000000, 15));
	LOG_ASSERT(0xfffffffe, ==, _asr(0x80000000, 30));
	LOG_ASSERT(0xffffffff, ==, _asr(0x80000000, 31));
	LOG_ASSERT(0xffffffff, ==, _asr(0x80000000, 32));
}

static void _test_asr_vc(void) {
	int32_t out_c = 0;

	LOG("asr_c");
	LOG_ASSERT(0x00000001, ==, _asr_vc(0x00000001, 0, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);
	LOG_ASSERT(0xffffffff, ==, _asr_vc(0xffffffff, 0, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);
	LOG_ASSERT(0x00000000, ==, _asr_vc(0x00000001, 1, &out_c));
	LOG_ASSERT(0x00000001, ==, out_c);
	LOG_ASSERT(0x00000001, ==, _asr_vc(0x40000000, 30, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);
	LOG_ASSERT(0x00000000, ==, _asr_vc(0x40000000, 31, &out_c));
	LOG_ASSERT(0x00000001, ==, out_c);
	LOG_ASSERT(0x00000000, ==, _asr_vc(0x40000000, 32, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);
	LOG_ASSERT(0xffffffff, ==, _asr_vc(0x80000000, 31, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);
	LOG_ASSERT(0xffffffff, ==, _asr_vc(0x80000000, 32, &out_c));
	LOG_ASSERT(0x00000001, ==, out_c);

	LOG_ASSERT(0x10101010, ==, _asr_vc(0x10101010, 0, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);
	LOG_ASSERT(0x08080808, ==, _asr_vc(0x10101010, 1, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);
	LOG_ASSERT(0x04040404, ==, _asr_vc(0x10101010, 2, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);
	LOG_ASSERT(0x18080808, ==, _asr_vc(0x30101010, 1, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);
	LOG_ASSERT(0xc8080808, ==, _asr_vc(0x90101010, 1, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);
}

static void _test_lsl(void) {
	LOG("lsl");
	LOG_ASSERT(0x00000001, ==, _lsl(0x00000001, 0));
	LOG_ASSERT(0x00000002, ==, _lsl(0x00000001, 1));
	LOG_ASSERT(0x00010000, ==, _lsl(0x00000001, 16));
	LOG_ASSERT(0x40000000, ==, _lsl(0x00000001, 30));
	LOG_ASSERT(0x80000000, ==, _lsl(0x00000001, 31));
	LOG_ASSERT(0x00000000, ==, _lsl(0x00000001, 32));

	LOG_ASSERT(0x80000001, ==, _lsl(0x80000001, 0));
	LOG_ASSERT(0x00000002, ==, _lsl(0x80000001, 1));
	LOG_ASSERT(0x00000100, ==, _lsl(0x80000001, 8));
	LOG_ASSERT(0x00010000, ==, _lsl(0x80000001, 16));
	LOG_ASSERT(0x40000000, ==, _lsl(0x80000001, 30));
	LOG_ASSERT(0x80000000, ==, _lsl(0x80000001, 31));
	LOG_ASSERT(0x00000000, ==, _lsl(0x80000001, 32));

	LOG_ASSERT(0x80018001, ==, _lsl(0x80018001, 0));
	LOG_ASSERT(0x00030002, ==, _lsl(0x80018001, 1));
	LOG_ASSERT(0x01800100, ==, _lsl(0x80018001, 8));
	LOG_ASSERT(0x80010000, ==, _lsl(0x80018001, 16));
	LOG_ASSERT(0x40000000, ==, _lsl(0x80018001, 30));
	LOG_ASSERT(0x80000000, ==, _lsl(0x80018001, 31));
	LOG_ASSERT(0x00000000, ==, _lsl(0x80018001, 32));
}

static void	_test_lsl_vc(void) {
	uint32_t out_c = 0;

	LOG("lsl_c");
	LOG_ASSERT(0x80000001, ==, _lsl_vc(0x80000001, 0, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);
	LOG_ASSERT(0x00000002, ==, _lsl_vc(0x80000001, 1, &out_c));
	LOG_ASSERT(0x00000001, ==, out_c);
	LOG_ASSERT(0x80000000, ==, _lsl_vc(0x80000001, 31, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);
	LOG_ASSERT(0x00000000, ==, _lsl_vc(0x80000001, 32, &out_c));
	LOG_ASSERT(0x00000001, ==, out_c);
	LOG_ASSERT(0x00000000, ==, _lsl_vc(0x80000001, 33, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);

	LOG_ASSERT(0x80808080, ==, _lsl_vc(0x80808080, 0, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);
	LOG_ASSERT(0x01010100, ==, _lsl_vc(0x80808080, 1, &out_c));
	LOG_ASSERT(0x00000001, ==, out_c);
	LOG_ASSERT(0x02020200, ==, _lsl_vc(0x80808080, 2, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);
}

static void _test_lsr(void) {
	LOG("lsr");
	LOG_ASSERT(0x00000001, ==, _lsr(0x00000001, 0));
	LOG_ASSERT(0x00000001, ==, _lsr(0x00000002, 1));
	LOG_ASSERT(0x00001000, ==, _lsr(0x10000000, 16));
	LOG_ASSERT(0x00000001, ==, _lsr(0x40000000, 30));
	LOG_ASSERT(0x00000001, ==, _lsr(0x80000000, 31));
	LOG_ASSERT(0x00000000, ==, _lsr(0x80000000, 32));

	LOG_ASSERT(0x80000001, ==, _lsr(0x80000001, 0));
	LOG_ASSERT(0x40000000, ==, _lsr(0x80000001, 1));
	LOG_ASSERT(0x00800000, ==, _lsr(0x80000001, 8));
	LOG_ASSERT(0x00008000, ==, _lsr(0x80000001, 16));
	LOG_ASSERT(0x00000002, ==, _lsr(0x80000001, 30));
	LOG_ASSERT(0x00000000, ==, _lsr(0x80000001, 32));

	LOG_ASSERT(0x80018001, ==, _lsr(0x80018001, 0));
	LOG_ASSERT(0x4000c000, ==, _lsr(0x80018001, 1));
	LOG_ASSERT(0x00800180, ==, _lsr(0x80018001, 8));
	LOG_ASSERT(0x00008001, ==, _lsr(0x80018001, 16));
	LOG_ASSERT(0x00000002, ==, _lsr(0x80018001, 30));
	LOG_ASSERT(0x00000001, ==, _lsr(0x80018001, 31));
	LOG_ASSERT(0x00000000, ==, _lsr(0x80018001, 32));
}

static void	_test_lsr_vc(void) {
	uint32_t out_c = 0;

	LOG("lsr_c");
	LOG_ASSERT(0x80000001, ==, _lsr_vc(0x80000001, 0, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);
	LOG_ASSERT(0x40000000, ==, _lsr_vc(0x80000001, 1, &out_c));
	LOG_ASSERT(0x00000001, ==, out_c);
	LOG_ASSERT(0x00000001, ==, _lsr_vc(0x80000001, 31, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);
	LOG_ASSERT(0x00000000, ==, _lsr_vc(0x80000001, 32, &out_c));
	LOG_ASSERT(0x00000001, ==, out_c);
	LOG_ASSERT(0x00000000, ==, _lsr_vc(0x80000001, 33, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);

	LOG_ASSERT(0x00808080, ==, _lsr_vc(0x01010101, 1, &out_c));
	LOG_ASSERT(0x00000001, ==, out_c);
	LOG_ASSERT(0x00404040, ==, _lsr_vc(0x01010101, 2, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);
	LOG_ASSERT(0x00202020, ==, _lsr_vc(0x01010101, 3, &out_c));
	LOG_ASSERT(0x00000000, ==, out_c);
}

static void _test_rol(void) {
	LOG("rol");
	LOG_ASSERT(0x80000001, ==, _rol(0x80000001, 0));
	LOG_ASSERT(0x00000003, ==, _rol(0x80000001, 1));
	LOG_ASSERT(0x00000006, ==, _rol(0x80000001, 2));
	LOG_ASSERT(0x0000000c, ==, _rol(0x80000001, 3));
	LOG_ASSERT(0x00000180, ==, _rol(0x80000001, 8));
	LOG_ASSERT(0x00018000, ==, _rol(0x80000001, 16));
	LOG_ASSERT(0x18000000, ==, _rol(0x80000001, 28));
	LOG_ASSERT(0x60000000, ==, _rol(0x80000001, 30));
	LOG_ASSERT(0xc0000000, ==, _rol(0x80000001, 31));
}

static void _test_ror(void) {
	LOG("ror");
	LOG_ASSERT(0x80000001, ==, _ror(0x80000001, 0));
	LOG_ASSERT(0xc0000000, ==, _ror(0x80000001, 1));
	LOG_ASSERT(0x60000000, ==, _ror(0x80000001, 2));
	LOG_ASSERT(0x30000000, ==, _ror(0x80000001, 3));
	LOG_ASSERT(0x01800000, ==, _ror(0x80000001, 8));
	LOG_ASSERT(0x00018000, ==, _ror(0x80000001, 16));
	LOG_ASSERT(0x00000018, ==, _ror(0x80000001, 28));
	LOG_ASSERT(0x0000000c, ==, _ror(0x80000001, 29));
	LOG_ASSERT(0x00000006, ==, _ror(0x80000001, 30));
	LOG_ASSERT(0x00000003, ==, _ror(0x80000001, 31));
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
static void _test_ror_c(void) {
	char bso[33];
	unsigned cout = 0;
	
	for(unsigned i = 0; i <= sizeof(uint32_t) << 3; i++) {
//		unsigned cin = (cout = 0 & i & 1);
		unsigned cin = i & 1;
//		LOG("%01u -- 0x%08x -- %s -- %01u", cin, bstring(_ror_c(-2, i, cin, &cout), bso), bso, cout);
//		LOG("%01u -- 0x%08x -- %s -- %01u", 1, bstring(_ror_c(0, i, 1, &cout), bso), bso, cout);
		LOG("%01u -- 0x%08x -- %s -- %01u", cin, bstring(_ror_vc(-2, i, cin, &cout), bso), bso, cout);
		LOG("%01u -- 0x%08x -- %s -- %01u", 1, bstring(_ror_vc(0, i, 1, &cout), bso), bso, cout);
	}
}
#endif

int main(void) {
	if(1) {
		_test_asr();
		_test_asr_vc();
		_test_lsl();
		_test_lsl_vc();
		_test_lsr();
		_test_lsr_vc();
		_test_rol();
		_test_ror();
	}
	
//	_test_ror_c();
}
