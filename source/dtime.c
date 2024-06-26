
#define __GNU_SOURCE

#include "dtime.h"
#include "log.h"

/* **** */

#include <inttypes.h>
#include <time.h> // clock_gettime
#include <unistd.h> // sleep
#include <stdio.h> // printf
#include <stdint.h>

/* **** */

static uint64_t calibrate_get_dtime_loop(void)
{
	int i = 0;

	volatile uint64_t elapsedTime = 0;

	do {
		const volatile uint64_t start = get_dtime();
		elapsedTime += _get_dtime_elapsed(start);
	}while(++i < 1024);

	return(elapsedTime / i);

}

static uint64_t calibrate_get_dtime_sleep(void)
{
	const uint64_t start = get_dtime();

	sleep(1);

	return(_get_dtime_elapsed(start));
}

uint64_t dtime_calibrate(void)
{
	const uint64_t cycleTime = calibrate_get_dtime_loop();
	uint64_t elapsedTime, ecdt;
	double emhz;

	printf("%s: calibrate_get_dtime_cycles(%016" PRIu64 ")\n", __func__, cycleTime);

	elapsedTime = 0;

	for(int i = 1; i <= 3; i++) {
		elapsedTime += (calibrate_get_dtime_sleep() - cycleTime);

		ecdt = elapsedTime / i;
		emhz = (double)ecdt / MHz(1.0);
		printf("%s: elapsed time: %016" PRIu64 ", ecdt: %016" PRIu64 ", estMHz: %010.4f\n", __func__, elapsedTime, ecdt, emhz);
	}
	return(ecdt);
}
