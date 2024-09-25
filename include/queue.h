#pragma once

/* **** */

#include <stdlib.h>

/* **** */

enum {
	QSORT_CONTINUE,
	QSORT_INSERT,
//
	QSORT_DROP = -1,
	QSORT_RESTART = -2,
};

typedef struct qelem_t** qelem_h;
typedef struct qelem_t* qelem_p;
typedef struct qelem_t {
	qelem_p		next;
	union {
		void*		data;
		void		(*fn)(void*, ...);
	};
}qelem_t;

typedef struct queue_t* queue_p;
typedef struct queue_t {
	qelem_p		head;
	qelem_p		tail;
}queue_t;

typedef int (*queue_sort_fn)(qelem_p lhs, qelem_p insert, qelem_p rhs);

/* **** */

size_t queue_count(queue_p q);
int queue_dequeue(qelem_p const e, qelem_p const p2lhs, queue_p const q);
qelem_p queue_dequeue_next(queue_p q);
void queue_enqueue(qelem_p e, queue_p q);
void queue_exit(queue_p q);
queue_p queue_init(queue_p q);
void queue_insert(qelem_p lhs, qelem_p e, qelem_p rhs, queue_p q);
void queue_insert_sorted(qelem_p e, queue_p q, queue_sort_fn fn);
qelem_p queue_next(qelem_h lhs, qelem_h rhs, queue_p q);
