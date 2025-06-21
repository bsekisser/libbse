#pragma once

/* **** */

#include <unistd.h>

#include "bitops.h"

/* **** */

typedef volatile char spin_t;
typedef spin_t* spin_ptr;
typedef spin_ptr const spin_ref;

enum {
//	_spin_lock,
	_spin_granted,
	_spin_request,
};

static inline
void _clear(spin_ref lock, const char bit) {
	BCLR(*lock,  bit);
}

static inline
int _check(spin_ref lock, const char bit) {
	return(BTST(*lock, bit));
}

static inline
void _set(spin_ref lock, const char bit) {
	BSET(*lock, bit);
}

static inline
void _spin_set(spin_ref lock, const char bit) {
	while(!_check(lock, bit))
		_set(lock, bit);
}

static inline
void _spin_wait_till_set(spin_ref lock, const char bit, const int sleep) {
	while(!_check(lock, bit)) {
		if(sleep)
			usleep(10);
	}
}

static inline
void _spin_wait_till_clear(spin_ref lock, const char bit, const int sleep) {
	while(_check(lock, bit)) {
		if(sleep)
			usleep(10);
	}
}

/* **** */

static inline
void spin_clear(spin_ref lock) {
	*lock = 0;
}

static inline
void spin_lock(spin_ref lock) {
//	printf("%s: lock = 0x%08x\n", __FUNCTION__, *lock);

	while(*lock)
		;
}

static inline
void spin_lock_set(spin_ref lock, spin_ref set) {
//	printf("%s: lock = 0x%08x, set = 0x%08x\n", __FUNCTION__, *lock, *set);

	*set |= 1;

	spin_lock(lock);
}

static inline
void spin_set_wait(spin_ref set, spin_ref wait, const char till) {
	*set |= 1;

	while(till != *wait)
		;
}

static inline
void spin_unlock(spin_ref lock) {
//	printf("%s: lock = 0x%08x\n", __FUNCTION__, *lock);

	*lock = 0;
}

static inline
void spin_lock_unlock(spin_ref lock, spin_ref unlock) {
//	printf("%s: lock = 0x%08x, unlock = 0x%08x\n", __FUNCTION__, *lock, *unlock);

	spin_lock(lock);
	spin_unlock(unlock);
}

#if 0
	#define spin_lock(_x) \
		do { \
			printf("%s:", __FUNCTION__); \
			_spin_lock(_x); \
		}while(0);
	#define spin_lock_set(_x, _y) \
		do { \
			printf("%s:", __FUNCTION__); \
			_spin_lock_set(_x, _y); \
		}while(0);
	#define spin_unlock(_x) \
		do { \
			printf("%s:", __FUNCTION__); \
			_spin_unlock(_x); \
		}while(0);
#endif

/* **** */

static inline
void spin_clear_request(spin_ref lock) {
	_clear(lock, _spin_request);
}

static inline
void _sleep_spin_lock_request(spin_ref lock, const int sleep) {
	_spin_set(lock, _spin_request);
	_spin_wait_till_set(lock, _spin_granted, sleep);
}

static inline
void sleep_lock_request(spin_ref lock) {
	_sleep_spin_lock_request(lock, 1);
}

static inline
void spin_lock_request(spin_ref lock) {
	_sleep_spin_lock_request(lock, 0);
}

static inline
int spin_lock_requested(spin_ref lock) {
	return(_check(lock, _spin_request));
}

static inline
void _sleep_spin_lock_granted(spin_ref lock, const int sleep) {
	_spin_set(lock, _spin_granted);
//	_spin_wait_till_clear(lock, _spin_request, 1);
	_spin_wait_till_clear(lock, _spin_request, sleep);
}

static inline
void sleep_lock_granted(spin_ref lock) {
	_sleep_spin_lock_granted(lock, 1);
}

static inline
void spin_lock_granted(spin_ref lock) {
	_sleep_spin_lock_granted(lock, 0);
}

static inline
void _sleep_spin_yeild_request(spin_ref lock, const int sleep) {
	if(_check(lock, _spin_request))
	{
		_sleep_spin_lock_granted(lock, sleep);
		_clear(lock, _spin_granted);
	}
}

static inline
void spin_yeild_request(spin_ref lock) {
	_sleep_spin_yeild_request(lock, 0);
}

static inline
void sleep_yeild_request(spin_ref lock) {
	_sleep_spin_yeild_request(lock, 1);
}
