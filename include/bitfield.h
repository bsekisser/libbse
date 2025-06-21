#pragma once

#include "bitops.h"

/* singular bit operations */


/* **** */

/* helper bitfield operations */

#define _BFC(_pos, _bits)						(~pbBF(_pos, _bits))

#define _BF(_bits)								_LSL(~0U, _bits)
#define _BFULL(_bits)							_LSL((unsigned long long int)~0ULL, _bits)
#define _BM(_bits)								(~_BF(_bits))
#define _BMULL(_bits)							(~_BFULL(_bits))

#include "bitfield_ml.h"
#include "bitfield_pb.h"

/* **** */

#define BFXsASR(_p2data, _bits) _bitfield_xs_asr(_p2data, _bits)
static inline
signed _bitfield_xs_asr(signed *const p2data, const unsigned bits) {
	const signed data = _bitfield_pb_bfexts(*p2data, 0, bits);
	*p2data = _ASR(*p2data, bits);

	return(data);
}

#define BFXsLSR(_p2data, _bits) _bitfield_xs_lsr(_p2data, _bits)
static inline
signed _bitfield_xs_lsr(signed *const p2data, const unsigned bits) {
	const signed data = _bitfield_pb_bfexts(*p2data, 0, bits);
	*p2data = _LSR(*p2data, bits);

	return(data);
}

#define BFXuASR(_p2data, _bits) _bitfield_xu_asr(_p2data, _bits)
static inline
unsigned _bitfield_xu_asr(unsigned *const p2data, const unsigned bits) {
	const unsigned data = _bitfield_pb_bfext(*p2data, 0, bits);
	*p2data = _ASR(*p2data, bits);

	return(data);
}

#define BFXuLSR(_p2data, _bits) _bitfield_xu_lsr(_p2data, _bits)
static inline
unsigned _bitfield_xu_lsr(unsigned *const p2data, const unsigned bits) {
	const unsigned data = _bitfield_pb_bfext(*p2data, 0, bits);
	*p2data = _LSR(*p2data, bits);

	return(data);
}
