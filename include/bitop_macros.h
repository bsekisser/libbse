// NOTE, TODO: !!! #pragma once does not work here !!!

#ifndef __BITOP_MACROS__
#define __BITOP_MACROS__

/* **** */

#include "shift_roll_macros.h"

/* **** helpers */

#define _BV(_bit) _BV_AS(_bit, 1U)
#define _BV_AS(_bit, _as) _LSL((unsigned)!!(_as), _bit)
#define _BVM(_bit) (~_BV(_bit))

/* **** base bit operation macros */

#define _BCLR(_data, _bit) ((_data) & _BVM(_bit))
#define _BEXT(_data, _bit) (_LSR(_data, _bit) & 1U)
#define _BMAS(_data, _bit, _set) ((_set) ? _BSET(_data, _bit) : _BCLR(_data, _bit))
#define _BMOV(_data, _from, _to) _LSL(_BEXT(_data, _from), _to)
#define _BSET(_data, _bit) _BSET_AS(_data, _bit, 1U)
#define _BSET_AS(_data, _bit, _as) ((_data) | _BV_AS(_bit, _as))
#define _BTST(_data, _bit) ((_data) & _BV(_bit))
#define _BXMI(_dst, _dst_bit, _src, _src_bit) (_BCLR(_dst, _dst_bit) | _BMOV(_src, _src_bit, _dst_bit))
#define _BXOR(_data, _bit) ((_data) ^ _BV(_bit))

/* **** compatibility and writeback macros */

#define BCLR(_data, _bit) ((_data) = _BCLR(_data, _bit))
#define BEXT _BEXT
#define BMAS(_data, _bit, _set) ((_data) = _BMAS(_data, _bit, _set))
#define BMOV _BMOV
#define BSET(_data, _bit) ((_data) = _BSET(_data, _bit))
#define BSET_AS(_data, _bit, _as) ((_data) = _BSET_AS(_data, _bit, _as))
#define BTST _BTST
#define BXMI(_dst, _dst_bit, _src, _src_bit) ((_dst) = _BXMI(_dst, _dst_bit, _src, _src_bit))
#define BXCG(_data, _bit, _set) ({ typeof(_data) _out = _data; BMAS(_data, _bit, _set); _BEXT(_out, _bit); })
#define BXOR(_data, _bit) ((_data) = _BXOR(_data, _bit))

#endif // __BITOP_MACROS__
