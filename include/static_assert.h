#pragma once

/* **** */

#ifdef __cplusplus
	#define STATIC_ASSERT static_assert
#elifndef __cplusplus
	#define STATIC_ASSERT _Static_assert
#endif
