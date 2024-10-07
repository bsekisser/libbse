#include "queue.h"

/* **** */

#include "log.h"

/* **** */

#include <assert.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

/* **** */

size_t queue_count(queue_ref q)
{
	assert(q);

	size_t count = 0;

	for(qelem_p e = q->head; e; count++)
		e = e->next;

	return(count);
}


int queue_dequeue(qelem_ref e, qelem_ref p2lhs, queue_ref q)
{
	const qelem_ref next = e ? e->next : 0;
	e->next = 0;

	if(!next) assert(e == q->tail);

	if(0) {
		LOG_START("lhs: 0x%016" PRIxPTR, (uintptr_t)p2lhs);
		_LOG_(", e: 0x%016" PRIxPTR, (uintptr_t)e);
		_LOG_("->next: 0x%016" PRIxPTR, (uintptr_t)next);
		LOG_END(", q: 0x%016" PRIxPTR, (uintptr_t)q);
	}

	assert(e);

	if(p2lhs)
		p2lhs->next = next;
	else {
		if(e == q->head) {
			q->head = next;
		} else {
			qelem_p lhs = 0, rhs = 0, t = 0;

			do {
				t = queue_next(&lhs, &rhs, q);
				if(e == t) {
					return(queue_dequeue(e, lhs, q));
				}
			}while(t);

			return(0);
		}
	}

	if(e == q->tail)
		q->tail = next;

	return(1);
}

qelem_p queue_dequeue_next(queue_ref q)
{
	assert(q);

	const qelem_ref e = q->head;
	const qelem_ref next = e ? e->next : 0;

	q->head = next;

	if(e == q->tail)
		q->tail = next;

	return(e);
}

void queue_enqueue(qelem_ref e, queue_ref q)
{
	assert(e);
	assert(q);

	if(q->tail)
		q->tail->next = e;

	q->tail = e;
	e->next = 0;

	if(!q->head)
		q->head = e;
}

void queue_exit(queue_ref q)
{
	assert(q);

	for(qelem_p e = q->head; e; e = e->next)
		free(e);

	free(q);
}

queue_p queue_init(queue_p q)
{
	if(!q)
		q = (queue_p)malloc(sizeof(queue_t));

	assert(q);

	q->head = 0;
	q->tail = 0;

	return(q);
}

void queue_insert(qelem_ref lhs, qelem_ref e, qelem_ref rhs, queue_ref q)
{
	assert(e);
	assert(q);

	e->next = rhs;

	if(lhs)
		lhs->next = e;

	if(!q->head || !lhs)
		q->head = e;

	if(!q->tail || !rhs)
		q->tail = e;
}

void queue_insert_sorted(qelem_ref e, queue_ref q, queue_sort_fn const fn)
{
	assert(e && q && fn);
	int restarts = 4;

restart_sort:;
	qelem_p lhs = 0, rhs = 0;
	while(queue_next(&lhs, &rhs, q)) {
		switch(fn(lhs, e, rhs)) {
		case QSORT_DROP:
			return;
		case QSORT_INSERT:
			goto do_queue_insert;
		case QSORT_RESTART:
			if(restarts--)
				goto restart_sort;
			else
				abort();
		}
	}

do_queue_insert:
	queue_insert(lhs, e, rhs, q);
}

void queue_iterator_init(queue_iterator_ref qi, queue_ref q)
{
	assert(qi && q);

	(void)memset(qi, 0, sizeof(queue_iterator_t));

	qi->q = q;

	return(queue_iterator_reset(qi));
}

qelem_p queue_iterator_next(queue_iterator_ref qi)
{ return(queue_next(&qi->lhs, &qi->cqe, qi->q)); }

void queue_iterator_reset(queue_iterator_ref qi)
{
	assert(qi);

	qi->cqe = 0;
	qi->lhs = 0;
}

int queue_iterator_search(queue_iterator_search_ref qis, void *const param)
{
	queue_iterator_reset(&qis->qi);
	return(queue_iterator_search_next(qis, param));
}

void queue_iterator_search_init(queue_iterator_search_ref qis, queue_ref q, queue_iterator_search_fn fn)
{
	(void)memset(qis, 0, sizeof(queue_iterator_search_t));
	queue_iterator_init(&qis->qi, q);
	qis->fn = fn;
}

int queue_iterator_search_next(queue_iterator_search_ref qis, void *const param)
{
	int rval = 0;

	do {
		rval = queue_iterator_search_step(qis, param);
	}while(0 == rval);

	return(rval);
}

int queue_iterator_search_step(queue_iterator_search_ref qis, void *const param)
{
	const qelem_ref cqe = queue_iterator_next(&qis->qi);
	void *const qdata = cqe ? cqe->data : 0;

	if(cqe) {
		if(qis->fn)
			return(qis->fn(qis, param, qdata));
		else
			return(param == qdata);
	}

	return(-1);
}

qelem_p queue_next(qelem_href h2lhs, qelem_href h2rhs, queue_ref q)
{
	assert(q);

	const qelem_ref lhs = h2lhs ? *h2lhs : 0;
	const qelem_ref rhs = h2rhs ? *h2rhs : 0;
	const qelem_ref next = rhs ? rhs->next : (lhs ? 0 : q->head);

	if(h2lhs)
		*h2lhs = rhs;

	if(h2rhs)
		*h2rhs = next;

	return(next);
}
