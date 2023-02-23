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
		callback_list_elem_p cbe = &cbl->cbe[i];
		
		if(cbe->fn)
			cbe->fn(cbe->param);
	};
}

void callback_list_register_callback(callback_list_p cbl, callback_fn fn, void* param)
{
	for(int i = 0; i < cbl->limit; i++) {
		callback_list_elem_p cbe = cbl->cbe[i];

		if(0 == cbe->fn) {
			cbe->fn = fn;
			cbe->param = param;
			return;
		}
	}
}
