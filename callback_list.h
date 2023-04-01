#pragma once

typedef int (*callback_fn)(void* param);

enum {
	LIST_NULL,
	LIST_FIFO,
	LIST_LIFO,
};

#define __CALLBACK_LIST_COUNT 8

typedef struct callback_list_elem_t* callback_list_elem_p;
typedef struct callback_list_elem_t {
	callback_fn fn;
	void* param;
}callback_list_elem_t;

typedef struct callback_list_t** callback_list_h;
typedef struct callback_list_t* callback_list_p;
typedef struct callback_list_t {
	unsigned int type;
	unsigned int count;
	unsigned int limit;
	callback_list_elem_t cble[__CALLBACK_LIST_COUNT];
}callback_list_t;

void callback_list_alloc_init(callback_list_h cbl, unsigned int additional, unsigned int type);
void callback_list_init(callback_list_p cbl, unsigned int additional, unsigned int type);
void callback_list_process(callback_list_p cbl);
void callback_list_register_callback(callback_list_p cbl, callback_fn fn, void* param);

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
