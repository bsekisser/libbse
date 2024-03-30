	/*
	 * frequency in Hz
	 *	32 -> 32767
	 * duration in ticks
	 *  0 -> 65536
	 *  18.2 ticks / second
	 *
	 * sound blocks until finished.
	 */

void sound(qbasic_p qb, uint16_t frequency, uint16_t duration);
