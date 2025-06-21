#pragma once

#ifdef _cplusspluss
extern "C" {
#endif

/* **** */

#include "err_test.h"
#include "log.h"

/* **** */

#ifndef callback_fn
	typedef int (*callback_fn)(void* param);
#endif

enum {
	LIST_NULL,
	LIST_FIFO,
	LIST_LIFO,
//
	_LIST_TYPE_COUNT,
};

typedef struct callback_qlist_elem_tag* callback_qlist_elem_ptr;
typedef callback_qlist_elem_ptr const callback_qlist_elem_ref;

typedef struct callback_qlist_elem_tag {
	callback_qlist_elem_ptr next;
	callback_qlist_elem_ptr prev;

	unsigned flags;
	callback_fn fn;
	void* param;
}callback_qlist_elem_tag;

typedef struct callback_qlist_tag** callback_qlist_hptr;
typedef callback_qlist_hptr const callback_qlist_href;

typedef struct callback_qlist_tag* callback_qlist_ptr;
typedef callback_qlist_ptr const callback_qlist_ref;

typedef struct callback_qlist_tag {
	callback_qlist_elem_ptr head;
	callback_qlist_elem_ptr tail;

	unsigned int count;
	unsigned int type;
}callback_qlist_t;

/* **** */

void callback_qlist_alloc_init(callback_qlist_href cbl, unsigned int type);
void callback_qlist_init(callback_qlist_ref cbl, unsigned int type);
void callback_qlist_process(callback_qlist_ref cbl);
void callback_qlist_process_singleton_list(callback_qlist_ref cbl);
void callback_qlist_register_callback(callback_qlist_ref cbl,
	callback_qlist_elem_ptr const cble);

/* **** */

static inline void callback_qlist_setup_elem(callback_qlist_elem_ref cble,
	callback_fn const fn, void *const param)
{
	ERR_NULL(cble);
//	ERR_IF(cble->next);
//	ERR_IF(cble->prev);

	cble->fn = fn;
	cble->next = 0;
	cble->param = param;
	cble->prev = 0;
}

static inline void callback_qlist_setup_and_register_callback(callback_qlist_ref cbl,
	callback_qlist_elem_ref cble, callback_fn const fn, void *const param)
{
	ERR_NULL(cbl);
	ERR_NULL(cble);

	callback_qlist_setup_elem(cble, fn, param);
	callback_qlist_register_callback(cbl, cble);
}

#ifdef _cplusspluss
}
#endif
