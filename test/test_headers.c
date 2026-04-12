#define __BSE_LIBRARY_TESTING__

#ifdef __BSE_LIBRARY_TESTING__
	#define __STATIC__ extern
#endif

#include "bitfield.h"
#include "bitops32.h"
#include "bitops64.h"
//#include "bitops.h" -- TODO: remove, depreciated
#include "bounds.h"
#include "bswap.h"
#include "callback_list.h"
#include "cast.h"
#include "dtime.h"
#include "err_test.h"
#include "handle.h"
#include "log.h"
#include "min_max.h"
//#include "on_err.h"
#include "page.h"
#include "queue.h"
#include "shift_roll_32.h"
#include "shift_roll_64.h"
#include "shift_roll.h"
#include "spinlock.h"
//#include "trace.h"
#include "unused.h"

#include "../source/callback_list.c"
#include "../source/dtime.c"
#include "shift_roll.c"
