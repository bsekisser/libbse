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

/* **** */

typedef struct qelem_t** qelem_h;
typedef struct qelem_t* qelem_p;
typedef qelem_p const qelem_ref;
typedef qelem_h const qelem_href;

typedef struct queue_t* queue_p;
typedef queue_p const queue_ref;

typedef struct queue_iterator_t* queue_iterator_p;
typedef queue_iterator_p const queue_iterator_ref;

typedef struct queue_iterator_search_t* queue_iterator_search_p;
typedef queue_iterator_search_p const queue_iterator_search_ref;

typedef int (*queue_iterator_search_fn)(queue_iterator_search_ref qis, void *const param, void *const qdata);
typedef int (*queue_sort_fn)(qelem_p lhs, qelem_p insert, qelem_p rhs);

/* **** */

typedef struct queue_iterator_t {
	qelem_p lhs, cqe;
	queue_p q;
}queue_iterator_t;

typedef struct queue_iterator_search_t {
	queue_iterator_t qi;
	queue_iterator_search_fn fn;
}queue_iterator_search_t;

typedef struct qelem_t {
	qelem_p		next;
	union {
		void*		data;
		void		(*fn)(void*, ...);
	};
}qelem_t;

typedef struct queue_t {
	qelem_p		head;
	qelem_p		tail;
}queue_t;

/* **** */

size_t queue_count(queue_ref q);
int queue_dequeue(qelem_ref e, qelem_ref p2lhs, queue_ref q);
qelem_p queue_dequeue_next(queue_ref q);
void queue_enqueue(qelem_ref e, queue_ref q);
void queue_exit(queue_ref q);
queue_p queue_init(queue_p q);
void queue_insert(qelem_ref lhs, qelem_ref e, qelem_ref rhs, queue_ref q);
void queue_insert_sorted(qelem_ref e, queue_ref q, queue_sort_fn fn);
void queue_iterator_init(queue_iterator_ref qi, queue_ref q);
qelem_p queue_iterator_next(queue_iterator_ref qi);
void queue_iterator_reset(queue_iterator_ref qi);
int queue_iterator_search(queue_iterator_search_ref qis, void *const param);
void queue_iterator_search_init(queue_iterator_search_ref qis, queue_ref q, queue_iterator_search_fn fn);
int queue_iterator_search_next(queue_iterator_search_ref qis, void *const param);
int queue_iterator_search_step(queue_iterator_search_ref qis, void *const param);
qelem_p queue_next(qelem_href lhs, qelem_href rhs, queue_ref q);
qelem_p queue_pop_back(queue_ref q, qelem_ref p2lhs);
qelem_p queue_pop_front(queue_ref q);
void queue_push_back(qelem_ref e, queue_ref q);
void queue_push_front(qelem_ref e, queue_ref q);
