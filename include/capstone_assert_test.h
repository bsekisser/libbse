#define ucs_assert_abort_msg(_test, _f, ...) \
	({ \
		if((_test)) \
		{ \
			LOG(_f, ##__VA_ARGS__); \
			abort(); \
		} \
	})

#define ucs_assert_err(_ucs, _expect, _test) \
	({ \
		const _ucs ## _err __err = (_test); \
		ucs_assert_abort_msg(__err != _expect, "%s", _ucs ## _strerror(__err)); \
	})

#define cs_assert_success(_err)		ucs_assert_err(cs, CS_ERR_OK, _err)
#define uc_assert_success(_err)		ucs_assert_err(uc, UC_ERR_OK, _err)
