#define ERR_LOG(_f, ...) \
	({ \
		LOG("%s:: %s:: %04u:: %s::" _f, \
			__FILE__, \
			__FUNCTION__, \
			__LINE__, \
			strerror(errno), ##__VA_ARGS__); \
	})

#define _ERR_TEST_ABORT(_test) \
	({ \
		if((_test)) { \
			ERR_LOG("%s", #_test); \
			abort(); \
		} \
	})

#define ERR(_test) _ERR_TEST_ABORT(-1 == (_test))
#define ERR_NULL(_test) _ERR_TEST_ABORT(0 == (_test))
