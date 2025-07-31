typedef union generic128_data_tag* generic128_data_ptr;
typedef generic128_data_ptr const generic128_data_ref;

typedef union generic128_data_tag {
	char c;
	double d;
	float f;
	int i;
#if defined(__SIZEOF_INT128__) //|| defined(__aarch64__)
	__int128_t i128;
#endif
	int16_t i16;
	int32_t i32;
	int64_t i64;
	int8_t i8;
	long l;
	long long ll;
	void *p;
	int16_t* p2i16;
	uint16_t* p2u16;
	int32_t* p2i32;
	uint32_t* p2u32;
	int8_t* p2i8;
	uint8_t* p2u8;
	short s;
	signed st;
#if defined(__SIZEOF_INT128__) //|| defined(__aarch64__)
	__uint128_t u128;
#endif
	uint16_t u16;
	uint32_t u32;
	int64_t u64;
	uint8_t u8;
	unsigned char uc;
	unsigned long ul;
	unsigned long long ull;
	unsigned short us;
	unsigned ut;
}generic128_data_t;
