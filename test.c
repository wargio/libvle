/*
EXAMPLE 1
00 80                             se_mflr   r0
18 21 06 F0                       e_stwu    r1, -0x10(r1)
D5 01                             se_stw    r0, 0x14(r1)
79 FF AF 09                       e_bl      loc_21240
C5 01                             se_lwz    r0, 0x14(r1)
00 D3                             se_extsb  r3
00 90                             se_mtlr   r0
20 F1                             se_addi   r1, 0x10
00 04                             se_blr

EXAMPLE 2
2D 07                             se_bmaski r7, 0x10
70 D8 E3 FE                       e_lis     r6, -0x3C02
70 0B 02 F0                       e_li      r0, 0x5AF0
6D C3                             se_slwi   r3, 0x1C
44 30                             se_or     r0, r3
1C C6 C0 00                       e_add16i  r6, r6, -0x4000
D1 06                             se_stw    r0, 4(r6)
7C E0 02 78                       xor       r0, r7, r0
D1 06                             se_stw    r0, 4(r6)
C0 06                             se_lwz    r0, 0(r6)
66 40                             se_btsti  r0, 4
E2 FE                             se_bne    0xFFFFC8D0
00 04                             se_blr
*/

#include "vle.h"
#include <stdio.h>

const uint8_t example_1 [] = {0x00, 0x80, 0x18, 0x21, 0x06, 0xF0, 0xD5, 0x01, 0x79, 0xFF, 0xAF, 0x09, 0xC5, 0x01, 0x00, 0xD3, 0x00, 0x90, 0x20, 0xF1, 0x00, 0x04};
const uint8_t example_2 [] = {0x2D, 0x07, 0x70, 0xD8, 0xE3, 0xFE, 0x70, 0x0B, 0x02, 0xF0, 0x6D, 0xC3, 0x44, 0x30, 0x1C, 0xC6, 0xC0, 0x00, 0xD1, 0x06, 0x7C, 0xE0, 0x02, 0x78, 0xD1, 0x06, 0xC0, 0x06, 0x66, 0x40, 0xE2, 0xFE, 0x00, 0x04};

int main(int argc, char const *argv[]) {
	printf("example 1\n");
	decode(example_1, sizeof(example_1));
	printf("\n\nexample 2\n");
	decode(example_2, sizeof(example_2));
	return 0;
}