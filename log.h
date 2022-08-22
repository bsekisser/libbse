#define LOG_START(_f, ...) \
	({ \
		printf("%s:%s:%u: " _f, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__); \
	})

#define _LOG_(_f, ...) \
	({ \
		printf(_f, __VA_ARGS__); \
	})

#define LOG_END(_f, ...) \
	({ \
		printf(_f "\n", __VA_ARGS__); \
	})

#define LOG(_f, ...) \
	({ \
		printf("%s:%04u: " _f "\n", __FUNCTION__, __LINE__, __VA_ARGS__);
	})

#define LOG_ACTION(_action) \
	({ \
		LOG(#_action); \
		_action; \
	})