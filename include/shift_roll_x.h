#pragma once

/* **** */

typedef shift_type_st const shift_type_stref;
typedef shift_type_ut const shift_type_utref;

/* **** */

#define ASR __PASTE(asr, __SHIFT_BITSv)
#define LSL __PASTE(lsl, __SHIFT_BITSv)
#define LSL_MASKED __PASTE(__PASTE(lsl, __SHIFT_BITSv), _masked)
#define LSR __PASTE(lsr, __SHIFT_BITSv)
#define LSR_MASKED __PASTE(__PASTE(lsr, __SHIFT_BITSv), _masked)
#define ROL __PASTE(rol, __SHIFT_BITSv)
#define ROR __PASTE(ror, __SHIFT_BITSv)
#define __RRX __PASTE(rrx, __SHIFT_BITSv)
#define RRX(_) __PASTE(__RRX, _)

#ifndef __INLINE__
	#define __INLINE__ inline
#endif

#ifndef ___PASTE
	#define ___PASTE(_a, _b) _a##_b
#endif

#ifndef __PASTE
	#define __PASTE(_a, _b) ___PASTE(_a, _b)
#endif

#ifndef __SHIFT_BITS__
	#define __SHIFT_BITS__(_v) (sizeof(_v) << 3)
#endif

#define __SHIFT_C(_lname, _v, _sa) \
	{ const unsigned __sa = _sa; (__sa ? (_lname(v, __sa - 1) & 1) : 0); }

#define __SHIFT_Cs(_lname) \
	__STATIC__ __INLINE__ \
	shift_type_st __PASTE(_lname, _c)(shift_type_stref v, const unsigned sa) \
	{ return(__SHIFT_C(_lname, v, sa)); }

#define __SHIFT_Cu(_lname) \
	__STATIC__ __INLINE__ \
	shift_type_ut __PASTE(_lname, _c)(shift_type_utref v, const unsigned sa) \
	{ return(__SHIFT_C(_lname, v, sa)); }

#define __SHIFT_MASKED(_lname, _v, _sa) \
	_lname(_v, (_sa) & __SHIFT_MASK__(_v))

#define __SHIFT_MASKEDs(_lname) \
	__STATIC__ __INLINE__ \
	shift_type_st __PASTE(_lname, _masked)(shift_type_stref v, const unsigned sa) \
	{ return(__SHIFT_MASKED(_lname, v, sa)); }

#define __SHIFT_MASKEDu(_lname) \
	__STATIC__ __INLINE__ \
	shift_type_ut __PASTE(_lname, _masked)(shift_type_utref v, const unsigned sa) \
	{ return(__SHIFT_MASKED(_lname, v, sa)); }

#ifndef __SHIFT_MASK__
	#define __SHIFT_MASK__(_v) (__SHIFT_BITS__(_v) - 1)
#endif

#ifndef __STATIC__
	#define __STATIC__ static
#endif

#define __SHIFT_VC(_carry_out, _lname, _v, _sa) \
	{ if(_carry_out) *_carry_out = _lname##_c(v, sa); _lname(v, sa); }

#define __SHIFT_VCs(_lname) \
	__STATIC__ __INLINE__ \
	shift_type_st __PASTE(_lname, _vc)(shift_type_st v, const unsigned sa, unsigned *const carry_out) \
	{ return(__SHIFT_VC(carry_out, _lname, v, sa)); }

#define __SHIFT_VCu(_lname) \
	__STATIC__ __INLINE__ \
	shift_type_utref __PASTE(_lname, _vc)(shift_type_utref v, unsigned sa, unsigned *const carry_out) \
	{ return(__SHIFT_VC(carry_out, _lname, v, sa)); }

#define __SHIFTs(_lname, _action) \
	__STATIC__ __INLINE__ \
	shift_type_st _lname(shift_type_st v, const unsigned sa) \
	{ return(_action); }

#define __SHIFTu(_lname, _action) \
	__STATIC__ __INLINE__ \
	shift_type_ut _lname(shift_type_utref v, const unsigned sa) \
	{ return(_action); }

/* **** */

__SHIFTs(ASR, v >> sa)
__SHIFT_Cs(ASR)
__SHIFT_VCs(ASR)

/* **** */

__SHIFTu(LSL, v << sa)

__STATIC__ __INLINE__
shift_type_ut __PASTE(LSL, _c)(shift_type_utref v, const unsigned sa)
{ return(sa ? !!(v & (((shift_type_ut)1) << (__SHIFT_BITS__(v) - sa))) : 0); }

__SHIFT_MASKEDu(LSL)
__SHIFT_VCu(LSL)

/* **** */

__SHIFTu(LSR, v >> sa)
__SHIFT_Cu(LSR)
__SHIFT_MASKEDu(LSR)
__SHIFT_VCu(LSR)

/* **** */

__SHIFTu(ROL, LSL(v, sa) | LSR_MASKED(v, -sa))
__SHIFT_Cu(ROL)
__SHIFT_VCu(ROL)

/* **** */

__SHIFTu(ROR, LSL_MASKED(v, -sa) | LSR(v, sa))
__SHIFT_Cu(ROR)
__SHIFT_VCu(ROR)

/* **** */

unsigned RRX(_c)(shift_type_utref v, unsigned *const carry_out);
shift_type_ut RRX(_v)(shift_type_utref v, const unsigned carry_in);

__STATIC__ __INLINE__
shift_type_ut RRX()(shift_type_utref v, const unsigned carry_in, unsigned *const carry_out)
{ (void)RRX(_c)(v, carry_out); return(RRX(_v)(v, carry_in)); }

__STATIC__ __INLINE__
unsigned RRX(_c)(shift_type_utref v, unsigned *const carry_out)
{ const unsigned c = v & 1; if(carry_out) *carry_out = c; return(c); }

__STATIC__ __INLINE__
shift_type_ut RRX(_v)(shift_type_utref v, const unsigned carry_in)
{ return(LSL(!!carry_in, __SHIFT_MASK__(v)) | LSR(v, 1)); }
