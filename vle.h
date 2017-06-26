#ifndef LIB_PPCVLE
#define LIB_PPCVLE
#include <stdint.h>


#define TYPE_NONE 0
#define TYPE_REG  1
#define TYPE_IMM  2
#define TYPE_MEM  3
#define TYPE_JMP  4
#define TYPE_CR   5

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef struct {
	const u8* end;
	const u8* pos;
	u16 inc;
} vle_handle;

typedef struct {
	u32 value;
	u16 type;
} vle_field_t;

typedef struct {
	const char* name;
	vle_field_t fields[10];
	u16 n;
	u16 size;
} vle_t;

int vle_init(vle_handle* handle, const u8* buffer, const u32 size);
vle_t* vle_next(vle_handle* handle);
void vle_free(vle_t* instr);
void vle_print(vle_t* instr);


#endif