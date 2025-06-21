#pragma once

/* **** */

#ifndef __BV
	#define __BV(_x) (sizeof(_x) << 3)
#endif

#ifndef __BM
	#define __BM(_x) (__BV(_x) - 1)
#endif

/* **** */

extern inline
int abs(int v)
{ return(v ^ (v >> __BM(v))); }

extern inline
long labs(long v)
{ return(v ^ (v >> __BM(v))); }

extern inline
long long llabs(long long v)
{ return(v ^ (v >> __BM(v))); }
