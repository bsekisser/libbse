typedef union generic_data_tag* generic_data_ptr;
typedef generic_data_ptr const generic_data_ref;

typedef union generic_data_tag {
	char c;
	double d;
	float f;
	int i;
	int16_t i16;
	int32_t i32;
	int8_t i8;
	long l;
	void *p;
	int16_t* p2i16;
	uint16_t* p2u16;
	int32_t* p2i32;
	uint32_t* p2u32;
	int8_t* p2i8;
	uint8_t* p2u8;
	short s;
	signed st;
	uint16_t u16;
	uint32_t u32;
	uint8_t u8;
	unsigned char uc;
	unsigned long ul;
	unsigned short us;
	unsigned ut;
}generic_data_t;
