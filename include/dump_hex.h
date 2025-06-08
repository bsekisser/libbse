#pragma once

/* **** */

#include <stdint.h>

/* **** */

void dump_hex(void *const p, const uint32_t ppa, const unsigned count, const unsigned span, const unsigned ascii);
void dump_hex_line(void *const p, const uint32_t base, const uint32_t pos, const unsigned count, const unsigned ascii);
