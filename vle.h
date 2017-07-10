/* LGPL - Copyright 2017 - wargio */
#ifndef LIB_PPCVLE
#define LIB_PPCVLE
#include <stdint.h>

typedef uint8_t ut8;
typedef uint16_t ut16;
typedef uint32_t ut32;
typedef uint64_t ut64;

#define TYPE_NONE 0
#define TYPE_REG  1
#define TYPE_IMM  2
#define TYPE_MEM  3
#define TYPE_JMP  4
#define TYPE_CR   5

typedef struct {
	const ut8* end;
	const ut8* pos;
	ut16 inc;
} vle_handle;

typedef struct {
	ut32 value;
	ut16 type;
} vle_field_t;

typedef struct {
	const char* name;
	vle_field_t fields[10];
	ut16 n;
	ut16 size;
} vle_t;

int vle_init(vle_handle* handle, const ut8* buffer, const ut32 size);
vle_t* vle_next(vle_handle* handle);
void vle_free(vle_t* instr);
void vle_snprint(char* str, int size, ut64 addr, vle_t* instr);

#endif