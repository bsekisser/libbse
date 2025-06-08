#include "dump_hex.h"

/* **** */

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

/* **** */

void dump_hex(void *const p, const uint32_t ppa, const unsigned count, const unsigned span, const unsigned ascii)
{
	for(unsigned index = 0; index < count; index += span)
		dump_hex_line(&((char*)p)[index], ppa, index, span, ascii);
}

void dump_hex_line(void *const p, const uint32_t base, const uint32_t pos, const unsigned count, const unsigned ascii)
{
	if(base)
		printf("0x%08x:0x%03x:", base, pos);
	else
		printf("0x%08x:", pos);

	char out[256], *dst = out;

	for(unsigned index = 0; index < count; index++)
	{
		char c = ((char*)p)[index];

		if(ascii)
			*dst++ = isprint(c) ? c : '.';

		printf(" %02x", c);
	}

	if(ascii) {
		*dst = 0;
		printf("    --    %s\n", out);
	}
}
