#define _ASR(_data, _bits)						_LSR((signed)_data, _bits)

#ifdef _SHIFT_UNMASKED
	#define _LSL(_data, _bits)						((_data) << (_bits))
	#define _LSR(_data, _bits)						((_data) >> (_bits))
#else
	#define _LSL(_data, _bits)						((_data) << ((_bits) & ((sizeof(_data) << 3) - 1)))
	#define _LSR(_data, _bits)						((_data) >> ((_bits) & ((sizeof(_data) << 3) - 1)))
#endif

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

#define _BMAS(_data, _bit, _set) \
		({ \
			typeof(_data) _ddata = _BCLR(_data, _bit); \
			BSET_AS(_ddata, _bit, _set); \
			_ddata; \
		})

#define BMAS(_data, _bit, _set)					(_data = _BMAS(_data, _bit, _set))

#define BMOV(_data, _from, _to)					_LSL(BEXT(_data, _from), _to)

#define _BSET(_data, _bit)						((_data) | _BV(_bit))
#define BSET(_data, _bit)						(_data = _BSET(_data, _bit))

#define _BSET_AS(_data, _bit, _set)				((_data) | _LSL(!!(_set), _bit))
#define BSET_AS(_data, _bit, _set)				(_data = _BSET_AS(_data, _bit, _set))

#define BTST(_data, _bit)						((_data) & _BV(_bit))

#define BXCG(_data, _bit, _set) \
		({ \
			typeof(_data) _was_set = BEXT(_data, _bit); \
			BCLR(_data, _bit); \
			if(_set) \
				BSET(_data, _bit); \
			_was_set; \
		})

/* helper bitfield operations */

#define pbBF(_pos, _bits)						(_LSL(_BM(_bits), _pos))
#define _BFC(_pos, _bits)						(~pbBF(_pos, _bits))
#define _BFLJ(_data, _pos, _bits)				_LSL(_data, -((_pos) + (_bits)))
#define _BF(_bits)								_LSL(~0U, _bits)
#define _BM(_bits)								(~_BF(_bits))

/* msb-to-lsb bitfield operations */

#define mlBF(_msb, _lsb)						pbBF(_lsb, MSB_LSB_TO_BITS(_msb, _lsb))
#define mlBFCLR(_data, _msb, _lsb)				pbBFCLR(_data, _lsb, MSB_LSB_TO_BITS(_msb, _lsb))
#define mlBFEXT(_data, _msb, _lsb)				pbBFEXT(_data, _lsb, MSB_LSB_TO_BITS(_msb, _lsb))
#define mlBFEXTs(_data, _msb, _lsb)				pbBFEXTs(_data, _lsb, MSB_LSB_TO_BITS(_msb, _lsb))
#define mlBFINS(_data, _src, _msb, _lsb)		pbBFINS(_data, _src, _lsb, MSB_LSB_TO_BITS(_msb, _lsb))
#define mlBFMOV(_data, _msb, _lsb, _to)			pbBFMOV(_data, _lsb, MSB_LSB_TO_BITS(_msb, _lsb), _to)
#define mlBFMOVs(_data, _msb, _lsb, _to)		pbBFMOVs(_data, _lsb, MSB_LSB_TO_BITS(_msb, _lsb), _to)
#define mlBFTST(_data, _msb, _lsb)				pbBFTST(_data, _lsb, MSB_LSB_TO_BITS(_msb, _lsb))

/* pos-bits bitfield operations */

#define pbBFCLR(_data, _pos, _bits)				((_data) & _BFC(_pos, _bits))
#define pbBFEXT(_data, _pos, _bits)				(_LSR(_data, _pos) & _BM(_bits))
#define pbBFEXTs(_data, _pos, _bits)			_ASR(_BFLJ(_data, _pos, _bits), -_bits)
#define pbBFINS(_data, _ins, _pos, _bits)		(pbBFCLR(_data, _pos, _bits) | _LSL(pbBFEXT(_ins, 0, _bits), _pos))
#define pbBFMOV(_data, _pos, _bits, _to)		_LSL(pbBFEXT(_data, _pos, _bits), _to)
#define pbBFMOVs(_data, _pos, _bits, _to)		_LSL(_ASR(_BFLJ(_data, _pos, _bits), -_bits), _to)
#define pbBFTST(_data, _pos, _bits)				((_data) & pbBF(_pos, _bits))
