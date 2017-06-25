#include "vle.h"
#include "vle_internal.h"
#include <stdlib.h>
#include <stdio.h>

#define NONE 0
#define REG 1
#define IMM 2
#define MEM 3
#define CR  4
#define MSIZE(x) (8-(x))

const e_vle_t e_array[] = {
};
// page 96
// page 1264
const se_vle_t se_array[] = {
//	{ "name"      , op    , mask  , n, {{field ,shl,shr,  +, i, imm}, ...}
	{ "se_illegal", 0x0000, 0x0000, 0, {{0}, {0}, {0}, {0}, {0}}},
	{ "se_isync"  , 0x0001, 0x0001, 0, {{0}, {0}, {0}, {0}, {0}}},
	{ "se_sc"     , 0x0002, 0x0002, 0, {{0}, {0}, {0}, {0}, {0}}},
	{ "se_blr"    , 0x0004, 0x0004, 0, {{0}, {0}, {0}, {0}, {0}}},
	{ "se_blrl"   , 0x0005, 0x0005, 0, {{0}, {0}, {0}, {0}, {0}}},
	{ "se_bctr"   , 0x0006, 0x0006, 0, {{0}, {0}, {0}, {0}, {0}}},
	{ "se_bctrl"  , 0x0007, 0x0007, 0, {{0}, {0}, {0}, {0}, {0}}},
	{ "se_rfi"    , 0x0008, 0x0008, 0, {{0}, {0}, {0}, {0}, {0}}},
	{ "se_rfci"   , 0x0009, 0x0009, 0, {{0}, {0}, {0}, {0}, {0}}},
	{ "se_not"    , 0x0020, 0x002F, 1, {{0x000F,  0,  0,  0, 0, REG}, {0}, {0}, {0}, {0}}},
	{ "se_neg"    , 0x0030, 0x003F, 1, {{0x000F,  0,  0,  0, 0, REG}, {0}, {0}, {0}, {0}}},
	{ "se_mtlr"   , 0x0090, 0x009F, 1, {{0x000F,  0,  0,  0, 0, REG}, {0}, {0}, {0}, {0}}},
	{ "se_mflr"   , 0x0080, 0x008F, 1, {{0x000F,  0,  0,  0, 0, REG}, {0}, {0}, {0}, {0}}},
	{ "se_mfctr"  , 0x00A0, 0x00AF, 1, {{0x000F,  0,  0,  0, 0, REG}, {0}, {0}, {0}, {0}}},
	{ "se_mtctr"  , 0x00B0, 0x00BF, 1, {{0x000F,  0,  0,  0, 0, REG}, {0}, {0}, {0}, {0}}},
	{ "se_extzb"  , 0x00C0, 0x00CF, 1, {{0x000F,  0,  0,  0, 0, REG}, {0}, {0}, {0}, {0}}},
	{ "se_extsb"  , 0x00D0, 0x00DF, 1, {{0x000F,  0,  0,  0, 0, REG}, {0}, {0}, {0}, {0}}},
	{ "se_extzh"  , 0x00E0, 0x00EF, 1, {{0x000F,  0,  0,  0, 0, REG}, {0}, {0}, {0}, {0}}},
	{ "se_extsh"  , 0x00F0, 0x00FF, 1, {{0x000F,  0,  0,  0, 0, REG}, {0}, {0}, {0}, {0}}},
	{ "se_mr"     , 0x0100, 0x01FF, 2, {{0x00F0,  4,  0,  0, 1, REG}, {0x000F,  0,  0,  0,  0, REG}, {0}, {0}, {0}}},
	{ "se_tar"    , 0x0200, 0x02FF, 2, {{0x00F0,  4,  0,  0, 1, REG}, {0x000F,  0,  0,  0,  0, REG}, {0}, {0}, {0}}},
	{ "se_mfar"   , 0x0300, 0x03FF, 2, {{0x00F0,  4,  0,  0, 1, REG}, {0x000F,  0,  0,  0,  0, REG}, {0}, {0}, {0}}},
	{ "se_add"    , 0x0400, 0x04FF, 2, {{0x00F0,  4,  0,  0, 1, REG}, {0x000F,  0,  0,  0,  0, REG}, {0}, {0}, {0}}},
	{ "se_mullw"  , 0x0500, 0x05FF, 2, {{0x00F0,  4,  0,  0, 1, REG}, {0x000F,  0,  0,  0,  0, REG}, {0}, {0}, {0}}},
	{ "se_addi"   , 0x2000, 0x21FF, 2, {{0x01F0,  4,  0,  1, 1, IMM}, {0x000F,  0,  0,  0,  0, REG}, {0}, {0}, {0}}},
	{ "se_and"    , 0x4800, 0x4CFF, 2, {{0x00F0,  4,  0,  0, 1, REG}, {0x000F,  0,  0,  0,  0, REG}, {0}, {0}, {0}}},
	{ "se_and."   , 0x4C00, 0x4EFF, 2, {{0x00F0,  4,  0,  0, 1, REG}, {0x000F,  0,  0,  0,  0, REG}, {0}, {0}, {0}}},
	{ "se_andi"   , 0x2E00, 0x2EFF, 2, {{0x01F0,  4,  0,  0, 1, IMM}, {0x000F,  0,  0,  0,  0, REG}, {0}, {0}, {0}}},
	{ "se_andc"   , 0x4500, 0x45FF, 2, {{0x00F0,  4,  0,  0, 1, REG}, {0x000F,  0,  0,  0,  0, REG}, {0}, {0}, {0}}},
	{ "se_b"      , 0xE800, 0xE8FF, 1, {{0x00FF,  0,  1,  0, 0, IMM}, {0}, {0}, {0}, {0}}},
	{ "se_bl"     , 0xE900, 0xE9FF, 1, {{0x00FF,  0,  1,  0, 0, IMM}, {0}, {0}, {0}, {0}}},
	{ "se_blt"    , 0xE000, 0xE0FF, 1, {{0x00FF,  0,  1,  0, 0, IMM}, {0}, {0}, {0}, {0}}},
	{ "se_bgt"    , 0xE000, 0xE1FF, 1, {{0x00FF,  0,  1,  0, 0, IMM}, {0}, {0}, {0}, {0}}},
	{ "se_beq"    , 0xE000, 0xE2FF, 1, {{0x00FF,  0,  1,  0, 0, IMM}, {0}, {0}, {0}, {0}}},
	{ "se_bso"    , 0xE000, 0xE3FF, 1, {{0x00FF,  0,  1,  0, 0, IMM}, {0}, {0}, {0}, {0}}},
	{ "se_bc"     , 0xE000, 0xE3FF, 2, {{0x0300,  8,  0, 32, 0, IMM}, {0x00FF,  0,  1,  0,  1, IMM}, {0}, {0}, {0}}},
	{ "se_bltctr" , 0xE000, 0xE4FF, 1, {{0x00FF,  0,  1,  0, 0, IMM}, {0}, {0}, {0}, {0}}},
	{ "se_bgtctr" , 0xE000, 0xE5FF, 1, {{0x00FF,  0,  1,  0, 0, IMM}, {0}, {0}, {0}, {0}}},
	{ "se_beqctr" , 0xE000, 0xE6FF, 1, {{0x00FF,  0,  1,  0, 0, IMM}, {0}, {0}, {0}, {0}}},
	{ "se_bsoctr" , 0xE000, 0xE7FF, 1, {{0x00FF,  0,  1,  0, 0, IMM}, {0}, {0}, {0}, {0}}},
	{ "se_bcctr"  , 0xE000, 0xE7FF, 2, {{0x0300,  8,  0, 32, 0, IMM}, {0x00FF,  0,  1,  0,  1, IMM}, {0}, {0}, {0}}},
	{ "se_bclri"  , 0x6000, 0x61FF, 2, {{0x01F0,  4,  0,  0, 1, IMM}, {0x000F,  0,  0,  0,  0, REG}, {0}, {0}, {0}}},
	{ "se_bgeni"  , 0x6200, 0x62FF, 2, {{0x01F0,  4,  0,  0, 1, IMM}, {0x000F,  0,  0,  0,  0, REG}, {0}, {0}, {0}}},
	{ "se_bmaski" , 0x2C00, 0x2DFF, 2, {{0x01F0,  4,  0,  0, 1, IMM}, {0x000F,  0,  0,  0,  0, REG}, {0}, {0}, {0}}},
	{ "se_bseti"  , 0x6400, 0x65FF, 2, {{0x01F0,  4,  0,  0, 1, IMM}, {0x000F,  0,  0,  0,  0, REG}, {0}, {0}, {0}}},
	{ "se_btsti"  , 0x6600, 0x67FF, 2, {{0x01F0,  4,  0,  0, 1, IMM}, {0x000F,  0,  0,  0,  0, REG}, {0}, {0}, {0}}},
	{ "se_cmpi"   , 0x2A00, 0x2BFF, 2, {{0x01F0,  4,  0,  0, 1, IMM}, {0x000F,  0,  0,  0,  0, REG}, {0}, {0}, {0}}},
	{ "se_cmp"    , 0x0C00, 0x0CFF, 2, {{0x00F0,  4,  0,  0, 1, REG}, {0x000F,  0,  0,  0,  0, REG}, {0}, {0}, {0}}},
	{ "se_cmpl"   , 0x0D00, 0x0DFF, 2, {{0x00F0,  4,  0,  0, 1, REG}, {0x000F,  0,  0,  0,  0, REG}, {0}, {0}, {0}}},
	{ "se_cmph"   , 0x0E00, 0x0EFF, 2, {{0x00F0,  4,  0,  0, 1, REG}, {0x000F,  0,  0,  0,  0, REG}, {0}, {0}, {0}}},
	{ "se_cmphl"  , 0x0F00, 0x0FFF, 2, {{0x00F0,  4,  0,  0, 1, REG}, {0x000F,  0,  0,  0,  0, REG}, {0}, {0}, {0}}},
	{ "se_cmpli"  , 0x2200, 0x23FF, 2, {{0x01F0,  4,  0,  1, 1, IMM}, {0x000F,  0,  0,  0,  0, REG}, {0}, {0}, {0}}},
	{ "se_lbz"    , 0x8000, 0x8FFF, 3, {{0x0F00,  8,  0,  0, 1, MEM}, {0x00F0,  4,  0,  0,  0, REG}, {0x000F,  0,  0,  0,  2, REG}, {0}, {0}}},
	{ "se_lbh"    , 0xA000, 0xAFFF, 3, {{0x0F00,  8,  0,  0, 1, MEM}, {0x00F0,  4,  0,  0,  0, REG}, {0x000F,  0,  0,  0,  2, REG}, {0}, {0}}},
	{ "se_li"     , 0x4800, 0x4FFF, 2, {{0x07F0,  4,  0,  0, 1, IMM}, {0x000F,  0,  0,  0,  0, REG}, {0}, {0}, {0}}},
	{ "se_lwz"    , 0xC000, 0xCFFF, 3, {{0x0F00,  6,  0,  0, 1, MEM}, {0x00F0,  4,  0,  0,  0, REG}, {0x000F,  0,  0,  0,  2, REG}, {0}, {0}}},
	{ "se_or"     , 0x4400, 0x44FF, 2, {{0x00F0,  4,  0,  0, 1, REG}, {0x000F,  0,  0,  0,  0, REG}, {0}, {0}, {0}}},
};



static const vle_t *find_e (const u8* buffer) {
	return NULL;
} 

static vle_t *find_se (const u8* buffer) {
	u32 i, j, k;
	u16 data = (buffer[0] << 8) | buffer[1];
	const se_vle_t* p = NULL;
	const u32 size = sizeof(se_array) / sizeof(se_vle_t);
	for (i = 0; i < size; ++i) {
		p = &se_array[i];
		if ((p->op & data) == p->op && (p->mask & data) == data) {
			if(i == 8) {

			}
			vle_t* ret = (vle_t*) calloc(1, sizeof(vle_t));
			ret->name = p->name;
			for (j = 0; j < p->n; ++j) {
				for (k = 0; k < p->n; ++k) {
					if(p->fields[k].idx == j){
						ret->fields[j].value = data & p->fields[k].mask;
						ret->fields[j].value >>= p->fields[k].shr;
						ret->fields[j].value <<= p->fields[k].shl;
						ret->fields[j].value += p->fields[k].add;
						ret->fields[j].value &= 0xFFFF;
						ret->fields[j].type = p->fields[k].type;
						break;
					}
				}
			}
			ret->n = p->n;
			return ret;
		}
	}
	return NULL;
} 

void decode (const u8* buffer, u32 size) {
	u32 i, j;
	vle_t *op = NULL;

	for (i = 0; i < size; i += 2) {
		op = find_se (&buffer[i]);
		if(op) {
			printf ("%02X %02X      %s ", buffer[i], buffer[i+1], op->name);
			for (j = 0; j < op->n; ++j) {
				if (op->fields[j].type == REG) {
					printf ("r%u ", op->fields[j].value);
				} else if (op->fields[j].type == IMM) {
					printf ("0x%x ", op->fields[j].value);
				} else if (op->fields[j].type == MEM)  {
					printf ("0x%x(r%d) ", op->fields[j].value, op->fields[j + 1].value);
					j++;
				} else if (op->fields[j].type == CR)  {
					printf ("cr%u ", op->fields[j].value);
				}
			}
			printf ("\n");
			free (op);
		}
	}
}