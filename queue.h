#pragma once

typedef struct qelem_t* qelem_p;
typedef struct qelem_t {
	qelem_p		next;
	union {
		void*		data;
		void		(*fn)(void*);
	};
}qelem_t;

typedef struct queue_t {
	qelem_p		head;
	qelem_p		tail;
}queue_t;

#define ENQUEUE(_q, _e) \
	do { \
		if(_q->tail) \
			_q->tail->next = _e; \
		_q->tail = _e; \
		if(!_q->head) \
			_q->head = _e; \
	}while(0);
