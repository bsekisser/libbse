#pragma once

/* **** */

#include "bitops.h"
#include "bitfield_pb.h"

/* **** */

#define mlBITS(_msb, _lsb) \
	(1 + (_msb - _lsb))

/* msb-to-lsb bitfield operations */

#define mlBF(_msb, _lsb)						pbBF(_lsb, mlBITS(_msb, _lsb))
#define mlBFCLR(_data, _msb, _lsb)				pbBFCLR(_data, _lsb, mlBITS(_msb, _lsb))
#define mlBFEXT(_data, _msb, _lsb)				pbBFEXT(_data, _lsb, mlBITS(_msb, _lsb))
#define mlBFEXTs(_data, _msb, _lsb)				pbBFEXTs(_data, _lsb, mlBITS(_msb, _lsb))
#define mlBFINS(_data, _src, _msb, _lsb)		pbBFINS(_data, _src, _lsb, mlBITS(_msb, _lsb))
#define mlBFBIC_MAS(_data, _src, _msb, _lsb)	pbBFBIC_MAS(_data, _src, _lsb, mlBITS(_msb, _lsb))
#define mlBFMOV(_data, _msb, _lsb, _to)			pbBFMOV(_data, _lsb, mlBITS(_msb, _lsb), _to)
#define mlBFMOVs(_data, _msb, _lsb, _to)		pbBFMOVs(_data, _lsb, mlBITS(_msb, _lsb), _to)
#define mlBFTST(_data, _msb, _lsb)				pbBFTST(_data, _lsb, mlBITS(_msb, _lsb))

