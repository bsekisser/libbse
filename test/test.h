#include "log.h"

typedef struct test_result_tag {
	unsigned passed;
	unsigned failed;
}test_results_t;

extern test_results_t test_results;

#define TEST(_expect, _test, _action) \
	({ \
		const typeof(_action) __expect = (typeof(_action))_expect; \
		const typeof(_action) __result = (typeof(_action))_action; \
		\
		const unsigned passed = (__expect _test __result), failed = !passed; \
		test_results.passed += !!passed; \
		test_results.failed += !!failed; \
		\
		LOG_START("[ %s ] -- ", failed ? " FAIL " : " PASS " ); \
		LOG_END("0x%016" PRIx64 " " #_test " (0x%016" PRIx64 " <-- " #_action ")", \
			(int64_t)__expect, (int64_t)__result); \
	})
