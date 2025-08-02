#pragma once

/* **** */

#include "bitfield_macros.h"
#include "bitops32.h"
#include "shift_roll_macros.h"

/* **** */

#include <stdint.h>

/* **** */

static inline
uint32_t _bitfield32_pb_bfclr(const uint32_t data, const unsigned pos, const unsigned bits)
{ return((data) & pbBFC(pos, bits)); }

static inline
uint32_t _bitfield32_pb_bfext(const uint32_t data, const unsigned pos, const unsigned bits)
{ return(_LSR(data, pos) & _BM(bits)); }

static inline
uint32_t _bitfield32_pb_bfins(uint32_t data, uint32_t ins, const unsigned pos, const unsigned bits) {
	data = _bitfield32_pb_bfclr(data, pos, bits);
	ins = _bitfield32_pb_bfext(ins, 0, bits);
	data |= _LSL(ins, pos);
	return(data);
}
