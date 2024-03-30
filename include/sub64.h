#pragma once

static int64_t sub64(uint64_t s1, uint64_t s2) {
	uint64_t abs_diff = (s1 > s2) ? (s1 - s2) : (s2 - s1);

	assert(abs_diff <= INT64_MAX);

	return(s1 > s2) ? (int64_t)abs_diff : -(int64_t)abs_diff;
}
