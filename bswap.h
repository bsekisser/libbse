#pragma once

static inline uint16_t bswap16(uint16_t data)
{
	return((data >> 8) | (data << 8));
}

static inline uint32_t bswap32(uint32_t data)
{
	return(bswap16(data >> 16) | (bswap16(data) << 16));
}

static inline uint64_t bswap64(uint64_t data)
{
	return(bswap32(data >> 16) | (bswap32(data) << 16));
}
