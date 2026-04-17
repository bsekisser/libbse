#include "paste.h"
#include "shift_roll_macros.h"
#include "static_inline.h"

/* **** */

#define __SHIFT_TYPE_SIGNED_REF const __SHIFT_TYPE_SIGNED
#define __SHIFT_TYPE_UNSIGNED_REF const __SHIFT_TYPE_UNSIGNED

/* **** */

#define __SHIFT(_) __PASTE(_,__SHIFT_BITSv)
#define __SHIFT_ACTION_CARRY(_sa, _f) ({ if(p2carry_out) *p2carry_out = __SHIFT_C(_f)(v, _sa); return(__SHIFT(_f)(v, sa)); })
#define __SHIFT_C(_) __PASTE(__SHIFT(_),_c)
#define __SHIFT_MASKED(_) __PASTE(__SHIFT(_),_masked)
#define __SHIFT_V(_) __PASTE(__SHIFT(_),_v)
#define __SHIFT_VC(_) __PASTE(__SHIFT_V(_),c)

/* **** */

#define __SHIFTs_FN(_lname, _uname) \
	__STATIC__ __INLINE__ \
	__SHIFT_TYPE_UNSIGNED __SHIFT(_lname)(__SHIFT_TYPE_SIGNED_REF v, const unsigned sa) \
	{ return(_##_uname(v, sa)); }

#define __SHIFTs_C_FN(_lname, _uname) \
	__STATIC__ __INLINE__ \
	__SHIFT_TYPE_UNSIGNED __SHIFT_C(_lname)(__SHIFT_TYPE_SIGNED_REF v, const unsigned sa) \
	{ return(sa ? _##_uname##_C(v, sa) : 0); }

#define __SHIFTs_VC_FN(_lname) \
	__STATIC__ __INLINE__ \
	__SHIFT_TYPE_UNSIGNED __SHIFT_VC(_lname)(__SHIFT_TYPE_SIGNED_REF v, const unsigned sa, unsigned *const p2carry_out) \
	{ __SHIFT_ACTION_CARRY(sa, _lname); }

/* **** */

__SHIFTs_FN(asr, ASR)
__SHIFTs_C_FN(asr, ASR)
__SHIFTs_VC_FN(asr)

/* **** */

#define __SHIFTu_FN(_lname, _uname) \
	__STATIC__ __INLINE__ \
	__SHIFT_TYPE_UNSIGNED __SHIFT(_lname)(__SHIFT_TYPE_UNSIGNED_REF v, const unsigned sa) \
	{ return(_##_uname(v, sa)); }

#define __SHIFTu_C_FN(_lname, _uname) \
	__STATIC__ __INLINE__ \
	__SHIFT_TYPE_UNSIGNED __SHIFT_C(_lname)(__SHIFT_TYPE_UNSIGNED_REF v, const unsigned sa) \
	{ return(_##_uname##_C(v, sa)); }

#define __SHIFTu_MASKED_FN(_lname, _uname) \
	__STATIC__ __INLINE__ \
	__SHIFT_TYPE_UNSIGNED __SHIFT_MASKED(_lname)(__SHIFT_TYPE_UNSIGNED_REF v, const unsigned sa) \
	{ return(_##_uname##_MASKED(v, sa)); }

#define __SHIFTu_VC_FN(_lname) \
	__STATIC__ __INLINE__ \
	__SHIFT_TYPE_UNSIGNED __SHIFT_VC(_lname)(__SHIFT_TYPE_UNSIGNED_REF v, const unsigned sa, unsigned *const p2carry_out) \
	{ __SHIFT_ACTION_CARRY(sa, _lname); }

/* **** */

__SHIFTu_FN(lsl, LSL)
__SHIFTu_C_FN(lsl, LSL)
__SHIFTu_MASKED_FN(lsl, LSL)
__SHIFTu_VC_FN(lsl)

/* **** */

__SHIFTu_FN(lsr, LSR)
__SHIFTu_C_FN(lsr, LSR)
__SHIFTu_MASKED_FN(lsr, LSR)
__SHIFTu_VC_FN(lsr)

/* **** */

__SHIFTu_FN(rol, ROL)
__SHIFTu_C_FN(rol, ROL)
__SHIFTu_VC_FN(rol)

/* **** */

__SHIFTu_FN(ror, ROR)
__SHIFTu_C_FN(ror, ROR)
__SHIFTu_VC_FN(ror)

/* **** */

__STATIC__ __INLINE__
__SHIFT_TYPE_UNSIGNED __SHIFT_C(rrx)(__SHIFT_TYPE_UNSIGNED_REF v)
{ return(_RRX_C(v)); }

__STATIC__ __INLINE__
__SHIFT_TYPE_UNSIGNED __SHIFT_V(rrx)(__SHIFT_TYPE_UNSIGNED_REF v, const unsigned carry_in)
{ return(_RRX_V(v, carry_in)); }
