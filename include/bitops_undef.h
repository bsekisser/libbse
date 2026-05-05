#ifndef __BITOP_MACROS__
	#error !defined(__BITOP_MACROS__)
#endif

#undef __BITOP_MACROS__

#ifndef __BITOPS_UNDEF__
	#error __BITOPS_UNDEF__
#else

#undef _BCLR
#undef _BEXT
#undef _BMAS
#undef _BMOV
#undef _BSET
#undef _BSET_AS
#undef _BTST
#undef _BXMI
#undef _BXOR

#undef BCLR
#undef BEXT
#undef BMAS
#undef BMOV
#undef BSET
#undef BSET_AS
#undef BTST
#undef BXMI
#undef BXOR

#if 0
	#undef _BV
	#undef _BV_AS
	#undef _BVM
#endif

#define __BITOPS__UNDEF__
#endif // __BITOPS_UNDEF__
#undef __BITOPS_UNDEF__
