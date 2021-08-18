typedef volatile char spin_t;
typedef spin_t* spin_p;

enum {
//	_spin_lock,
	_spin_granted,
	_spin_request,
};

static inline void _clear(spin_p lock, char bit) {
	*lock &= ~(1 << bit);
}

static inline int _check(spin_p lock, char bit) {
	return(*lock & (1 << bit));
}

static inline void _set(spin_p lock, char bit) {
	*lock |= (1 << bit);
}

static inline void _spin_set(spin_p lock, char bit) {
	while(!_check(lock, bit))
		_set(lock, bit);
}

static inline void _spin_wait_till_set(spin_p lock, char bit) {
	while(!_check(lock, bit))
		;
}

static inline void _spin_wait_till_clear(spin_p lock, char bit) {
	while(_check(lock, bit))
		;
}

/* **** */

static inline void spin_clear(spin_p lock) {
	*lock = 0;
}

static inline void spin_lock(spin_p lock) {
//	printf("%s: lock = 0x%08x\n", __FUNCTION__, *lock);
	
	while(*lock)
		;
}

static inline void spin_lock_set(spin_p lock, spin_p set) {
//	printf("%s: lock = 0x%08x, set = 0x%08x\n", __FUNCTION__, *lock, *set);

	*set |= 1;

	spin_lock(lock);
}

static inline void spin_set_wait(spin_p set, spin_p wait, char till) {
	*set |= 1;
	
	while(till != *wait)
		;
}

static inline void spin_unlock(spin_p lock) {
//	printf("%s: lock = 0x%08x\n", __FUNCTION__, *lock);

	*lock = 0;
}

static inline void spin_lock_unlock(spin_p lock, spin_p unlock) {
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

static inline void spin_clear_request(spin_p lock) {
	_clear(lock, _spin_request);
}

static inline void spin_lock_request(spin_p lock) {
	_spin_set(lock, _spin_request);
	_spin_wait_till_set(lock, _spin_granted);
}

static inline int spin_lock_requested(spin_p lock) {
	return(_check(lock, _spin_request));
}

static inline void spin_lock_granted(spin_p lock) {
	_spin_set(lock, _spin_granted);
	_spin_wait_till_clear(lock, _spin_request);
}

static inline void spin_yeild_request(spin_p lock) {
	if(_check(lock, _spin_request))
	{
		spin_lock_granted(lock);
		_clear(lock, _spin_granted);
	}
}
