#include "log.h"

#define __STATIC__ extern
//#define __INLINE__ inline

#include <stdio.h>

#ifndef uint
	typedef unsigned int uint;
#endif

#include "shift_roll.h"

/* **** */

#include <assert.h>
#include <stdint.h>
#include <stdio.h>

/* **** */

#ifndef uint
	typedef unsigned int uint;
#endif

#define LOG_ASSERT(_expect, _test, _action) \
	({ \
		uint _result = _action; \
		uint fail = !(_expect _test _result); \
		\
		LOG_START(#_expect " " #_test " (0x%08x <-- " #_action ") -- ", _result); \
		\
		if(fail) { \
			LOG_END("FAIL"); \
			assert(_expect _test _result); \
		} \
		LOG_END("PASS"); \
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

	LOG("lsl_c");
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

	for(int i = 1; i <= bits; i++) {
		uint8_t bit = (bits - i);
		*dst++ = ((data >> bit) & 1) ? '1' : '0';
	}

	*dst = 0;

	return(data);
}

#if 0
static void _test_ror_c(void) {
	char bso[33];
	uint cout = 0;
	
	for(int i = 0; i <= sizeof(uint32_t) << 3; i++) {
//		uint cin = (cout = 0 & i & 1);
		uint cin = i & 1;
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
