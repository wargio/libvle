#ifndef LIB_PPCVLE_INTERNAL
#define LIB_PPCVLE_INTERNAL


typedef struct {
	u16 mask;
	u16 shr;
	u16 shl;
	u16 add;
	u8 idx;
	u8 type;
} field_t;

typedef struct {
	u16 mask;
	u16 shr;
	u16 shl;
	u16 add;
	u8 idx;
	u8 type;
} field32_t;

typedef struct {
	const char* name;
	u32 op;
	u32 mask;
	u16 n;
	field32_t fields[5];
} e_vle_t;

typedef struct {
	const char* name;
	u16 op;
	u16 mask;
	u16 n;
	field_t fields[5];
} se_vle_t;

typedef struct {
	u16 value;
	u16 type;
} vle_field_t;

typedef struct {
	const char* name;
	vle_field_t fields[10];
	u16 n;
} vle_t;

#endif