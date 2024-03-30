#pragma once

//extern int _on_err_;
static int _on_err_ = 0;

#define _ON_ERR(_fail, _test) \
	{ \
		if((_on_err_ = (_test))) { \
			goto on_err_##_fail; \
		} \
	}

#define ON_ERR(_fail, _test) _ON_ERR(_fail, -1 == (_test))
#define ON_0ERR(_fail, _test) _ON_ERR(_fail, 0 == (_test))
