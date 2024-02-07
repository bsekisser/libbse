#include "queue.h"

/* **** */

#include <assert.h>
#include <stdlib.h>

/* **** */

void enqueue(qelem_p e, queue_p q)
{
	assert(e);
	assert(q);

	if(q->tail)
		q->tail->next = e;

	q->tail = e;

	if(!q->head)
		q->head = e;
}

size_t queue_count(queue_p q)
{
	assert(q);

	size_t count = 0;

	for(qelem_p e = q->head; e; count++)
		e = e->next;

	return(count);
}

void queue_exit(queue_p q)
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

void queue_insert(qelem_p lhs, qelem_p e, qelem_p rhs, queue_p q)
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

void queue_insert_sorted(qelem_p e, queue_p q, queue_sort_fn fn)
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

qelem_p queue_next(qelem_h h2lhs, qelem_h h2rhs, queue_p q)
{
	assert(q);

	qelem_p lhs = h2lhs ? *h2lhs : 0;
	qelem_p rhs = h2rhs ? *h2rhs : 0;
	qelem_p next = rhs ? rhs->next : (lhs ? 0 : q->head);

	if(h2lhs)
		*h2lhs = rhs;

	if(h2rhs)
		*h2rhs = next;

	return(next);
}
