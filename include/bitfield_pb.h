#pragma once

/* **** */

#include "bitops.h"

/* pos-bits bitfield helper operations */

#define pbBF(_pos, _bits)						(_LSL(_BM(_bits), _pos))
#define pbBFC(_pos, _bits)						(~pbBF(_pos, _bits))
#define pbBFR(_pos, _bits)						(_LSL_MASKED(_BM(_bits), ~(_pos)))

#define _BFLJ(_data, _pos, _bits)				__bitfield_pb_bflj(_data, _pos, _bits)
static inline
unsigned __bitfield_pb_bflj(const unsigned data, const unsigned pos, const unsigned bits)
{ return(_LSL_MASKED(data, -((pos) + (bits)))); }

#define _BFLJR(_data, _pos, _bits)				__bitfield_pb_bfljr(_data, _pos, _bits)
static inline
unsigned __bitfield_pb_bfljr(const unsigned data, const unsigned pos, const unsigned bits)
{ return(_LSL_MASKED(data, -((~pos) + (bits)))); }

/* pos-bits bitfield (primary/non dependant) operations */

#define pbBFCLR(_data, _pos, _bits)				_bitfield_pb_bfclr(_data, _pos, _bits)
static inline
unsigned _bitfield_pb_bfclr(const unsigned data, const unsigned pos, const unsigned bits)
{ return((data) & pbBFC(pos, bits)); }

#define pbBFEXT(_data, _pos, _bits)				((typeof(_data))_bitfield_pb_bfext(_data, _pos, _bits))
static inline
unsigned _bitfield_pb_bfext(const unsigned data, const unsigned pos, const unsigned bits)
{ return(_LSR(data, pos) & _BM(bits)); }

#define pbBFEXTR(_data, _pos, _bits)				((typeof(_data))_bitfield_pb_bfextr(_data, _pos, _bits))
static inline
unsigned _bitfield_pb_bfextr(const unsigned data, const unsigned pos, const unsigned bits)
{ return(_LSR_MASKED(data, ~pos) & _BM(bits)); }

#define pbBFEXTRs(_data, _pos, _bits)			((typeof(_data))_bitfield_pb_bfextrs(_data, _pos, _bits))
static inline
signed _bitfield_pb_bfextrs(unsigned data, const unsigned pos, const unsigned bits) {
	data = __bitfield_pb_bfljr(data, pos, bits);
	data = (unsigned)_ASR_MASKED((signed)data, -bits);
	return((signed)data);
}

#define pbBFEXTs(_data, _pos, _bits)			((typeof(_data))_bitfield_pb_bfexts(_data, _pos, _bits))
static inline
signed _bitfield_pb_bfexts(unsigned data, const unsigned pos, const unsigned bits) {
	data = __bitfield_pb_bflj(data, pos, bits);
	data = (unsigned)_ASR_MASKED((signed)data, -bits);
	return((signed)data);
}

#define pbBFINS(_data, _ins, _pos, _bits)		_bitfield_pb_bfins(_data, _ins, _pos, _bits)
static inline
unsigned _bitfield_pb_bfins(unsigned data, unsigned ins, const unsigned pos, const unsigned bits) {
	data = _bitfield_pb_bfclr(data, pos, bits);
	ins = _bitfield_pb_bfext(ins, 0, bits);
	data |= _LSL(ins, pos);
	return(data);
}

#define pbBFMOV(_data, _pos, _bits, _to)		_bitfield_pb_bfmov(_data, _pos, _bits, _to)
static inline
unsigned _bitfield_pb_bfmov(unsigned data, const unsigned pos, const unsigned bits, const unsigned to) {
	data = _bitfield_pb_bfext(data, pos, bits);
	data = _LSL(data, to);
	return(data);
}

#define pbBFMOVRs(_data, _pos, _bits, _to)		_bitfield_pb_bfmovrs((int)_data, _pos, _bits, _to)
static inline
signed _bitfield_pb_bfmovrs(unsigned data, const unsigned pos, const unsigned bits, const unsigned to) {
	data = (unsigned)_bitfield_pb_bfextrs(data, pos, bits);
	data = _LSL_MASKED(data, ~to);
	return((signed)data);
}

#define pbBFMOVs(_data, _pos, _bits, _to)		_bitfield_pb_bfmovs((int)_data, _pos, _bits, _to)
static inline
signed _bitfield_pb_bfmovs(unsigned data, const unsigned pos, const unsigned bits, const unsigned to) {
	data = (unsigned)_bitfield_pb_bfexts(data, pos, bits);
	data = _LSL(data, to);
	return((signed)data);
}

#define pbBFTST(_data, _pos, _bits)				_bitfield_pb_bftst(_data, _pos, _bits)
static inline
unsigned _bitfield_pb_bftst(const unsigned data, const unsigned pos, const unsigned bits)
{ return(data & pbBF(pos, bits)); }

/* **** secondary (primary dependant) operations */

#define pbBFBIC_MAS(_data, _ins, _pos, _bits)	_bitfield_pb_bfbic_mas(_data, _ins, _pos, _bits)
static inline
unsigned _bitfield_pb_bfbic_mas(unsigned data, unsigned ins, const unsigned pos, const unsigned bits) {
	data = _bitfield_pb_bfclr(data, pos, bits);
	ins = _bitfield_pb_bftst(ins, pos, bits);
	return(data | ins);
}
