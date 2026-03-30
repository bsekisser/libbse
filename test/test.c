#include "log.h"
#include "test.h"

const char* pass_failed[2] = { " PASS ", "FAILED" };
test_results_t test_results;

int main(void)
{
	LOG("tests.(failed: 0x%08x, passed: 0x%08x)",
		test_results.failed, test_results.passed);
}
