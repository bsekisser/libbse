#define __BSE_LIBRARY_TESTING__

#ifdef __BSE_LIBRARY_TESTING__
	#define __STATIC__ extern
#endif

#include "bitfield.h"
#include "bounds.h"
#include "bswap.h"
//#include "callback_list.h"
#include "cast.h"
#include "dtime.h"
#include "err_test.h"
#include "handle.h"
#include "log.h"
#include "min_max.h"
#include "on_err.h"
#include "page.h"
#include "queue.h"
#include "shift_roll.h"
#include "spinlock.h"
#include "trace.h"
#include "unused.h"

#include "callback_list.c"
#include "dtime.c"
