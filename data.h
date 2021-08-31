#pragma once

/*
#define _BV(_bit) 								(1U << (_bit))
#define _BM1(_bit)								(_BV(_bit) - 1)
#define _BM2(_bit)								(~((~(uint32_t)0) << (_bit)))
#define _BM3(_bit)								((~(uint32_t)0U) >> (32 - (_bit)))
#define _BM(_bit)								(~((~0U) << ((_bit) + 1)))

#define _BF(_msb, _lsb)							(_BM((_msb) - (_lsb)) << (_lsb))

#define _BFC(_data, _msb, _lsb)					((_data) & ~_BF(_msb, _lsb))
#define _BFI(_data, _src, _msb, _lsb)			(_BFC(_data, _msb, _lsb) | (((_src) << _lsb) & _BF(_msb, _lsb)))
#define _BFX(_data, _msb, _lsb)					(((_data) >> _lsb) & _BM(_msb - _lsb))

#define BTST(_data, _bit)						((_data) & _BV(_bit))
#define BEXT(_data, _bit)						(((_data) >> (_bit)) & 1)
#define BMOV(_data, _from, _to)					(BEXT(_data, _from) << _to)

#define BMAS(_data, _bit, _set)	\
	do { \
		BCLR(_data, _bit); \
		(_data) |= (!!(_set)) << (_bit); \
	}while(0);

#define BFTST(_data, _msb, _lsb)				((_data) & _BF(_msb, _lsb))
#define BFEXT(_data, _msb, _lsb)				_BFX(_data, _msb, _lsb)
#define BFSEXT(_data, _msb, _lsb)				((((signed)_data) << (31 - _msb)) >> ((31 - _msb) + _lsb))
#define BFMOV(_data, _msb, _lsb, _to)			(_BFX(_data, _msb, _lsb) << _to)

#define BCLR(_data, _bit) 						((_data) &= ~_BV(_bit))
#define BSET(_data, _bit) 						((_data) |= _BV(_bit))


static inline uint32_t _bits(uint32_t data, uint8_t msb, uint8_t lsb)
{
	uint8_t mmsb = MAX(msb, lsb);
	uint8_t llsb = MIN(lsb, msb);
	
	uint32_t lvalue = data >> llsb;
	lvalue &= (1UL << (1 + mmsb - llsb)) - 1;
	
	return(lvalue);
}

static inline int32_t _bits_sext(int32_t data, uint8_t msb, uint8_t lsb)
{
	uint8_t mmsb = MAX(msb, lsb);
	uint8_t llsb = MIN(lsb, msb);

	uint8_t mmsbsv = (31 - mmsb);
	int32_t lvalue = ((data << mmsbsv) >> (mmsbsv + llsb));

	return(lvalue);
}
*/

static inline int _in_bounds(int check, int size, int min, int max)
{
	return((check >= min) && (check <= (max - size)));
}

#define in_bounds(_check, _size, _min, _max) \
	_in_bounds((int)_check, (int)_size, (int)_min, (int)_max)
