#pragma once

#define __bitfield_functions__

#define _ASR(_data, _bits)						((typeof(_data))_LSR((signed)_data, _bits))
#define _ASR_MASKED(_data, _bits)				((typeof(_data))_LSR_MASKED((signed)_data, _bits))

#define __SIZEOF_DATA_BITS(_data) (sizeof(_data) << 3)
#define __SIZEOF_DATA_BITS_MASK(_data) (__SIZEOF_DATA_BITS(_data) - 1)

#define _LSL(_data, _bits)						((_data) << (_bits))
#define _LSR(_data, _bits)						((_data) >> (_bits))

#define _LSL_MASKED(_data, _bits)				_LSL(_data, (_bits) & (typeof(_bits))__SIZEOF_DATA_BITS_MASK(_data))
#define _LSR_MASKED(_data, _bits)				_LSR(_data, (_bits) & (typeof(_bits))__SIZEOF_DATA_BITS_MASK(_data))

#define MSB_LSB_TO_BITS(_msb, _lsb) \
	(1 + (_msb - _lsb))

#define MSB_LSB_TO_POS(_msb, _lsb) \
	_lsb

#define MSB_LSB_TO_POS_BITS(_msb, _lsb) \
	MSB_LSB_TO_POS(_msb, _lsb), MSB_LSB_TO_BITS(_msb, _lsb)

/* singular bit operations */

#define _BV(_bit)								_LSL(1U, _bit)

#define __BCLR(_data, _bit) 					(_data & ~_BV(_bit))
static inline unsigned _bitfield_bclr(unsigned data, unsigned bit) {
	return(__BCLR(data, bit));
}
#ifdef __bitfield_functions__
	#define _BCLR(_data, _bit) 					_bitfield_bclr(_data, _bit)
#else
	#define _BCLR __BCLR
#endif

#define BCLR(_data, _bit)						(_data = (typeof(_data))_BCLR(_data, _bit))

#define __BEXT(_data, _bit)					(_LSR(_data, _bit) & 1U)
static inline unsigned _bitfield_bext(unsigned data, unsigned bit) {
	return(__BEXT(data, bit));
}
#ifdef __bitfield_functions__
	#define BEXT(_data, _bit)					(!!_bitfield_bext(_data, _bit))
#else
	#define BEXT __BEXT
#endif

#define __BSET(_data, _bit)					(_data | _BV(_bit))
static inline unsigned _bitfield_bset(unsigned data, unsigned bit) {
	return(__BSET(data, bit));
}
#ifdef __bitfield_functions__
	#define _BSET(_data, _bit)					_bitfield_bset(_data, _bit)
#else
	#define _BSET __BSET
#endif

#define BSET(_data, _bit)						(_data = (typeof(_data))_BSET(_data, _bit))

#define __BSET_AS(_data, _bit, _set)			(_data | (typeof(data))_LSL(!!((unsigned)(_set)), _bit))
static inline unsigned _bitfield_bset_as(unsigned data, unsigned bit, unsigned set) {
	return(__BSET_AS(data, bit, set));
}
#ifdef __bitfield_functions__
	#define _BSET_AS(_data, _bit, _set)			_bitfield_bset_as(_data, _bit, _set)
#else
	#define _BSET_AS __BSET_AS
#endif

#define BSET_AS(_data, _bit, _set)				(_data = (typeof(_data))_BSET_AS(_data, _bit, _set))


#define __BTST(_data, _bit)					((_data) & _BV(_bit))
static inline unsigned _bitfield_btst(unsigned data, unsigned bit) {
	return(__BTST(data, bit));
}
#ifdef __bitfield_functions__
	#define BTST(_data, _bit)					_bitfield_btst(_data, _bit)
#else
	#define BTST __BTST
#endif

#define __BXOR(_data, _bit) 					((_data) ^ _BV(_bit))
static inline unsigned _bitfield_bxor(unsigned data, unsigned bit) {
	return(__BXOR(data, bit));
}
#ifdef __bitfield_functions__
	#define _BXOR(_data, _bit) 					_bitfield_bxor(_data, _bit)
#else
	#define _BXOR __BXOR
#endif

#define BXOR(_data, _bit)						(_data = _BXOR(_data, _bit))

/* **** */

static inline unsigned _bitfield_bmov(unsigned data, unsigned from, unsigned to) {
	data = _bitfield_bext(data, from);

	return(_LSL(data, to));
}
#ifdef __bitfield_functions__
	#define BMOV(_data, _from, _to)					_bitfield_bmov(_data, _from, _to)
#else
	#define BMOV(_data, _from, _to)					_LSL(BEXT(_data, _from), _to)
#endif

/* helper bitfield operations */

#define pbBF(_pos, _bits)						(_LSL(_BM(_bits), _pos))
#define _BFC(_pos, _bits)						(~pbBF(_pos, _bits))

#define _BFLJ(_data, _pos, _bits)				_bitfield_pb_bflj(_data, _pos, _bits)
static inline unsigned _bitfield_pb_bflj(unsigned data, unsigned pos, unsigned bits) {
	return(_LSL_MASKED(data, -((pos) + (bits))));
}

#define _BF(_bits)								_LSL(~0U, _bits)
#define _BFULL(_bits)							_LSL((unsigned long long int)~0ULL, _bits)
#define _BM(_bits)								(~_BF(_bits))
#define _BMULL(_bits)							(~_BFULL(_bits))

/* msb-to-lsb bitfield operations */

#define mlBF(_msb, _lsb)						pbBF(_lsb, MSB_LSB_TO_BITS(_msb, _lsb))
#define mlBFCLR(_data, _msb, _lsb)				pbBFCLR(_data, _lsb, MSB_LSB_TO_BITS(_msb, _lsb))
#define mlBFEXT(_data, _msb, _lsb)				pbBFEXT(_data, _lsb, MSB_LSB_TO_BITS(_msb, _lsb))
#define mlBFEXTs(_data, _msb, _lsb)				pbBFEXTs(_data, _lsb, MSB_LSB_TO_BITS(_msb, _lsb))
#define mlBFINS(_data, _src, _msb, _lsb)		pbBFINS(_data, _src, _lsb, MSB_LSB_TO_BITS(_msb, _lsb))
#define mlBFBIC_MAS(_data, _src, _msb, _lsb)	pbBFBIC_MAS(_data, _src, _lsb, MSB_LSB_TO_BITS(_msb, _lsb))
#define mlBFMOV(_data, _msb, _lsb, _to)			pbBFMOV(_data, _lsb, MSB_LSB_TO_BITS(_msb, _lsb), _to)
#define mlBFMOVs(_data, _msb, _lsb, _to)		pbBFMOVs(_data, _lsb, MSB_LSB_TO_BITS(_msb, _lsb), _to)
#define mlBFTST(_data, _msb, _lsb)				pbBFTST(_data, _lsb, MSB_LSB_TO_BITS(_msb, _lsb))

/* pos-bits bitfield operations */

#define pbBFCLR(_data, _pos, _bits)				_bitfield_pb_bfclr(_data, _pos, _bits)
static inline unsigned _bitfield_pb_bfclr(unsigned data, unsigned pos, unsigned bits) {
	return((data) & _BFC(pos, bits));
}

#define pbBFEXT(_data, _pos, _bits)				((typeof(_data))_bitfield_pb_bfext(_data, _pos, _bits))
static inline unsigned _bitfield_pb_bfext(unsigned data, unsigned pos, unsigned bits) {
	return(_LSR(data, pos) & _BM(bits));
}

#define pbBFEXTs(_data, _pos, _bits)			((typeof(_data))_bitfield_pb_bfexts(_data, _pos, _bits))
static inline signed _bitfield_pb_bfexts(unsigned data, unsigned pos, unsigned bits) {
	data = _bitfield_pb_bflj(data, pos, bits);
	data = (unsigned)_ASR_MASKED((signed)data, -bits);
	return((signed)data);
}

#define pbBFINS(_data, _ins, _pos, _bits)		_bitfield_pb_bfins(_data, _ins, _pos, _bits)
static inline unsigned _bitfield_pb_bfins(unsigned data, unsigned ins, unsigned pos, unsigned bits) {
	data = _bitfield_pb_bfclr(data, pos, bits);
	ins = _bitfield_pb_bfext(ins, 0, bits);
	data |= _LSL(ins, pos);
	return(data);
}

#define pbBFBIC_MAS(_data, _ins, _pos, _bits)	_bitfield_pb_bfbic_mas(_data, _ins, _pos, _bits)
static inline unsigned _bitfield_pb_bfbic_mas(unsigned data, unsigned ins, unsigned pos, unsigned bits) {
	data &= _BFC(pos, bits);
	data |= (ins & pbBF(pos, bits));
	return(data);
}

#define pbBFMOV(_data, _pos, _bits, _to)		_bitfield_pb_bfmov(_data, _pos, _bits, _to)
static inline unsigned _bitfield_pb_bfmov(unsigned data, unsigned pos, unsigned bits, unsigned to) {
	data = _bitfield_pb_bfext(data, pos, bits);
	data = _LSL(data, to);
	return(data);
}

#define pbBFMOVs(_data, _pos, _bits, _to)		_bitfield_pb_bfmovs((int)_data, _pos, _bits, _to)
static inline signed _bitfield_pb_bfmovs(unsigned data, unsigned pos, unsigned bits, unsigned to) {
	data = (unsigned)_bitfield_pb_bfexts(data, pos, bits);
	data = _LSL(data, to);
	return((signed)data);
}


#define pbBFTST(_data, _pos, _bits)				_bitfield_pb_bftst(_data, _pos, _bits)
static inline unsigned _bitfield_pb_bftst(unsigned data, unsigned pos, unsigned bits) {
	return(data & pbBF(pos, bits));
}

/* **** */

#define _BMAS(_data, _bit, _set) _bitfield_bmas(_data, _bit, _set)
static inline unsigned _bitfield_bmas(unsigned data, unsigned bit, unsigned set) {
	data = _bitfield_bclr(data, bit);
	data = _bitfield_bset_as(data, bit, !!set);
	return(data);
}
#define BMAS(_data, _bit, _set)					(_data = (typeof(_data))_BMAS(_data, _bit, _set))

#define BXCG(_data, _bit, _set) _bitfield_bxcg(_data, _bit, _set)
static inline unsigned _bitfield_bxcg(unsigned* p2data, unsigned bit, unsigned set) {
	unsigned was_set = _bitfield_bext(*p2data, bit);
	*p2data = _bitfield_bmas(*p2data, bit, !!set);
	return(was_set);
}
