#pragma once

#ifndef ___PASTE
	#define ___PASTE(a,b) a##b
#endif

#ifndef __PASTE
	#define __PASTE(a,b) ___PASTE(a,b)
#endif
