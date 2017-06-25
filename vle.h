#ifndef LIB_PPCVLE
#define LIB_PPCVLE
#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

void decode(const u8* buffer, u32 size);


#endif