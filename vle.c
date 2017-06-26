#include "vle.h"
#include "vle_internal.h"
#include <stdlib.h>
#include <stdio.h>

#define TYPE_NONE 0
#define TYPE_REG  1
#define TYPE_IMM  2
#define TYPE_MEM  3
#define TYPE_JMP  4
#define TYPE_CR   5

#define E_NONE 0
#define E_X    1
#define E_XL   2
#define E_D    3
#define E_D8   4
#define E_I16A 5
#define E_SCI8 6
#define E_I16L 7
#define E_BD24 8
#define E_BD15 9
#define E_IA16 10
#define E_LI20 11
#define E_M    12
#define E_XCR  13
#define E_XLSP 14

#define E_MASK_X    0x03FFF800
#define E_MASK_XL   0x03FFF801
#define E_MASK_D    0x01FFFFFF
#define E_MASK_D8   0x03FF00FF
#define E_MASK_I16A 0x03FF07FF
#define E_MASK_SCI8 0x03FF07FF
#define E_MASK_I16L 0x03FF07FF
#define E_MASK_BD24 0x03FFFFFE
#define E_MASK_BD15 0x000CFFFE
#define E_MASK_IA16 0x03FF07FF
#define E_MASK_LI20 0x03FF7FFF
#define E_MASK_M    0x03FFFFFE

/*
I16A 
*/
const e_vle_t e_array[] = {
//	{ "name"       , op        , mask                    , type  }
	{ "e_add16i"   , 0x1C000000, 0x1C000000 | E_MASK_D   , E_D   , {TYPE_NONE}},
	{ "e_add2i."   , 0x70008800, 0x70008800 | E_MASK_I16A, E_I16A, {TYPE_NONE}},
	{ "e_add2is"   , 0x70009000, 0x70009000 | E_MASK_I16A, E_I16A, {TYPE_NONE}},
	{ "e_addi"     , 0x18008000, 0x18008000 | E_MASK_SCI8, E_SCI8, {TYPE_NONE}},
	{ "e_addi."    , 0x18008800, 0x18008800 | E_MASK_SCI8, E_SCI8, {TYPE_NONE}},
	{ "e_addic"    , 0x18009000, 0x18009000 | E_MASK_SCI8, E_SCI8, {TYPE_NONE}},
	{ "e_addic."   , 0x18009800, 0x18009800 | E_MASK_SCI8, E_SCI8, {TYPE_NONE}},
	{ "e_and2i."   , 0x7000C800, 0x7000C800 | E_MASK_I16L, E_I16L, {TYPE_NONE}},
	{ "e_and2is."  , 0x7000E800, 0x7000E800 | E_MASK_I16L, E_I16L, {TYPE_NONE}},
	{ "e_andi"     , 0x1800C000, 0x1800C000 | E_MASK_SCI8, E_SCI8, {TYPE_NONE}},
	{ "e_andi."    , 0x1800C800, 0x1800C800 | E_MASK_SCI8, E_SCI8, {TYPE_NONE}},
	{ "e_b"        , 0x78000000, 0x78000000 | E_MASK_BD24, E_BD24, {TYPE_NONE}},
	{ "e_bl"       , 0x78000001, 0x78000001 | E_MASK_BD24, E_BD24, {TYPE_NONE}},
	// has cr0-cr3 
	{ "e_bge"      , 0x7A000000, 0x7A000000 | E_MASK_BD15, E_BD15, {TYPE_NONE}},
	{ "e_ble"      , 0x7A000000, 0x7A010000 | E_MASK_BD15, E_BD15, {TYPE_NONE}},
	{ "e_bne"      , 0x7A000000, 0x7A020000 | E_MASK_BD15, E_BD15, {TYPE_NONE}},
	{ "e_bns"      , 0x7A000000, 0x7A030000 | E_MASK_BD15, E_BD15, {TYPE_NONE}},
	{ "e_blt"      , 0x7A000000, 0x7A110000 | E_MASK_BD15, E_BD15, {TYPE_NONE}},
	{ "e_bgt"      , 0x7A000000, 0x7A120000 | E_MASK_BD15, E_BD15, {TYPE_NONE}},
	{ "e_beq"      , 0x7A000000, 0x7A130000 | E_MASK_BD15, E_BD15, {TYPE_NONE}},
	{ "e_bso"      , 0x7A000000, 0x7A140000 | E_MASK_BD15, E_BD15, {TYPE_NONE}},
	{ "e_bc"       , 0x7A000000, 0x7A140000 | E_MASK_BD15, E_BD15, {TYPE_NONE}},
	{ "e_bgel"     , 0x7A000001, 0x7A000001 | E_MASK_BD15, E_BD15, {TYPE_NONE}},
	{ "e_blel"     , 0x7A000001, 0x7A010001 | E_MASK_BD15, E_BD15, {TYPE_NONE}},
	{ "e_bnel"     , 0x7A000001, 0x7A020001 | E_MASK_BD15, E_BD15, {TYPE_NONE}},
	{ "e_bnsl"     , 0x7A000001, 0x7A030001 | E_MASK_BD15, E_BD15, {TYPE_NONE}},
	{ "e_bltl"     , 0x7A000001, 0x7A110001 | E_MASK_BD15, E_BD15, {TYPE_NONE}},
	{ "e_bgtl"     , 0x7A000001, 0x7A120001 | E_MASK_BD15, E_BD15, {TYPE_NONE}},
	{ "e_beql"     , 0x7A000001, 0x7A130001 | E_MASK_BD15, E_BD15, {TYPE_NONE}},
	{ "e_bsol"     , 0x7A000001, 0x7A140001 | E_MASK_BD15, E_BD15, {TYPE_NONE}},
	{ "e_bcl"      , 0x7A000001, 0x7A140001 | E_MASK_BD15, E_BD15, {TYPE_NONE}},
	// has cr0-cr3 
	{ "e_bgectr"   , 0x7A000000, 0x7A200000 | E_MASK_BD15, E_BD15, {TYPE_NONE}},
	{ "e_blectr"   , 0x7A000000, 0x7A210000 | E_MASK_BD15, E_BD15, {TYPE_NONE}},
	{ "e_bnectr"   , 0x7A000000, 0x7A220000 | E_MASK_BD15, E_BD15, {TYPE_NONE}},
	{ "e_bnsctr"   , 0x7A000000, 0x7A230000 | E_MASK_BD15, E_BD15, {TYPE_NONE}},
	{ "e_bltctr"   , 0x7A000000, 0x7A310000 | E_MASK_BD15, E_BD15, {TYPE_NONE}},
	{ "e_bgtctr"   , 0x7A000000, 0x7A320000 | E_MASK_BD15, E_BD15, {TYPE_NONE}},
	{ "e_beqctr"   , 0x7A000000, 0x7A330000 | E_MASK_BD15, E_BD15, {TYPE_NONE}},
	{ "e_bsoctr"   , 0x7A000000, 0x7A340000 | E_MASK_BD15, E_BD15, {TYPE_NONE}},
	{ "e_bcctr"    , 0x7A000000, 0x7A340000 | E_MASK_BD15, E_BD15, {TYPE_NONE}},
	{ "e_bgectrl"  , 0x7A000001, 0x7A200001 | E_MASK_BD15, E_BD15, {TYPE_NONE}},
	{ "e_blectrl"  , 0x7A000001, 0x7A210001 | E_MASK_BD15, E_BD15, {TYPE_NONE}},
	{ "e_bnectrl"  , 0x7A000001, 0x7A220001 | E_MASK_BD15, E_BD15, {TYPE_NONE}},
	{ "e_bnsctrl"  , 0x7A000001, 0x7A230001 | E_MASK_BD15, E_BD15, {TYPE_NONE}},
	{ "e_bltctrl"  , 0x7A000001, 0x7A310001 | E_MASK_BD15, E_BD15, {TYPE_NONE}},
	{ "e_bgtctrl"  , 0x7A000001, 0x7A320001 | E_MASK_BD15, E_BD15, {TYPE_NONE}},
	{ "e_beqctrl"  , 0x7A000001, 0x7A330001 | E_MASK_BD15, E_BD15, {TYPE_NONE}},
	{ "e_bsoctrl"  , 0x7A000001, 0x7A340001 | E_MASK_BD15, E_BD15, {TYPE_NONE}},
	{ "e_bcctrl"   , 0x7A000001, 0x7A340001 | E_MASK_BD15, E_BD15, {TYPE_NONE}},
	{ "e_cmp16i"   , 0x70009800, 0x70009800 | E_MASK_IA16, E_IA16, {TYPE_NONE}},
	{ "e_cmph16i"  , 0x7000B000, 0x7000B000 | E_MASK_IA16, E_IA16, {TYPE_NONE}},
	{ "e_cmph"     , 0x7C00001C, 0x7C00001D | E_MASK_X   , E_XCR , {TYPE_CR, TYPE_REG, TYPE_REG, TYPE_NONE, TYPE_NONE}},
	{ "e_cmphl16i" , 0x7000B800, 0x7000B800 | E_MASK_IA16, E_IA16, {TYPE_NONE}},
	{ "e_cmphl"    , 0x7C00005C, 0x7C00005D | E_MASK_X   , E_XCR , {TYPE_CR, TYPE_REG, TYPE_REG, TYPE_NONE, TYPE_NONE}},
	{ "e_cmpi"     , 0x1800A800, 0x1800A800 | E_MASK_SCI8, E_SCI8, {TYPE_NONE}},
	{ "e_cmpl16i"  , 0x7000A800, 0x7000A800 | E_MASK_IA16, E_IA16, {TYPE_NONE}},
	{ "e_cmpli"    , 0x1880A800, 0x1880A800 | E_MASK_SCI8, E_SCI8, {TYPE_NONE}},
	{ "e_crand"    , 0x7C000202, 0x7C000202 | E_MASK_XL  , E_XL  , {TYPE_CR, TYPE_CR, TYPE_CR, TYPE_NONE, TYPE_NONE}},
	{ "e_crandc"   , 0x7C000102, 0x7C000102 | E_MASK_XL  , E_XL  , {TYPE_CR, TYPE_CR, TYPE_CR, TYPE_NONE, TYPE_NONE}},
	{ "e_creqv"    , 0x7C000242, 0x7C000242 | E_MASK_XL  , E_XL  , {TYPE_CR, TYPE_CR, TYPE_CR, TYPE_NONE, TYPE_NONE}},
	{ "e_crnand"   , 0x7C0001C2, 0x7C0001C2 | E_MASK_XL  , E_XL  , {TYPE_CR, TYPE_CR, TYPE_CR, TYPE_NONE, TYPE_NONE}},
	{ "e_crnor"    , 0x7C000042, 0x7C000042 | E_MASK_XL  , E_XL  , {TYPE_CR, TYPE_CR, TYPE_CR, TYPE_NONE, TYPE_NONE}},
	{ "e_cror"     , 0x7C000382, 0x7C000382 | E_MASK_XL  , E_XL  , {TYPE_CR, TYPE_CR, TYPE_CR, TYPE_NONE, TYPE_NONE}},
	{ "e_crorc"    , 0x7C000342, 0x7C000342 | E_MASK_XL  , E_XL  , {TYPE_CR, TYPE_CR, TYPE_CR, TYPE_NONE, TYPE_NONE}},
	{ "e_crxor"    , 0x7C000182, 0x7C000182 | E_MASK_XL  , E_XL  , {TYPE_CR, TYPE_CR, TYPE_CR, TYPE_NONE, TYPE_NONE}},
	{ "e_lbz"      , 0x30000000, 0x30000000 | E_MASK_D   , E_D   , {TYPE_NONE}},
	{ "e_lbzu"     , 0x18000000, 0x18000000 | E_MASK_D8  , E_D8  , {TYPE_NONE}},
	{ "e_lha"      , 0x38000000, 0x38000000 | E_MASK_D   , E_D   , {TYPE_NONE}},
	{ "e_lhau"     , 0x18000300, 0x18000300 | E_MASK_D8  , E_D8  , {TYPE_NONE}},
	{ "e_lhz"      , 0x58000000, 0x58000000 | E_MASK_D   , E_D   , {TYPE_NONE}},
	{ "e_lhzu"     , 0x18000100, 0x18000100 | E_MASK_D8  , E_D8  , {TYPE_NONE}},
	{ "e_li"       , 0x70000000, 0x70000000 | E_MASK_LI20, E_LI20, {TYPE_NONE}},
	{ "e_lis"      , 0x7000E000, 0x7000E000 | E_MASK_I16L, E_I16L, {TYPE_NONE}},
	{ "e_lmw"      , 0x18000800, 0x18000800 | E_MASK_D8  , E_D8  , {TYPE_NONE}},
	{ "e_lwz"      , 0x50000000, 0x50000000 | E_MASK_D   , E_D   , {TYPE_NONE}},
	{ "e_lwzu"     , 0x18000200, 0x18000200 | E_MASK_D8  , E_D8  , {TYPE_NONE}},
	{ "e_mcrf"     , 0x7C000020, 0x7C000020 | E_MASK_XL  , E_XLSP, {TYPE_CR, TYPE_CR, TYPE_NONE, TYPE_NONE, TYPE_NONE}},
	{ "e_mull2i"   , 0x7000A000, 0x7000A000 | E_MASK_I16A, E_I16A, {TYPE_NONE}},
	{ "e_mulli"    , 0x1800A000, 0x1800A000 | E_MASK_SCI8, E_SCI8, {TYPE_NONE}},
	{ "e_or2i"     , 0x7000C000, 0x7000C000 | E_MASK_I16L, E_I16L, {TYPE_NONE}},
	{ "e_or2is"    , 0x7000D000, 0x7000D000 | E_MASK_I16L, E_I16L, {TYPE_NONE}},
	{ "e_ori"      , 0x1800D000, 0x1800D000 | E_MASK_SCI8, E_SCI8, {TYPE_NONE}},
	{ "e_ori."     , 0x1800D800, 0x1800D800 | E_MASK_SCI8, E_SCI8, {TYPE_NONE}},
	{ "e_rlw"      , 0x7C000230, 0x7C000230 | E_MASK_X   , E_X   , {TYPE_REG, TYPE_REG, TYPE_REG, TYPE_NONE, TYPE_NONE}},
	{ "e_rlw."     , 0x7C000231, 0x7C000231 | E_MASK_X   , E_X   , {TYPE_REG, TYPE_REG, TYPE_REG, TYPE_NONE, TYPE_NONE}},
	{ "e_rlwi"     , 0x7C000270, 0x7C000270 | E_MASK_X   , E_X   , {TYPE_REG, TYPE_REG, TYPE_REG, TYPE_NONE, TYPE_NONE}},
	{ "e_rlwi."    , 0x7C000271, 0x7C000271 | E_MASK_X   , E_X   , {TYPE_REG, TYPE_REG, TYPE_REG, TYPE_NONE, TYPE_NONE}},
	{ "e_rlwimi"   , 0x74000000, 0x74000000 | E_MASK_M   , E_M   , {TYPE_NONE}},
	{ "e_rlwinm"   , 0x74000001, 0x74000001 | E_MASK_M   , E_M   , {TYPE_NONE}},
	{ "e_slwi"     , 0x7C000070, 0x7C000070 | E_MASK_X   , E_X   , {TYPE_REG, TYPE_REG, TYPE_REG, TYPE_NONE, TYPE_NONE}},
	{ "e_slwi."    , 0x7C000071, 0x7C000071 | E_MASK_X   , E_X   , {TYPE_REG, TYPE_REG, TYPE_REG, TYPE_NONE, TYPE_NONE}},
	{ "e_srwi"     , 0x7C000470, 0x7C000470 | E_MASK_X   , E_X   , {TYPE_REG, TYPE_REG, TYPE_REG, TYPE_NONE, TYPE_NONE}},
	{ "e_srwi."    , 0x7C000471, 0x7C000471 | E_MASK_X   , E_X   , {TYPE_REG, TYPE_REG, TYPE_REG, TYPE_NONE, TYPE_NONE}},
	{ "e_stb"      , 0x34000000, 0x34000000 | E_MASK_D   , E_D   , {TYPE_NONE}},
	{ "e_stbu"     , 0x18000400, 0x18000400 | E_MASK_D8  , E_D8  , {TYPE_NONE}},
	{ "e_sth"      , 0x5C000000, 0x5C000000 | E_MASK_D   , E_D   , {TYPE_NONE}},
	{ "e_sthu"     , 0x18000500, 0x18000500 | E_MASK_D8  , E_D8  , {TYPE_NONE}},
	{ "e_stmw"     , 0x18000900, 0x18000900 | E_MASK_D8  , E_D8  , {TYPE_NONE}},
	{ "e_stw"      , 0x54000000, 0x54000000 | E_MASK_D   , E_D   , {TYPE_NONE}},
	{ "e_stwu"     , 0x18000600, 0x18000600 | E_MASK_D8  , E_D8  , {TYPE_NONE}},
	{ "e_subfic"   , 0x1800B000, 0x1800B000 | E_MASK_SCI8, E_SCI8, {TYPE_NONE}},
	{ "e_subfic."  , 0x1800B800, 0x1800B800 | E_MASK_SCI8, E_SCI8, {TYPE_NONE}},
	{ "e_xori"     , 0x1800E000, 0x1800E000 | E_MASK_SCI8, E_SCI8, {TYPE_NONE}},
	{ "e_xori."    , 0x1800E800, 0x1800E800 | E_MASK_SCI8, E_SCI8, {TYPE_NONE}},
};
// page 96
// page 1264
const se_vle_t se_array[] = {
//	{ "name"      , op    , mask  , n, {{field ,shl,shr,  +, i, TYPE_REG}, ...}
	{ "se_illegal", 0x0000, 0x0000, 0, {{0}, {0}, {0}, {0}, {0}}},
	{ "se_isync"  , 0x0001, 0x0001, 0, {{0}, {0}, {0}, {0}, {0}}},
	{ "se_sc"     , 0x0002, 0x0002, 0, {{0}, {0}, {0}, {0}, {0}}},
	{ "se_blr"    , 0x0004, 0x0004, 0, {{0}, {0}, {0}, {0}, {0}}},
	{ "se_blrl"   , 0x0005, 0x0005, 0, {{0}, {0}, {0}, {0}, {0}}},
	{ "se_bctr"   , 0x0006, 0x0006, 0, {{0}, {0}, {0}, {0}, {0}}},
	{ "se_bctrl"  , 0x0007, 0x0007, 0, {{0}, {0}, {0}, {0}, {0}}},
	{ "se_rfi"    , 0x0008, 0x0008, 0, {{0}, {0}, {0}, {0}, {0}}},
	{ "se_rfci"   , 0x0009, 0x0009, 0, {{0}, {0}, {0}, {0}, {0}}},
	{ "se_rfdi"   , 0x000A, 0x000A, 0, {{0}, {0}, {0}, {0}, {0}}},
	{ "se_not"    , 0x0020, 0x002F, 1, {{0x000F,  0,  0,  0, 0, TYPE_REG}, {0}, {0}, {0}, {0}}},
	{ "se_neg"    , 0x0030, 0x003F, 1, {{0x000F,  0,  0,  0, 0, TYPE_REG}, {0}, {0}, {0}, {0}}},
	{ "se_mflr"   , 0x0080, 0x008F, 1, {{0x000F,  0,  0,  0, 0, TYPE_REG}, {0}, {0}, {0}, {0}}},
	{ "se_mtlr"   , 0x0090, 0x009F, 1, {{0x000F,  0,  0,  0, 0, TYPE_REG}, {0}, {0}, {0}, {0}}},
	{ "se_mfctr"  , 0x00A0, 0x00AF, 1, {{0x000F,  0,  0,  0, 0, TYPE_REG}, {0}, {0}, {0}, {0}}},
	{ "se_mtctr"  , 0x00B0, 0x00BF, 1, {{0x000F,  0,  0,  0, 0, TYPE_REG}, {0}, {0}, {0}, {0}}},
	{ "se_extzb"  , 0x00C0, 0x00CF, 1, {{0x000F,  0,  0,  0, 0, TYPE_REG}, {0}, {0}, {0}, {0}}},
	{ "se_extsb"  , 0x00D0, 0x00DF, 1, {{0x000F,  0,  0,  0, 0, TYPE_REG}, {0}, {0}, {0}, {0}}},
	{ "se_extzh"  , 0x00E0, 0x00EF, 1, {{0x000F,  0,  0,  0, 0, TYPE_REG}, {0}, {0}, {0}, {0}}},
	{ "se_extsh"  , 0x00F0, 0x00FF, 1, {{0x000F,  0,  0,  0, 0, TYPE_REG}, {0}, {0}, {0}, {0}}},
	{ "se_mr"     , 0x0100, 0x01FF, 2, {{0x00F0,  4,  0,  0, 1, TYPE_REG}, {0x000F,  0,  0,  0,  0, TYPE_REG}, {0}, {0}, {0}}},
	{ "se_mtar"   , 0x0200, 0x02FF, 2, {{0x00F0,  4,  0,  0, 1, TYPE_REG}, {0x000F,  0,  0,  8,  0, TYPE_REG}, {0}, {0}, {0}}},
	{ "se_mfar"   , 0x0300, 0x03FF, 2, {{0x00F0,  4,  0,  8, 1, TYPE_REG}, {0x000F,  0,  0,  0,  0, TYPE_REG}, {0}, {0}, {0}}},
	{ "se_add"    , 0x0400, 0x04FF, 2, {{0x00F0,  4,  0,  0, 1, TYPE_REG}, {0x000F,  0,  0,  0,  0, TYPE_REG}, {0}, {0}, {0}}},
	{ "se_mullw"  , 0x0500, 0x05FF, 2, {{0x00F0,  4,  0,  0, 1, TYPE_REG}, {0x000F,  0,  0,  0,  0, TYPE_REG}, {0}, {0}, {0}}},
	{ "se_cmp"    , 0x0C00, 0x0CFF, 2, {{0x00F0,  4,  0,  0, 1, TYPE_REG}, {0x000F,  0,  0,  0,  0, TYPE_REG}, {0}, {0}, {0}}},
	{ "se_cmpl"   , 0x0D00, 0x0DFF, 2, {{0x00F0,  4,  0,  0, 1, TYPE_REG}, {0x000F,  0,  0,  0,  0, TYPE_REG}, {0}, {0}, {0}}},
	{ "se_cmph"   , 0x0E00, 0x0EFF, 2, {{0x00F0,  4,  0,  0, 1, TYPE_REG}, {0x000F,  0,  0,  0,  0, TYPE_REG}, {0}, {0}, {0}}},
	{ "se_cmphl"  , 0x0F00, 0x0FFF, 2, {{0x00F0,  4,  0,  0, 1, TYPE_REG}, {0x000F,  0,  0,  0,  0, TYPE_REG}, {0}, {0}, {0}}},
	{ "se_addi"   , 0x2000, 0x21FF, 2, {{0x01F0,  4,  0,  1, 1, TYPE_IMM}, {0x000F,  0,  0,  0,  0, TYPE_REG}, {0}, {0}, {0}}},
	{ "se_and"    , 0x4600, 0x46FF, 2, {{0x00F0,  4,  0,  0, 1, TYPE_REG}, {0x000F,  0,  0,  0,  0, TYPE_REG}, {0}, {0}, {0}}},
	{ "se_and."   , 0x4700, 0x47FF, 2, {{0x00F0,  4,  0,  0, 1, TYPE_REG}, {0x000F,  0,  0,  0,  0, TYPE_REG}, {0}, {0}, {0}}},
	{ "se_andi"   , 0x2F00, 0x2FFF, 2, {{0x01F0,  4,  0,  0, 1, TYPE_IMM}, {0x000F,  0,  0,  0,  0, TYPE_REG}, {0}, {0}, {0}}},
	{ "se_andc"   , 0x4500, 0x45FF, 2, {{0x00F0,  4,  0,  0, 1, TYPE_REG}, {0x000F,  0,  0,  0,  0, TYPE_REG}, {0}, {0}, {0}}},
	{ "se_b"      , 0xE800, 0xE8FF, 1, {{0x00FF,  0,  1,  0, 0, TYPE_JMP}, {0}, {0}, {0}, {0}}},
	{ "se_bl"     , 0xE900, 0xE9FF, 1, {{0x00FF,  0,  1,  0, 0, TYPE_JMP}, {0}, {0}, {0}, {0}}},
	{ "se_bge"    , 0xE000, 0xE0FF, 1, {{0x00FF,  0,  1,  0, 0, TYPE_JMP}, {0}, {0}, {0}, {0}}},
	{ "se_ble"    , 0xE000, 0xE1FF, 1, {{0x00FF,  0,  1,  0, 0, TYPE_JMP}, {0}, {0}, {0}, {0}}},
	{ "se_bne"    , 0xE000, 0xE2FF, 1, {{0x00FF,  0,  1,  0, 0, TYPE_JMP}, {0}, {0}, {0}, {0}}},
	{ "se_bns"    , 0xE000, 0xE3FF, 1, {{0x00FF,  0,  1,  0, 0, TYPE_JMP}, {0}, {0}, {0}, {0}}},
	{ "se_blt"    , 0xE000, 0xE4FF, 1, {{0x00FF,  0,  1,  0, 0, TYPE_JMP}, {0}, {0}, {0}, {0}}},
	{ "se_bgt"    , 0xE000, 0xE5FF, 1, {{0x00FF,  0,  1,  0, 0, TYPE_JMP}, {0}, {0}, {0}, {0}}},
	{ "se_beq"    , 0xE000, 0xE6FF, 1, {{0x00FF,  0,  1,  0, 0, TYPE_JMP}, {0}, {0}, {0}, {0}}},
	{ "se_bso"    , 0xE000, 0xE7FF, 1, {{0x00FF,  0,  1,  0, 0, TYPE_JMP}, {0}, {0}, {0}, {0}}},
	{ "se_bc"     , 0xE000, 0xE7FF, 2, {{0x0700,  8,  0, 32, 0, TYPE_IMM}, {0x00FF,  0,  1,  0,  1, TYPE_IMM}, {0}, {0}, {0}}},
	{ "se_bclri"  , 0x6000, 0x61FF, 2, {{0x01F0,  4,  0,  0, 1, TYPE_IMM}, {0x000F,  0,  0,  0,  0, TYPE_REG}, {0}, {0}, {0}}},
	{ "se_bgeni"  , 0x6300, 0x63FF, 2, {{0x01F0,  4,  0,  0, 1, TYPE_IMM}, {0x000F,  0,  0,  0,  0, TYPE_REG}, {0}, {0}, {0}}},
	{ "se_bmaski" , 0x2C00, 0x2DFF, 2, {{0x01F0,  4,  0,  0, 1, TYPE_IMM}, {0x000F,  0,  0,  0,  0, TYPE_REG}, {0}, {0}, {0}}},
	{ "se_bseti"  , 0x6400, 0x65FF, 2, {{0x01F0,  4,  0,  0, 1, TYPE_IMM}, {0x000F,  0,  0,  0,  0, TYPE_REG}, {0}, {0}, {0}}},
	{ "se_btsti"  , 0x6600, 0x67FF, 2, {{0x01F0,  4,  0,  0, 1, TYPE_IMM}, {0x000F,  0,  0,  0,  0, TYPE_REG}, {0}, {0}, {0}}},
	{ "se_cmpi"   , 0x2A00, 0x2BFF, 2, {{0x01F0,  4,  0,  0, 1, TYPE_IMM}, {0x000F,  0,  0,  0,  0, TYPE_REG}, {0}, {0}, {0}}},
	{ "se_cmpli"  , 0x2200, 0x23FF, 2, {{0x01F0,  4,  0,  1, 1, TYPE_IMM}, {0x000F,  0,  0,  0,  0, TYPE_REG}, {0}, {0}, {0}}},
	{ "se_lbz"    , 0x8000, 0x8FFF, 3, {{0x0F00,  6,  0,  0, 1, TYPE_MEM}, {0x00F0,  4,  0,  0,  0, TYPE_REG}, {0x000F,  0,  0,  0,  2, TYPE_REG}, {0}, {0}}},
	{ "se_lbh"    , 0xA000, 0xAFFF, 3, {{0x0F00,  6,  0,  0, 1, TYPE_MEM}, {0x00F0,  4,  0,  0,  0, TYPE_REG}, {0x000F,  0,  0,  0,  2, TYPE_REG}, {0}, {0}}},
	{ "se_li"     , 0x4800, 0x4FFF, 2, {{0x07F0,  4,  0,  0, 1, TYPE_IMM}, {0x000F,  0,  0,  0,  0, TYPE_REG}, {0}, {0}, {0}}},
	{ "se_lwz"    , 0xC000, 0xCFFF, 3, {{0x0F00,  6,  0,  0, 1, TYPE_MEM}, {0x00F0,  4,  0,  0,  0, TYPE_REG}, {0x000F,  0,  0,  0,  2, TYPE_REG}, {0}, {0}}},
	{ "se_or"     , 0x4400, 0x44FF, 2, {{0x00F0,  4,  0,  0, 1, TYPE_REG}, {0x000F,  0,  0,  0,  0, TYPE_REG}, {0}, {0}, {0}}},
	{ "se_slw"    , 0x4200, 0x42FF, 2, {{0x00F0,  4,  0,  0, 0, TYPE_REG}, {0x000F,  0,  0,  0,  2, TYPE_REG}, {0}, {0}, {0}}},
	{ "se_slwi"   , 0x6C00, 0x6DFF, 2, {{0x01F0,  4,  0,  0, 1, TYPE_IMM}, {0x000F,  0,  0,  0,  0, TYPE_REG}, {0}, {0}, {0}}},
	{ "se_sraw"   , 0x4100, 0x41FF, 2, {{0x00F0,  4,  0,  0, 0, TYPE_REG}, {0x000F,  0,  0,  0,  2, TYPE_REG}, {0}, {0}, {0}}},
	{ "se_srawi"  , 0x6A00, 0x6BFF, 2, {{0x01F0,  4,  0,  0, 1, TYPE_IMM}, {0x000F,  0,  0,  0,  0, TYPE_REG}, {0}, {0}, {0}}},
	{ "se_srw"    , 0x4000, 0x40FF, 2, {{0x00F0,  4,  0,  0, 0, TYPE_REG}, {0x000F,  0,  0,  0,  2, TYPE_REG}, {0}, {0}, {0}}},
	{ "se_srwi"   , 0x6800, 0x69FF, 2, {{0x01F0,  4,  0,  0, 1, TYPE_IMM}, {0x000F,  0,  0,  0,  0, TYPE_REG}, {0}, {0}, {0}}},
	{ "se_stb"    , 0x9000, 0x9FFF, 3, {{0x0F00,  6,  0,  0, 1, TYPE_MEM}, {0x00F0,  4,  0,  0,  0, TYPE_REG}, {0x000F,  0,  0,  0,  2, TYPE_REG}, {0}, {0}}},
	{ "se_sth"    , 0xB000, 0xBFFF, 3, {{0x0F00,  6,  0,  0, 1, TYPE_MEM}, {0x00F0,  4,  0,  0,  0, TYPE_REG}, {0x000F,  0,  0,  0,  2, TYPE_REG}, {0}, {0}}},
	{ "se_stw"    , 0xD000, 0xDFFF, 3, {{0x0F00,  6,  0,  0, 1, TYPE_MEM}, {0x00F0,  4,  0,  0,  0, TYPE_REG}, {0x000F,  0,  0,  0,  2, TYPE_REG}, {0}, {0}}},
	{ "se_sub"    , 0x0600, 0x06FF, 2, {{0x00F0,  4,  0,  0, 0, TYPE_REG}, {0x000F,  0,  0,  0,  2, TYPE_REG}, {0}, {0}, {0}}},
	{ "se_subf"   , 0x0700, 0x07FF, 2, {{0x00F0,  4,  0,  0, 0, TYPE_REG}, {0x000F,  0,  0,  0,  2, TYPE_REG}, {0}, {0}, {0}}},
	{ "se_subi"   , 0x2500, 0x25FF, 2, {{0x01F0,  4,  0,  1, 1, TYPE_IMM}, {0x000F,  0,  0,  0,  0, TYPE_REG}, {0}, {0}, {0}}},
	{ "se_subi."  , 0x2700, 0x27FF, 2, {{0x01F0,  4,  0,  1, 1, TYPE_IMM}, {0x000F,  0,  0,  0,  0, TYPE_REG}, {0}, {0}, {0}}},
};

static void set_e_fields(vle_t * v, const e_vle_t* p, u32 data) {
	if (!v) {
		return;
	}
	switch(p->type) {
	case E_X:
		{
			v->n = 3;
			v->fields[0].value = (data & 0x3E00000) >> 24;
			v->fields[0].type = p->types[0];
			v->fields[1].value = (data & 0x1F0000) >> 16;
			v->fields[1].type = p->types[1];
			v->fields[2].value = (data & 0xF800) >> 11;
			v->fields[2].type = p->types[2];
		}
		break;
	case E_XL:
		{
			v->n = 3;
			v->fields[0].value = (data & 0x3E00000) >> 21;
			v->fields[0].type = p->types[0];
			v->fields[1].value = (data & 0x1F0000) >> 16;
			v->fields[1].type = p->types[1];
			v->fields[2].value = (data & 0xF800) >> 11;
			v->fields[2].type = p->types[2];
		}
		break;
	case E_D:
		break;
	case E_D8:
		break;
	case E_I16A:
		break;
	case E_SCI8:
		break;
	case E_I16L:
		break;
	case E_BD24:
		break;
	case E_BD15:
		break;
	case E_IA16:
		break;
	case E_LI20:
		break;
	case E_M:
		break;
	case E_XCR:
		{
			v->n = 3;
			v->fields[0].value = (data & 0x3000000) >> 24;
			v->fields[0].type = p->types[0];
			v->fields[1].value = (data & 0x1F0000) >> 16;
			v->fields[1].type = p->types[1];
			v->fields[2].value = (data & 0xF800) >> 11;
			v->fields[2].type = p->types[2];
		}
		break;
	case E_XLSP:
		break;
	case E_NONE:
	default:
		v->n = 0;
		break;
	}
}

static vle_t *find_e (const u8* buffer) {
	u32 i;
	u32 data = (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | buffer[3];
	const e_vle_t* p = NULL;
	const u32 size = sizeof (e_array) / sizeof (e_vle_t);
	for (i = 0; i < size; ++i) {
		p = &e_array[i];
		if ((p->op & data) == p->op && (p->mask & data) == data) {
			vle_t* ret = (vle_t*) calloc (1, sizeof (vle_t));
			ret->name = p->name;
			ret->n = 0;
			set_e_fields (ret, p, data);
			return ret;
		}
	}
	return NULL;
} 

static vle_t *find_se (const u8* buffer) {
	u32 i, j, k;
	u16 data = (buffer[0] << 8) | buffer[1];
	const se_vle_t* p = NULL;
	const u32 size = sizeof (se_array) / sizeof (se_vle_t);
	for (i = 0; i < size; ++i) {
		p = &se_array[i];
		if ((p->op & data) == p->op && (p->mask & data) == data) {
			vle_t* ret = (vle_t*) calloc (1, sizeof (vle_t));
			ret->name = p->name;
			for (j = 0; j < p->n; ++j) {
				for (k = 0; k < p->n; ++k) {
					if (p->fields[k].idx == j) {
						ret->fields[j].value = data & p->fields[k].mask;
						ret->fields[j].value >>= p->fields[k].shr;
						ret->fields[j].value <<= p->fields[k].shl;
						ret->fields[j].value += p->fields[k].add;
						ret->fields[j].value &= 0xFFFF;
						if (p->fields[k].type == TYPE_JMP && ret->fields[j].value & 0x0100) {
							ret->fields[j].value = -ret->fields[j].value;
						}
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
	int se = 0;
	for (i = 0; i < size; i += se ? 2 : 4) {
		se = 0;
		if(i + 2 < size){
			op = find_e (&buffer[i]);
		}
		if(!op) {
			se = 1;
			op = find_se (&buffer[i]);
		}
		if (op) {
			if(se)
				printf ("%02X %02X        %-10s ", buffer[i], buffer[i+1], op->name);
			else
				printf ("%02X %02X %02X %02X  %-10s ", buffer[i], buffer[i+1], buffer[i+2], buffer[i+3], op->name);
			for (j = 0; j < op->n; ++j) {
				if (op->fields[j].type == TYPE_REG) {
					printf ("r%-2u ", op->fields[j].value);
				} else if (op->fields[j].type == TYPE_IMM) {
					printf ("0x%x ", op->fields[j].value);
				} else if (op->fields[j].type == TYPE_MEM)  {
					printf ("0x%x(r%d) ", op->fields[j].value, op->fields[j + 1].value);
					j++;
				} else if (op->fields[j].type == TYPE_JMP) {
					printf ("0x%x ", op->fields[j].value);
				} else if (op->fields[j].type == TYPE_CR) {
					printf ("cr%u ", op->fields[j].value);
				}
			}
			printf ("\n");
			free (op);
			op = NULL;
		} else {
			printf("%02X %02X        INVALID\n", buffer[i], buffer[i+1]);
		}
	}
}