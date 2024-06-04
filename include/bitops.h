#pragma once

/* **** */

#define __SIZEOF_DATA_BITS(_data) (sizeof(_data) << 3)
#define __SIZEOF_DATA_BITS_MASK(_data) (__SIZEOF_DATA_BITS(_data) - 1)

#define _ASR(_data, _bits)						((typeof(_data))_LSR((signed)_data, _bits))
#define _ASR_MASKED(_data, _bits)				((typeof(_data))_LSR_MASKED((signed)_data, _bits))

#define _BF(_bits)								_LSL(~0U, _bits)
#define _BM(_bits)								(~_BF(_bits))

#define _LSL(_data, _bits)						((_data) << (_bits))
#define _LSL_MASKED(_data, _bits)				_LSL(_data, (_bits) & (typeof(_bits))__SIZEOF_DATA_BITS_MASK(_data))

#define _LSR(_data, _bits)						((_data) >> (_bits))
#define _LSR_MASKED(_data, _bits)				_LSR(_data, (_bits) & (typeof(_bits))__SIZEOF_DATA_BITS_MASK(_data))

/* **** */

#define __BEXTR(_data, _bit)					(_LSR_MASKED(_data, ~_bit)  & 1U)
#define __BEXT(_data, _bit)						(_LSR(_data, _bit) & 1U)

static inline unsigned _bitop_rbext(unsigned data, unsigned bit) {
	return(__BEXTR(data, bit));
}

static inline unsigned _bitop_bext(unsigned data, unsigned bit) {
	return(__BEXT(data, bit));
}

#ifdef __bitfield_functions__
	#define BEXTR(_data, _bit)					(!!_bitfield_rbext(_data, _bit))
	#define BEXT(_data, _bit)					(!!_bitfield_bext(_data, _bit))
#else
	#define BEXTR __BEXTR
	#define BEXT __BEXT
#endif
