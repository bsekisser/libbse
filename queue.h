#pragma once

typedef struct qelem_t* qelem_p;
typedef struct qelem_t {
	qelem_p		next;
	union {
		void*		data;
		void		(*fn)(void*);
	};
}qelem_t;

typedef struct queue_t* queue_p;
typedef struct queue_t {
	qelem_p		head;
	qelem_p		tail;
}queue_t;

static inline void enqueue(queue_p q, qelem_p e)
{
	if(q->tail)
		q->tail->next = e;

	q->tail = e;

	if(!q->head)
		q->head = e;
}

static inline int queue_count(queue_p q)
{
	int count = 0;

	for(qelem_p e = q->head; e; count++)
		e = e->next;

	return(count);
}

static inline void queue_exit(queue_p q)
{
	for(qelem_p e = q->head; e; e = e->next)
		free(e);

	free(q);
}

static inline queue_p queue_init(void)
{
	queue_p q = (queue_p)malloc(sizeof(queue_t));

	q->head = 0;
	q->tail = 0;

	return(q);
}
