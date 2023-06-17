#pragma once

#ifndef callback_fn
	typedef int (*callback_fn)(void* param);
#endif

enum {
	LIST_NULL,
	LIST_FIFO,
	LIST_LIFO,
};

typedef struct callback_qlist_elem_t* callback_qlist_elem_p;
typedef struct callback_qlist_elem_t {
	callback_qlist_elem_p next;
	callback_qlist_elem_p prev;
	callback_fn fn;
	void* param;
}callback_qlist_elem_t;

typedef struct callback_qlist_t** callback_qlist_h;
typedef struct callback_qlist_t* callback_qlist_p;
typedef struct callback_qlist_t {
	callback_qlist_elem_p head;
	callback_qlist_elem_p tail;
	unsigned int type;
	unsigned int count;
}callback_qlist_t;

/* **** */

void callback_qlist_alloc_init(callback_qlist_h cbl, unsigned int type);
void callback_qlist_init(callback_qlist_p cbl, unsigned int type);
void callback_qlist_process(callback_qlist_p cbl);
void callback_qlist_register_callback(callback_qlist_p cbl,
	callback_qlist_elem_p cble);

/* **** */

static inline void callback_qlist_setup_elem(callback_qlist_elem_p cble, callback_fn fn, void* param)
{
	cble->fn = fn;
	cble->next = 0;
	cble->param = param;
	cble->prev = 0;
}

static inline void callback_qlist_setup_and_register_callback(callback_qlist_p cbl,
	callback_qlist_elem_p cble, callback_fn fn, void* param)
{
	callback_qlist_setup_elem(cble, fn, param);
	callback_qlist_register_callback(cbl, cble);
}
