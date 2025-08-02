#pragma once

/* **** */

#ifndef __SHIFT_BITS__
	#define __SHIFT_BITS__(_v) (sizeof(_v) << 3)
#endif

#ifndef __SHIFT_MASK__
	#define __SHIFT_MASK__(_v) (__SHIFT_BITS__(_v) - 1)
#endif

/* **** */

#ifdef _ASR
	#define _ASR(_data, _bits) _LSR((signed)_data, _bits)
#endif

#ifdef _ASR_MASKED
	#define _ASR_MASKED(_data, _bits) _LSR_MASKED((signed)_data, _bits)
#endif

#ifndef _LSL
	#define _LSL(_data, _bits) ((_data) << (_bits))
#endif

#ifndef _LSL_MASKED
	#define _LSL_MASKED(_data, _bits) _LSL(_data, (_bits) & __SHIFT_MASK__(_data))
#endif

#ifndef _LSR
	#define _LSR(_data, _bits) ((_data) >> (_bits))
#endif

#ifndef _LSR_MASKED
	#define _LSR_MASKED(_data, _bits) _LSR(_data, (_bits) & __SHIFT_MASK__(_data))
#endif
