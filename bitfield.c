#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#define CR() \
	printf("\n")

#define TRACE(_f, _args...) \
	printf(_f "\n", ##_args)

#define TRACE_ASSERT(_expect, _test, _action) \
	({ \
		int result = _expect _test _action; \
		TRACE("%s -- 0x%08x %s (0x%08x == %s)", result ? "pass" : "fail", \
			_expect, #_test, _action, #_action); \
		if(0) assert(result); \
	})

#include "bitfield.h"

int main(void)
{
	TRACE("0x%08x, 0x%08x, 0x%08x -- _BF(0, 9)", 511, (1 << 9) - 1, pbBF(0, 9));
	TRACE("0x%08x, 0x%08x, 0x%08x -- _BM(9)", 511, (1 << 9) - 1, _BM(9));
	TRACE("0x%08x, 0x%08x, 0x%08x -- _BV(9)", 512, (1 << 9), _BV(9));

	TRACE_ASSERT(0x00000001, ==, _BM(0));
	TRACE_ASSERT(0x00000001, ==, _BV(0));

	TRACE_ASSERT(0x00000001, ==, _BM(1));
	TRACE_ASSERT(0x00000002, ==, _BV(1));

	TRACE_ASSERT(0x000001ff, ==, _BM(9));
	TRACE_ASSERT(0x00000200, ==, _BV(9));

	TRACE_ASSERT(0x3fffffff, ==, _BM(30));
	TRACE_ASSERT(0x40000000, ==, _BV(30));

	TRACE_ASSERT(0x7fffffff, ==, _BM(31));
	TRACE_ASSERT(0x80000000, ==, _BV(31));

	TRACE_ASSERT(0xffffffff, ==, _BM(32));
	TRACE_ASSERT(0x00000001, ==, _BV(32));

	TRACE_ASSERT(0x00000020, ==, _BCLR(0xa0, 7));
	TRACE_ASSERT(0x00000080, ==, _BCLR(0xa0, 5));

	TRACE_ASSERT(0xffffffff, ==, _BMAS(-1, 7, 5));
	TRACE_ASSERT(0xffffff7f, ==, _BMAS(-1, 7, 0));

	TRACE_ASSERT(0x00000020, ==, BMOV(0x80, 7, 5));
	TRACE_ASSERT(0x00000080, ==, BMOV(0x20, 5, 7));

	TRACE_ASSERT(0xA0, ==, _BSET(0x80, 5));
	TRACE_ASSERT(0x20, ==, BTST(0xa0, 5));


	/* test singular bit operations */


	/* test bitfield operations */

	TRACE_ASSERT(0x000001ff, ==, pbBF(0, 9));
	TRACE_ASSERT(0x0003fe00, ==, pbBF(9, 9));

	TRACE_ASSERT(0x80000000, ==, _BFLJ(0x80, 0, 8));
	
	TRACE_ASSERT(0xfffffe00, ==, pbBFCLR(-1, 0, 9));
	TRACE_ASSERT(0xfffc01ff, ==, pbBFCLR(-1, 9, 9));

	TRACE_ASSERT(0x000000fe, ==, pbBFEXT(~0x80, 7, 8));
	TRACE_ASSERT(0xffffff80, ==, pbBFEXTs(0x80, 0, 8));

	TRACE_ASSERT(0x00000000, ==, pbBFEXTs((0x80LL << 9), 0, 8));
	TRACE_ASSERT(0xffffff80, ==, pbBFEXTs((0x80LL << 9), 9, 8));
	TRACE_ASSERT(0x0000007f, ==, pbBFEXTs((0x80LL << 9) - 1, 9, 8));

	TRACE_ASSERT(0x00000007, ==, mlBFEXT(0xfe000000, 27, 25));
}
