#pragma once

/* **** */

#include "bitops.h"
#include "bitfield_pb.h"

/* msb-to-lsb bitfield operations */

#define lmBITSR(_lsb, _msb) \
	(1 + (_msb - _lsb))

#define lmBFEXTR(_data, _lsb, _msb)					pbBFEXTR(_data, _msb, lmBITSR(_lsb, _msb))
#define lmBFEXTRs(_data, _lsb, _msb)				pbBFEXTRs(_data, _msb, lmBITSR(_lsb, _msb))
#define lmBFMOVRs(_data, _lsb, _msb, _to)			pbBFMOVRs(_data, _msb, lmBITSR(_lsb, _msb), _to)
