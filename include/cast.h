#define pointer(_t) \
	typeof(_t *)

#define array(_t, _n) \
	typeof(_t [_n])

/*
 * array(pointer(char), 4) y;
 * 
 * char* [4]y;
 */
