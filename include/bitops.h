#pragma once

/* **** */

#define __SIZEOF_DATA_BITS(_data) (sizeof(_data) << 3)
#define __SIZEOF_DATA_BITS_MASK(_data) (__SIZEOF_DATA_BITS(_data) - 1)

#define _ASR(_data, _bits)						((typeof(_data))_LSR((signed)_data, _bits))
#define _ASR_MASKED(_data, _bits)				((typeof(_data))_LSR_MASKED((signed)_data, _bits))

#define _BF(_bits)								_LSL(~0U, _bits)
#define _BM(_bits)								(~_BF(_bits))
#define _BV(_bit)								_LSL(1U, _bit)
#define _BVR(_bit)								_LSL_MASKED(1U, ~_bit)

#define _LSL(_data, _bits)						((_data) << (_bits))
#define _LSL_MASKED(_data, _bits)				_LSL(_data, (_bits) & (typeof(_bits))__SIZEOF_DATA_BITS_MASK(_data))

#define _LSR(_data, _bits)						((_data) >> (_bits))
#define _LSR_MASKED(_data, _bits)				_LSR(_data, (_bits) & (typeof(_bits))__SIZEOF_DATA_BITS_MASK(_data))

/* **** */

#define __BCLR(_data, _bit) 					(_data & ~_BV(_bit))
#define __BCLRR(_data, _bit) 					(_data & ~_BVR(~_bit))

static inline unsigned _bitop_bclr(unsigned data, unsigned bit) {
	return(__BCLR(data, bit));
}

static inline unsigned _bitop_bclrr(unsigned data, unsigned bit) {
	return(__BCLRR(data, bit));
}

#ifdef __bitfield_functions__
	#define _BCLR(_data, _bit) 					_bitop_bclr(_data, _bit)
	#define _BCLRR(_data, _bit)					_bitop_bclrr(_data, _bit)
#else
	#define _BCLR __BCLR
	#define _BCLRR __BCLRR
#endif

#define BCLR(_data, _bit)						(_data = (typeof(_data))_BCLR(_data, _bit))
#define BCLRR(_data, _bit)						(_data = (typeof(_data))_BCLRR(_data, _bit))

#define __BEXT(_data, _bit)						(_LSR(_data, _bit) & 1U)
#define __BEXTR(_data, _bit)					(_LSR_MASKED(_data, ~_bit)  & 1U)

static inline unsigned _bitop_bext(unsigned data, unsigned bit) {
	return(__BEXT(data, bit));
}

static inline unsigned _bitop_bextr(unsigned data, unsigned bit) {
	return(__BEXTR(data, bit));
}

#ifdef __bitfield_functions__
	#define BEXT(_data, _bit)					(!!_bitfield_bext(_data, _bit))
	#define BEXTR(_data, _bit)					(!!_bitfield_bextr(_data, _bit))
#else
	#define BEXT __BEXT
	#define BEXTR __BEXTR
#endif

#define __BSET_AS(_data, _bit, _set)			(_data | (typeof(_data))_LSL(!!((unsigned)(_set)), _bit))
#define __BSETR_AS(_data, _bit, _set)			(_data | (typeof(_data))_LSL_MASKED(!!((unsigned)(_set)), ~_bit))

static inline unsigned _bitop_bset_as(unsigned data, unsigned bit, unsigned set) {
	return(__BSET_AS(data, bit, set));
}

static inline unsigned _bitop_bsetr_as(unsigned data, unsigned bit, unsigned set) {
	return(__BSETR_AS(data, bit, set));
}

#ifdef __bitfield_functions__
	#define _BSET_AS(_data, _bit, _set)			_bitop_bset_as(_data, _bit, _set)
	#define _BSETR_AS(_data, _bit, _set)		_bitop_bsetr_as(_data, _bit, _set)
#else
	#define _BSET_AS __BSET_AS
	#define _BSETR_AS __BSETR_AS
#endif

#define BSET_AS(_data, _bit, _set)				(_data = (typeof(_data))_BSET_AS(_data, _bit, _set))
#define BSETR_AS(_data, _bit, _set)				(_data = (typeof(_data))_BSETR_AS(_data, _bit, _set))

/* **** */

#define _BMAS(_data, _bit, _set) _bitop_bmas(_data, _bit, _set)
static inline unsigned _bitop_bmas(unsigned data, unsigned bit, unsigned set) {
	data = _bitop_bclr(data, bit);
	data = _bitop_bset_as(data, bit, !!set);
	return(data);
}
#define BMAS(_data, _bit, _set)					(_data = (typeof(_data))_BMAS(_data, _bit, _set))

#define _BMASR(_data, _bit, _set) _bitop_bmasr(_data, _bit, _set)
static inline unsigned _bitop_bmasr(unsigned data, unsigned bit, unsigned set) {
	data = _bitop_bclrr(data, bit);
	data = _bitop_bsetr_as(data, bit, !!set);
	return(data);
}
#define BMASR(_data, _bit, _set)				(_data = (typeof(_data))_BMASR(_data, _bit, _set))
