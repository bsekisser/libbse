#pragma once

/* **** */

#define _BF(_bits) _LSL(~0U, _bits)
#define _BM(_bits) (~_BF(_bits))
#define _BV(_bit) _LSL(1U, _bit)
