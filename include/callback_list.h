#pragma once

typedef int (*callback_fn)(void* param);

enum {
	LIST_NULL,
	LIST_FIFO,
	LIST_LIFO,
};

#define __CALLBACK_LIST_COUNT 8

typedef struct callback_list_elem_tag* callback_list_elem_ptr;
typedef callback_list_elem_ptr const callback_list_elem_ref;

typedef struct callback_list_elem_tag {
	callback_fn fn;
	void* param;
}callback_list_elem_t;

typedef struct callback_list_tag** callback_list_hptr;
typedef callback_list_hptr const callback_list_href;

typedef struct callback_list_tag* callback_list_ptr;
typedef callback_list_ptr const callback_list_ref;

typedef struct callback_list_tag {
	unsigned int type;
	unsigned int count;
	unsigned int limit;
	callback_list_elem_t cble[__CALLBACK_LIST_COUNT];
}callback_list_t;

void callback_list_alloc_init(callback_list_href cbl, const unsigned int additional, const unsigned int type);
void callback_list_init(callback_list_ref cbl, const unsigned int additional, const unsigned int type);
void callback_list_process(callback_list_ref cbl);
void callback_list_register_callback(callback_list_ref cbl, callback_fn fn, void *const param);

#define DEFN_CALLBACK_REGISTER_FN(_name, _type, _what, _llist) \
	void _name ## _callback_ ## _llist(_type _what, callback_fn fn, void* param)

#define DECL_CALLBACK_REGISTER_FN(_name, _type, _what, _llist) \
	DEFN_CALLBACK_REGISTER_FN(_name, _type, _what, _llist) { \
		callback_list_register_callback(&_what->_llist ## _list, fn, param); \
	}

#define DECL_CALLBACK_P_REGISTER_FN(_name, _type, _what, _llist) \
	DEFN_CALLBACK_REGISTER_FN(_name, _type, _what, _llist) { \
		callback_list_register_callback(_what->_llist ## _list, fn, param); \
	}
