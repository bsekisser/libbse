#include "callback_list.h"

/* **** */

#include <stddef.h>
#include <string.h>

/* **** */

void callback_list_init(callback_list_p cbl, int additional)
{
	size_t size = sizeof(callback_list_t);
	
	if(additional)
		size += sizeof(callback_list_elem_t);

	memset(cbl, 0, size);

	cbl->limit = 16 + additional;
}

void callback_list_process(callback_list_p cbl)
{
	for(int i = 0; i < cbl->limit; i++) {
		callback_list_elem_p cble = &cbl->cble[i];
		
		if(cble->fn)
			cble->fn(cble->param);
	};
}

void callback_list_register_callback(callback_list_p cbl, callback_fn fn, void* param)
{
	for(int i = 0; i < cbl->limit; i++) {
		callback_list_elem_p cble = &cbl->cble[i];

		if(0 == cble->fn) {
			cble->fn = fn;
			cble->param = param;
			return;
		}
	}
}
