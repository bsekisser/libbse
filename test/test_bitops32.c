#include "test.h"

/* **** */

#include "bitops32.h"

/* **** */

static __attribute__((constructor))
void __preflight_checks(void)
{
	TEST(0x00000001, ==, _BV(0));
	TEST(0x00000002, ==, _BV(1));
	TEST(0x80000000, ==, _BV(31));
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshift-count-overflow"
	TEST(0x00000000, ==, _BV(32));
#pragma GCC diagnostic pop
	TEST(~0x00000001, ==, _BVM(0));
	TEST(~0x00000002, ==, _BVM(1));
	TEST(~0x80000000, ==, _BVM(31));
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshift-count-overflow"
	TEST(~0x00000000, ==, _BVM(32));
#pragma GCC diagnostic pop
}

static __attribute__((constructor))
void test_bclr32(void)
{
	TEST(0xfffffffe, == , bclr32(0xffffffff, 0));
	TEST(0xfffffffd, == , bclr32(0xffffffff, 1));
	TEST(0xfffffffb, == , bclr32(0xffffffff, 2));
	TEST(0xfffffff7, == , bclr32(0xffffffff, 3));
	TEST(0xffff7fff, == , bclr32(0xffffffff, 15));
	TEST(0xfffeffff, == , bclr32(0xffffffff, 16));
	TEST(0xfffdffff, == , bclr32(0xffffffff, 17));
	TEST(0xfffbffff, == , bclr32(0xffffffff, 18));
	TEST(0xf7ffffff, == , bclr32(0xffffffff, 27));
	TEST(0xefffffff, == , bclr32(0xffffffff, 28));
	TEST(0xdfffffff, == , bclr32(0xffffffff, 29));
	TEST(0xbfffffff, == , bclr32(0xffffffff, 30));
	TEST(0x7fffffff, == , bclr32(0xffffffff, 31));
	TEST(0xffffffff, == , bclr32(0xffffffff, 32));
}

static __attribute__((constructor))
void test_bext32(void)
{
	TEST(0x00000000, ==, bext32(0x00000008, 0));
	TEST(0x00000000, ==, bext32(0x00000008, 1));
	TEST(0x00000000, ==, bext32(0x00000008, 2));
	TEST(0x00000001, ==, bext32(0x00000008, 3));
	TEST(0x00000000, ==, bext32(0x80000000, 30));
	TEST(0x00000001, ==, bext32(0x80000000, 31));
	TEST(0x00000000, ==, bext32(0x80000000, 32));
}

static __attribute__((constructor))
void test_bmas32(void)
{
	TEST(0x00000000, ==, bmas32(0x00000000, 0, 0));
	TEST(0x00000001, ==, bmas32(0x00000000, 0, 1));
	TEST(0x00000001, ==, bmas32(0x00000000, 0, 2));
	TEST(0x00000002, ==, bmas32(0x00000000, 1, 1));
	TEST(0xffffffff, ==, bmas32(0xfffffffe, 0, 1));
	TEST(0xfffffffe, ==, bmas32(0xffffffff, 0, 0));
	TEST(0x7fffffff, ==, bmas32(0xffffffff, 31, 0));
	TEST(0xffffffff, ==, bmas32(0x7fffffff, 31, 1));
}

static __attribute__((constructor))
void test_bmov32(void)
{
	TEST(0x00000000, ==, bmov32(0x00000002, 0, 31));
	TEST(0x80000000, ==, bmov32(0x00000002, 1, 31));
	TEST(0x00000000, ==, bmov32(0x00000002, 1, 32));
	TEST(0x00000001, ==, bmov32(0x80000000, 31, 0));
	TEST(0x00000002, ==, bmov32(0x80000000, 31, 1));
	TEST(0x00000000, ==, bmov32(0x80000000, 32, 0));

}

static __attribute__((constructor))
void test_bset32(void)
{
	TEST(0x00000001, ==, bset32(0x00000000, 0));
	TEST(0x00000002, ==, bset32(0x00000000, 1));
	TEST(0x00000002, ==, bset32(0x00000002, 1));
	TEST(0x00000003, ==, bset32(0x00000001, 1));
	TEST(0x00008000, ==, bset32(0x00008000, 15));
	TEST(0x00018000, ==, bset32(0x00008000, 16));
	TEST(0x80008000, ==, bset32(0x00008000, 31));
	TEST(0x00008000, ==, bset32(0x00008000, 32));
}

static __attribute__((constructor))
void test_bset32_as(void)
{
	TEST(0xfffffffe, ==, bset32_as(0xfffffffe, 0, 0));
	TEST(0xffffffff, ==, bset32_as(0xfffffffe, 0, 1));
	TEST(0xffffff0f, ==, bset32_as(0xffffff0f, 4, 0));
	TEST(0xffffff1f, ==, bset32_as(0xffffff0f, 4, 1));
	TEST(0xffffff1f, ==, bset32_as(0xffffff0f, 4, 2));
	TEST(0xffffffff, ==, bset32_as(0xfffffff7, 3, 1));
}

static __attribute__((constructor))
void test_btst32(void)
{
	TEST(0x00000000, ==, btst32(0x00000008, 0));
	TEST(0x00000000, ==, btst32(0x00000008, 1));
	TEST(0x00000000, ==, btst32(0x00000008, 2));
	TEST(0x00000008, ==, btst32(0x00000008, 3));
	TEST(0x00000000, ==, btst32(0x80000000, 30));
	TEST(0x80000000, ==, btst32(0x80000000, 31));
	TEST(0x00000000, ==, btst32(0x80000000, 32));
}

static __attribute__((constructor))
void test_bxor32(void)
{
	TEST(0x00000009, ==, bxor32(0x00000008, 0));
	TEST(0x0000000a, ==, bxor32(0x00000008, 1));
	TEST(0x0000000c, ==, bxor32(0x00000008, 2));
	TEST(0x00000000, ==, bxor32(0x00000008, 3));
	TEST(0xc0000000, ==, bxor32(0x80000000, 30));
	TEST(0x00000000, ==, bxor32(0x80000000, 31));
	TEST(0x80000000, ==, bxor32(0x80000000, 32));
}
