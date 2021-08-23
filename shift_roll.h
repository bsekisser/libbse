static inline int32_t _asr(int32_t data, int shift)
{
	return(data >> (shift & 0x1f));
}

static inline uint32_t _lsl(uint32_t data, int shift)
{
	return(data << (shift & 0x1f));
}

static inline uint32_t _lsr(uint32_t data, int shift)
{
	return(data >> (shift & 0x1f));
}

static inline uint32_t _rol(uint32_t data, int shift)
{
	return(_lsl(data, shift) | _lsr(data, -shift));
}

static inline uint32_t _rol_c(uint32_t data, int shift, int cin, int* cout)
{
	int32_t cmask = _lsl(!!carry, shift - 1);
	uint32_t dout = _rol(data, shift);

	if(cout)
		*cout = !!(dout & cmask);

	return((dout & ~cin) | cin);
}

static inline uint32_t _ror(uint32_t data, int shift)
{
	return(_lsl(data, -shift) | _lsr(data, shift));
}

static inline uint32_t _ror_c(uint32_t data, int shift, int cin, int* cout)
{
	int32_t cmask = _lsl(!!carry, (-shift) - 1);
	uint32_t dout = _ror(data, shift);

	if(cout)
		*cout = !!(dout & cmask);

	return((dout & ~cin) | cin);
}
