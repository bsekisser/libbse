#define typeof_access(_name, _type) \
	static inline
	_type _name##_access(_type *const data, _type *const write) \
	{ \
		if(write) \
			*data = *write; \
	\
		return(*data);
	}

#if 0
	typeof_access(char, char)
	typeof_access(int, int)
	typeof_access(long, long)
	typeof_access(long_long, long long)
	typeof_access(short, short)
	typeof_access(signed, signed)
	typeof_access(unsigned, unsigned)
#endif
