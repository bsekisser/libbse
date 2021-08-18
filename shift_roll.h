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

static inline uint32_t _rol_c(uint32_t data, int shift, int carry)
{
	int32_t cmask = _lsl(!!carry, shift - 1);
	return((_rol(data, shift) & ~cmask) | cmask);
}

static inline uint32_t _ror(uint32_t data, int shift)
{
	return(_lsl(data, -shift) | _lsr(data, shift));
}

static inline uint32_t _ror_c(uint32_t data, int shift, int carry)
{
	int32_t cmask = _lsl(!!carry, (-shift) - 1);
	return((_ror(data, shift) & ~cmask) | cmask);
}
