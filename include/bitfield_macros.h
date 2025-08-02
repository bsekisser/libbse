#pragma once

/* **** */

#include "bitop_macros.h"
#include "shift_roll_macros.h"

/* **** */

#define pbBF(_pos, _bits)						(_LSL(_BM(_bits), _pos))
#define pbBFC(_pos, _bits)						(~pbBF(_pos, _bits))
#define pbBFR(_pos, _bits)						(_LSL_MASKED(_BM(_bits), ~(_pos)))
