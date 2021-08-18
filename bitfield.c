#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#define CR() \
	printf("\n")

#define TRACE(_f, _args...) \
	printf(_f "\n", ##_args)

#include "bitfield.h"

int main(void)
{
	TRACE("0x%08x, 0x%08x, 0x%08x -- _BF(0, 9)", 511, (1 << 9) - 1, _BF(0, 9));
	TRACE("0x%08x, 0x%08x, 0x%08x -- _BM(9)", 511, (1 << 9) - 1, _BM(9));
	TRACE("0x%08x, 0x%08x, 0x%08x -- _BV(9)", 512, (1 << 9), _BV(9));

	TRACE("0x%08x == BCLR(0xa0, 7)", BCLR(0xa0, 7));
	TRACE("0x%08x == BCLR(0xa0, 5)", BCLR(0xa0, 5));
	TRACE("0x%08x == BMAS(-1, 7, 5)", BMAS(-1, 7, 5));
	TRACE("0x%08x == BMAS(-1, 7, 0)", BMAS(-1, 7, 0));
	TRACE("0x%08x == BMOV(0x80, 7, 5)", BMOV(0x80, 7, 5));
	TRACE("0x%08x == BSET(0x80, 5)", BSET(0x80, 5));
	TRACE("0x%08x == BSET(0x80, 5)%08x", BSET(0x80, 5));
	TRACE("0x%08x == BTST(0xa0, 5)", BTST(0xa0, 5));

	assert(511 == _BF(0, 9));
	assert(511 == _BM(9));
	assert(512 == _BV(9));

	/* test singular bit operations */

	assert(0x20 == BCLR(0xa0, 7));
	assert(0x80 == BCLR(0xa0, 5));
	assert(0xffffffff == BMAS(-1, 7, 5));
	assert(0xffffff7f == BMAS(-1, 7, 0));
	assert(0x20 == BMOV(0x80, 7, 5));
	assert(0x80 == BMOV(0x20, 5, 7));
	assert(0xA0 == BSET(0x80, 5));
	assert(0x20 == BTST(0xa0, 5));

	/* test bitfield operations */

	TRACE("0x%08x == _BM(9)", _BM(9));
	TRACE("0x%08x == _BF(0, 9)", _BF(0, 9));
	TRACE("0x%08x == _BF(9, 9)", _BF(9, 9));

	TRACE("0x%08x == _BFLJ(0x80, 0, 8)", _BFLJ(0x80, 0, 8));
	

	TRACE("0x%08x == BFCLR(-1, 0, 9)", BFCLR(-1, 0, 9));
	TRACE("0x%08x == BFCLR(-1, 9, 9)", BFCLR(-1, 9, 9));
	TRACE("0x%08x == BFEXT(~0x80, 7, 8)", BFEXT(~0x80, 7, 8));
	TRACE("0x%08x == BFEXTS(0x80, 0, 8)", BFEXTS(0x80, 0, 8));
	int32_t i = 0x80 << 9;
	TRACE("0x%08x == BFEXTS(0x%08x, 0, 8)", BFEXTS(i, 0, 8), i);
	TRACE("0x%08x == BFEXTS(0x%08x, 9, 8)", BFEXTS(i, 9, 8), i);
	TRACE("0x%08x == BFEXTS(0x%08x, 9, 8)", BFEXTS(i - 1, 9, 8), i - 1);

	i = 0x7f << 25;
	TRACE("0x%08x == _MLBFX(0x%08x, 27, 25)", _MLBFX(i, 27, 25), i);


	assert(0x000001ff == _BF(0, 9));
	assert(0x0003fe00 == _BF(9, 9));
	assert(0x80000000 == _BFLJ(0x80, 0, 8));
	assert(0xfffffe00 == BFCLR(-1, 0, 9));
	assert(0xfffc01ff == BFCLR(-1, 9, 9));
	assert(0x000000fe == BFEXT(~0x80, 7, 8));
	assert(0xffffff80 == BFEXTS(0x80, 0, 8));
	assert(0x00000000 == BFEXTS((0x80LL << 9), 0, 8));
	assert(0xffffff80 == BFEXTS((0x80LL << 9), 9, 8));
	assert(0x0000007f == BFEXTS((0x80LL << 9) - 1, 9, 8));

//	assert(511 == BFEXT(-1, 8, 0));
}
