#pragma once

#ifndef UNUSED
	static inline
	void __unused(const int vvoid, ...) {
		(void)vvoid;
	}

	#define UNUSED(...) __unused(0, __VA_ARGS__)
	#define UNUSED_FN __attribute__((unused))
#endif
