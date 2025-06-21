	/*
	 * frequency in Hz
	 *	32 -> 32767
	 * duration in ticks
	 *  0 -> 65536
	 *  18.2 ticks / second
	 *
	 * sound blocks until finished.
	 */

void sound(qbasic_ref qb, const uint16_t frequency, const uint16_t duration);
