#pragma once

/* **** */

#include "bitops.h"

/* pos-bits bitfield helper operations */

#define _BFLJ(_data, _pos, _bits)				__bitfield_pb_bflj(_data, _pos, _bits)
static inline unsigned __bitfield_pb_bflj(unsigned data, unsigned pos, unsigned bits) {
	return(_LSL_MASKED(data, -((pos) + (bits))));
}

#define _BFLJR(_data, _pos, _bits)				__bitfield_pb_bfljr(_data, _pos, _bits)
static inline unsigned __bitfield_pb_bfljr(unsigned data, unsigned pos, unsigned bits) {
	return(_LSL_MASKED(data, -((~pos) + (bits))));
}

/* pos-bits bitfield operations */

#define pbBFEXT(_data, _pos, _bits)				((typeof(_data))_bitfield_pb_bfext(_data, _pos, _bits))
static inline unsigned _bitfield_pb_bfext(unsigned data, unsigned pos, unsigned bits) {
	return(_LSR(data, pos) & _BM(bits));
}

#define pbBFEXTR(_data, _pos, _bits)				((typeof(_data))_bitfield_pb_bfextr(_data, _pos, _bits))
static inline unsigned _bitfield_pb_bfextr(unsigned data, unsigned pos, unsigned bits) {
	return(_LSR_MASKED(data, ~pos) & _BM(bits));
}

#define pbBFEXTRs(_data, _pos, _bits)			((typeof(_data))_bitfield_pb_bfextrs(_data, _pos, _bits))
static inline signed _bitfield_pb_bfextrs(unsigned data, unsigned pos, unsigned bits) {
	data = __bitfield_pb_bfljr(data, pos, bits);
	data = (unsigned)_ASR_MASKED((signed)data, -bits);
	return((signed)data);
}

#define pbBFEXTs(_data, _pos, _bits)			((typeof(_data))_bitfield_pb_bfexts(_data, _pos, _bits))
static inline signed _bitfield_pb_bfexts(unsigned data, unsigned pos, unsigned bits) {
	data = __bitfield_pb_bflj(data, pos, bits);
	data = (unsigned)_ASR_MASKED((signed)data, -bits);
	return((signed)data);
}

#define pbBFMOVRs(_data, _pos, _bits, _to)		_bitfield_pb_bfmovrs((int)_data, _pos, _bits, _to)
static inline signed _bitfield_pb_bfmovrs(unsigned data, unsigned pos, unsigned bits, unsigned to) {
	data = (unsigned)_bitfield_pb_bfextrs(data, pos, bits);
	data = _LSL_MASKED(data, ~to);
	return((signed)data);
}

#define pbBFMOVs(_data, _pos, _bits, _to)		_bitfield_pb_bfmovs((int)_data, _pos, _bits, _to)
static inline signed _bitfield_pb_bfmovs(unsigned data, unsigned pos, unsigned bits, unsigned to) {
	data = (unsigned)_bitfield_pb_bfexts(data, pos, bits);
	data = _LSL(data, to);
	return((signed)data);
}
