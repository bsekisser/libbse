#define _ASR(_data, _bits)						_LSR((signed)_data, _bits)
#define _LSL(_data, _bits)						((_data) << ((_bits) & 0x1f))
#define _LSR(_data, _bits)						((_data) >> ((_bits) & 0x1f))


#define MSB_LSB_TO_BITS(_msb, _lsb) \
	(1 + (_msb - _lsb))

#define MSB_LSB_TO_POS(_msb, _lsb) \
	_lsb

#define MSB_LSB_TO_POS_BITS(_msb, _lsb) \
	MSB_LSB_TO_POS(_msb, _lsb), MSB_LSB_TO_BITS(_msb, _lsb)

/* singular bit operations */

#define _BV(_bit)								_LSL(1U, _bit)

#define _BCLR(_data, _bit)						((_data) & ~_BV(_bit))
#define BCLR(_data, _bit)						(_data = _BCLR(_data, _bit))

#define BEXT(_data, _bit)						(_LSR(_data, _bit) & 1)

#define BMAS(_data, _bit, _set) \
		BSET_AS(_BCLR(_data, _bit), _bit, _set)

#define BMOV(_data, _from, _to)					_LSL(BEXT(_data, _from), _to)

#define BSET(_data, _bit)						((_data) |= _BV(_bit))
#define _BSET_AS(_data, _bit, _set)				((_data) | _LSL(!!(_set), _bit))
#define BSET_AS(_data, _bit, _set)				(_data = _BSET_AS(_data, _bit, _set))

#define BTST(_data, _bit)						((_data) & _BV(_bit))

/* bitfield operations */

#define __BF(_pos, _bits)						(_LSL(_BM(_bits), _pos))
#define _BFC(_pos, _bits)						(~__BF(_pos, _bits))
#define _BFLJ(_data, _pos, _bits)				_LSL(_data, -((_pos) + (_bits)))

#define _MLBF(_msb, _lsb)						__BF(_lsb, MSB_LSB_TO_BITS(_msb, _lsb))
#define _MLBFC(_data, _msb, _lsb)				xBFCLR(_data, _lsb, MSB_LSB_TO_BITS(_msb, _lsb))
#define _MLBFI(_data, _src, _msb, _lsb)			xBFINS(_data, _src, _lsb, MSB_LSB_TO_BITS(_msb, _lsb))
#define _MLBFMOV(_data, _msb, _lsb, _to)		xBFMOV(_data, _lsb, MSB_LSB_TO_BITS(_msb, _lsb), _to)
#define _MLBFSEXT(_data, _msb, _lsb)			xBFEXTs(_data, _lsb, MSB_LSB_TO_BITS(_msb, _lsb))
#define _MLBFTST(_data, _msb, _lsb)				xBFTST(_data, _lsb, MSB_LSB_TO_BITS(_msb, _lsb))
#define _MLBFX(_data, _msb, _lsb)				xBFEXT(_data, _lsb, MSB_LSB_TO_BITS(_msb, _lsb))

#define _BM(_bits)								(~_LSL(~0U, _bits))

#define xBFCLR(_data, _pos, _bits)				((_data) & _BFC(_pos, _bits))
#define xBFEXT(_data, _pos, _bits)				(_LSR(_data, _pos) & _BM(_bits))
#define xBFEXTs(_data, _pos, _bits)				_ASR(_BFLJ(_data, _pos, _bits), -_bits)
#define xBFINS(_data, _ins, _pos, _bits)		(xBFCLR(_data, _pos, _bits) | _LSL(xBFEXT(_ins, 0, _bits), _pos))

#define xBFMOV(_data, _pos, _bits, _to)			_LSL(xBFEXT(_data, _pos, _bits), _to)
#define xBFTST(_data, _pos, _bits)				((_data) & __BF(_pos, _bits))

#define _BF __BF
#define BFCLR(_data, _pos, _bits) xBFCLR(_data, _pos, _bits)
#define BFEXT(_data, _pos, _bits) xBFEXT(_data, _pos, _bits)
#define BFEXTS(_data, _pos, _bits) xBFEXTs(_data, _pos, _bits)
