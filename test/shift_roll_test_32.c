#include "test.h"

#include "../include/shift_roll_32.h"

/* **** */

static __attribute__((constructor))
void test_asr32(void)
{
	TEST(0x00000001, ==, asr32(0x00000001, 0));
	TEST(0x00000000, ==, asr32(0x00000001, 1));
	TEST(0x20000000, ==, asr32(0x40000000, 1));
	TEST(0x08000000, ==, asr32(0x40000000, 3));
	TEST(0x00000001, ==, asr32(0x40000000, 30));
	TEST(0xc0000000, ==, asr32(0x80000000, 1));
	TEST(0xffff0000, ==, asr32(0x80000000, 15));
	TEST(0xfffffffe, ==, asr32(0x80000000, 30));
	TEST(0xffffffff, ==, asr32(0x80000000, 31));
	TEST(0xffffffff, ==, asr32(0x80000000, 32));
}

static __attribute__((constructor))
void test_asr32_vc(void)
{
	unsigned out_c = 0;

	TEST(0x00000001, ==, asr32_vc(0x00000001, 0, &out_c));
	TEST(0x00000000, ==, out_c);
	TEST(0xffffffff, ==, asr32_vc(0xffffffff, 0, &out_c));
	TEST(0x00000000, ==, out_c);
	TEST(0x00000000, ==, asr32_vc(0x00000001, 1, &out_c));
	TEST(0x00000001, ==, out_c);
	TEST(0x00000001, ==, asr32_vc(0x40000000, 30, &out_c));
	TEST(0x00000000, ==, out_c);
	TEST(0x00000000, ==, asr32_vc(0x40000000, 31, &out_c));
	TEST(0x00000001, ==, out_c);
	TEST(0x00000000, ==, asr32_vc(0x40000000, 32, &out_c));
	TEST(0x00000000, ==, out_c);
	TEST(0xffffffff, ==, asr32_vc(0x80000000, 31, &out_c));
	TEST(0x00000000, ==, out_c);
	TEST(0xffffffff, ==, asr32_vc(0x80000000, 32, &out_c));
	TEST(0x00000001, ==, out_c);

	TEST(0x10101010, ==, asr32_vc(0x10101010, 0, &out_c));
	TEST(0x00000000, ==, out_c);
	TEST(0x08080808, ==, asr32_vc(0x10101010, 1, &out_c));
	TEST(0x00000000, ==, out_c);
	TEST(0x04040404, ==, asr32_vc(0x10101010, 2, &out_c));
	TEST(0x00000000, ==, out_c);
	TEST(0x18080808, ==, asr32_vc(0x30101010, 1, &out_c));
	TEST(0x00000000, ==, out_c);
	TEST(0xc8080808, ==, asr32_vc(0x90101010, 1, &out_c));
	TEST(0x00000000, ==, out_c);
}

static __attribute__((constructor))
void test_lsl(void)
{
	TEST(0x00000001, ==, lsl32(0x00000001, 0));
	TEST(0x00000002, ==, lsl32(0x00000001, 1));
	TEST(0x00010000, ==, lsl32(0x00000001, 16));
	TEST(0x40000000, ==, lsl32(0x00000001, 30));
	TEST(0x80000000, ==, lsl32(0x00000001, 31));
	TEST(0x00000000, ==, lsl32(0x00000001, 32));

	TEST(0x80000001, ==, lsl32(0x80000001, 0));
	TEST(0x00000002, ==, lsl32(0x80000001, 1));
	TEST(0x00000100, ==, lsl32(0x80000001, 8));
	TEST(0x00010000, ==, lsl32(0x80000001, 16));
	TEST(0x40000000, ==, lsl32(0x80000001, 30));
	TEST(0x80000000, ==, lsl32(0x80000001, 31));
	TEST(0x00000000, ==, lsl32(0x80000001, 32));

	TEST(0x80018001, ==, lsl32(0x80018001, 0));
	TEST(0x00030002, ==, lsl32(0x80018001, 1));
	TEST(0x01800100, ==, lsl32(0x80018001, 8));
	TEST(0x80010000, ==, lsl32(0x80018001, 16));
	TEST(0x40000000, ==, lsl32(0x80018001, 30));
	TEST(0x80000000, ==, lsl32(0x80018001, 31));
	TEST(0x00000000, ==, lsl32(0x80018001, 32));
}

static __attribute__((constructor))
void test_lsl_vc(void)
{
	unsigned out_c = 0;

	TEST(0x80000001, ==, lsl32_vc(0x80000001, 0, &out_c));
	TEST(0x00000000, ==, out_c);
	TEST(0x00000002, ==, lsl32_vc(0x80000001, 1, &out_c));
	TEST(0x00000001, ==, out_c);
	TEST(0x80000000, ==, lsl32_vc(0x80000001, 31, &out_c));
	TEST(0x00000000, ==, out_c);
	TEST(0x00000000, ==, lsl32_vc(0x80000001, 32, &out_c));
	TEST(0x00000001, ==, out_c);
	TEST(0x00000000, ==, lsl32_vc(0x80000001, 33, &out_c));
	TEST(0x00000000, ==, out_c);

	TEST(0x80808080, ==, lsl32_vc(0x80808080, 0, &out_c));
	TEST(0x00000000, ==, out_c);
	TEST(0x01010100, ==, lsl32_vc(0x80808080, 1, &out_c));
	TEST(0x00000001, ==, out_c);
	TEST(0x02020200, ==, lsl32_vc(0x80808080, 2, &out_c));
	TEST(0x00000000, ==, out_c);
}

static __attribute__((constructor))
void test_lsr32(void)
{
	TEST(0x00000001, ==, lsr32(0x00000001, 0));
	TEST(0x00000001, ==, lsr32(0x00000002, 1));
	TEST(0x00001000, ==, lsr32(0x10000000, 16));
	TEST(0x00000001, ==, lsr32(0x40000000, 30));
	TEST(0x00000001, ==, lsr32(0x80000000, 31));
	TEST(0x00000000, ==, lsr32(0x80000000, 32));

	TEST(0x80000001, ==, lsr32(0x80000001, 0));
	TEST(0x40000000, ==, lsr32(0x80000001, 1));
	TEST(0x00800000, ==, lsr32(0x80000001, 8));
	TEST(0x00008000, ==, lsr32(0x80000001, 16));
	TEST(0x00000002, ==, lsr32(0x80000001, 30));
	TEST(0x00000000, ==, lsr32(0x80000001, 32));

	TEST(0x80018001, ==, lsr32(0x80018001, 0));
	TEST(0x4000c000, ==, lsr32(0x80018001, 1));
	TEST(0x00800180, ==, lsr32(0x80018001, 8));
	TEST(0x00008001, ==, lsr32(0x80018001, 16));
	TEST(0x00000002, ==, lsr32(0x80018001, 30));
	TEST(0x00000001, ==, lsr32(0x80018001, 31));
	TEST(0x00000000, ==, lsr32(0x80018001, 32));
}

static __attribute__((constructor))
void test_lsr32_vc(void)
{
	unsigned out_c = 0;

	TEST(0x80000001, ==, lsr32_vc(0x80000001, 0, &out_c));
	TEST(0x00000000, ==, out_c);
	TEST(0x40000000, ==, lsr32_vc(0x80000001, 1, &out_c));
	TEST(0x00000001, ==, out_c);
	TEST(0x00000001, ==, lsr32_vc(0x80000001, 31, &out_c));
	TEST(0x00000000, ==, out_c);
	TEST(0x00000000, ==, lsr32_vc(0x80000001, 32, &out_c));
	TEST(0x00000001, ==, out_c);
	TEST(0x00000000, ==, lsr32_vc(0x80000001, 33, &out_c));
	TEST(0x00000000, ==, out_c);

	TEST(0x00808080, ==, lsr32_vc(0x01010101, 1, &out_c));
	TEST(0x00000001, ==, out_c);
	TEST(0x00404040, ==, lsr32_vc(0x01010101, 2, &out_c));
	TEST(0x00000000, ==, out_c);
	TEST(0x00202020, ==, lsr32_vc(0x01010101, 3, &out_c));
	TEST(0x00000000, ==, out_c);
}

static __attribute__((constructor))
void test_rol32(void)
{
	TEST(0x80000001, ==, rol32(0x80000001, 0));
	TEST(0x00000003, ==, rol32(0x80000001, 1));
	TEST(0x00000006, ==, rol32(0x80000001, 2));
	TEST(0x0000000c, ==, rol32(0x80000001, 3));
	TEST(0x00000180, ==, rol32(0x80000001, 8));
	TEST(0x00018000, ==, rol32(0x80000001, 16));
	TEST(0x18000000, ==, rol32(0x80000001, 28));
	TEST(0x60000000, ==, rol32(0x80000001, 30));
	TEST(0xc0000000, ==, rol32(0x80000001, 31));
}

static __attribute__((constructor))
void test_ror32(void)
{
	TEST(0x80000001, ==, ror32(0x80000001, 0));
	TEST(0xc0000000, ==, ror32(0x80000001, 1));
	TEST(0x60000000, ==, ror32(0x80000001, 2));
	TEST(0x30000000, ==, ror32(0x80000001, 3));
	TEST(0x01800000, ==, ror32(0x80000001, 8));
	TEST(0x00018000, ==, ror32(0x80000001, 16));
	TEST(0x00000018, ==, ror32(0x80000001, 28));
	TEST(0x0000000c, ==, ror32(0x80000001, 29));
	TEST(0x00000006, ==, ror32(0x80000001, 30));
	TEST(0x00000003, ==, ror32(0x80000001, 31));
}
