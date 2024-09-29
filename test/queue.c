#include "../include/queue.h"
#include "../source/queue.c"

/* **** */

#include "../include/log.h"

/* **** */

#include <assert.h>
#include <inttypes.h>

/* **** */

#define kElem_count 3

queue_t qht;
qelem_t qet[kElem_count];

int main(void) {
	queue_init(&qht);

	for(unsigned x = 0; x < kElem_count; x++) {
		LOG_START("qe: 0x%016" PRIxPTR, (uintptr_t)&qet[x]);

		queue_enqueue(&qet[x], &qht);

		_LOG_(", qHead: 0x%016" PRIxPTR, (uintptr_t)qht.head);
		LOG_END(", qTail: 0x%016" PRIxPTR, (uintptr_t)qht.tail);
	}

	unsigned x = 0;
	qelem_p lhs = 0, cqe = 0, rhs = 0, next_lhs = 0, next_rhs = 0;

	while((cqe = queue_next(&lhs, &rhs, &qht))) {
		LOG_START("lhs: 0x%016" PRIxPTR, (uintptr_t)lhs);
		_LOG_(", cqe: 0x%016" PRIxPTR, (uintptr_t)cqe);
		LOG_END(", rhs: 0x%016" PRIxPTR, (uintptr_t)rhs);

		if(0 == x) assert(cqe == qht.head);
		assert(cqe == &qet[x++]);

		assert(lhs == next_lhs);

		if(next_rhs) assert(cqe == next_rhs);

		next_lhs = cqe;
		next_rhs = cqe ? cqe->next : 0;

		if(0 == next_rhs) assert(cqe == qht.tail);
	}
}
