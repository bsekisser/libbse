//#pragma once

#ifndef _DEBUG
	#warning _DEBUG flag unset
	#define _DEBUG 0
#endif

#define DEBUG(_x) if(_DEBUG) { _x; }
