#pragma once

#include "static_inline.h"

/* **** */

#define __SHIFT_BITS__(_v) (sizeof(_v) << 3)
#define __SHIFT_MASK__(_v) (__SHIFT_BITS__(_v) - 1)
#define __SHIFT_MASKED__(_v, _sa) ((_sa) & __SHIFT_MASK__(_v))

/* **** */

__STATIC__ __INLINE__
void* __asr_generic(void *const v, const unsigned size, const unsigned sa)
{
#undef __ESAC
#define __ESAC(_type) case sizeof(_type): *(_type*)v >>= sa; break

	switch(size) {
		__ESAC(char);
		__ESAC(int);
		__ESAC(long);
#if (__SIZEOF_LONG__ != __SIZEOF_LONG_LONG__)
		__ESAC(long long);
#endif
		__ESAC(short);
	}
#undef __ESAC

	return(v);
}

#define _ASR(_data, _bits) ({ typeof(_data) _data_out = _data; __asr_generic((void*)&_data_out, sizeof(_data), _bits); _data_out; })
#define _ASR_C(_data, _bits) (_ASR(_data, (_bits) - 1) & 1U)
#define _ASR_MASKED(_data, _bits) _ASR(_data, __SHIFT_MASKED__(_data, _bits))
#define _ASR_VC(_data, _bits, _carry_out) ({ _carry_out = _ASR_C(_data, _bits); _ASR(_data, _bits); })

#define _LSL(_data, _bits) ((_data) << (_bits))
#define _LSL_C(_data, _bits) (_LSR(_data, __SHIFT_BITS__(_data) - (_bits)) & 1U)
#define _LSL_MASKED(_data, _bits) _LSL(_data, __SHIFT_MASKED__(_data, _bits))
#define _LSL_VC(_data, _bits, _carry_out) ({ _carry_out = _LSL_C(_data, _bits); _LSL(_data, _bits); })

#define _LSR(_data, _bits) ((_data) >> (_bits))
#define _LSR_C(_data, _bits) (_LSR(_data, (_bits) - 1) & 1U)
#define _LSR_MASKED(_data, _bits) _LSR(_data, __SHIFT_MASKED__(_data, _bits))
#define _LSR_VC(_data, _bits, _carry_out) ({ _carry_out = _LSR_C(_data, _bits); _LSR(_data, _bits); })

#define _ROL(_data, _bits) (_LSL(_data, _bits) | _LSR_MASKED(_data, -(_bits)))
#define _ROL_C(_data, _bits) _LSL_C(_data, _bits)
#define _ROL_MASKED(_data, _bits) _ROL(_data, __SHIFT_MASKED__(_data, _bits))
#define _ROL_VC(_data, _bits, _carry_out) ({ _carry_out = _ROL_C(_data, _bits); _ROL(_data, _bits); })

#define _ROR(_data, _bits) ({ (_LSL_MASKED(_data, -(_bits)) | _LSR(_data, _bits)); })
#define _ROR_C(_data, _bits) _LSR_C(_data, _bits)
#define _ROR_VC(_data, _bits, _carry_out) ({ _carry_out = _ROR_C(_data, _bits); _ROR(_data, _bits); })

#define _RRX(_data, _carry_in, _carry_out) \
	({ \
		const unsigned __carry_out = _RRX_C(_data); \
		const typeof(_data) _result = _RRX_V(_data, _carry_in); \
		_carry_out = __carry_out; \
		_result; \
	})

#define _RRX_C(_data) (_data & 1)
#define _RRX_V(_data, _carry_in) (_LSL_MASKED(!!(_carry_in), -1) | _LSR(_data, 1))
