#include "vle.h"
#include <stdio.h>
#include <string.h>

#define SZ_SE   (2)
#define SZ_E    (4)
#define SZ_PPC  (4)

typedef struct {
	const uint8_t  bytes[4];
	const uint32_t size;
	const char*    expected;
} test_t;

const test_t test_se_only[] = {
	{{0x00, 0x00, 0x00, 0x00}, SZ_SE , "se_illegal"},
	{{0x00, 0x01, 0x00, 0x00}, SZ_SE , "se_isync"},
	{{0x00, 0x02, 0x00, 0x00}, SZ_SE , "se_sc"},
	{{0x00, 0x04, 0x00, 0x00}, SZ_SE , "se_blr"},
	{{0x00, 0x05, 0x00, 0x00}, SZ_SE , "se_blrl"},
	{{0x00, 0x06, 0x00, 0x00}, SZ_SE , "se_bctr"},
	{{0x00, 0x07, 0x00, 0x00}, SZ_SE , "se_bctrl"},
	{{0x00, 0x08, 0x00, 0x00}, SZ_SE , "se_rfi"},
	{{0x00, 0x09, 0x00, 0x00}, SZ_SE , "se_rfci"},
	{{0x00, 0x0A, 0x00, 0x00}, SZ_SE , "se_rfdi"},
	{{0x00, 0x29, 0x00, 0x00}, SZ_SE , "se_not r25"},
	{{0x00, 0x38, 0x00, 0x00}, SZ_SE , "se_neg r24"},
	{{0x00, 0x84, 0x00, 0x00}, SZ_SE , "se_mflr r4"},
	{{0x00, 0x9F, 0x00, 0x00}, SZ_SE , "se_mtlr r31"},
	{{0x00, 0xA3, 0x00, 0x00}, SZ_SE , "se_mfctr r3"},
	{{0x00, 0xB6, 0x00, 0x00}, SZ_SE , "se_mtctr r6"},
	{{0x00, 0xCE, 0x00, 0x00}, SZ_SE , "se_extzb r30"},
	{{0x00, 0xD1, 0x00, 0x00}, SZ_SE , "se_extsb r1"},
	{{0x00, 0xE8, 0x00, 0x00}, SZ_SE , "se_extzh r24"},
	{{0x00, 0xF2, 0x00, 0x00}, SZ_SE , "se_extsh r2"},
	{{0x01, 0x0F, 0x00, 0x00}, SZ_SE , "se_mr r31 r0"},
	{{0x02, 0x2F, 0x00, 0x00}, SZ_SE , "se_mtar r23 r2"},
	{{0x03, 0x07, 0x00, 0x00}, SZ_SE , "se_mfar r7 r24"},
	{{0x04, 0x7F, 0x00, 0x00}, SZ_SE , "se_add r31 r7"},
	{{0x05, 0x43, 0x00, 0x00}, SZ_SE , "se_mullw r3 r4"},
	{{0x06, 0x21, 0x00, 0x00}, SZ_SE , "se_sub r1 r2"},
	{{0x07, 0xAD, 0x00, 0x00}, SZ_SE , "se_subf r29 r26"},
	{{0x0C, 0x10, 0x00, 0x00}, SZ_SE , "se_cmp r0 r1"},
	{{0x0D, 0x76, 0x00, 0x00}, SZ_SE , "se_cmpl r6 r7"},
	{{0x0E, 0xCF, 0x00, 0x00}, SZ_SE , "se_cmph r31 r28"},
	{{0x0F, 0x91, 0x00, 0x00}, SZ_SE , "se_cmphl r1 r25"},
	{{0x21, 0xEC, 0x00, 0x00}, SZ_SE , "se_addi r28 0x1f"},
	{{0x22, 0xBC, 0x00, 0x00}, SZ_SE , "se_cmpli r28 0xc"},
	{{0x25, 0x77, 0x00, 0x00}, SZ_SE , "se_subi r7 0x18"},
	{{0x27, 0x29, 0x00, 0x00}, SZ_SE , "se_subi. r25 0x13"},
	{{0x2B, 0x63, 0x00, 0x00}, SZ_SE , "se_cmpi r3 0x16"},
	{{0x2C, 0x06, 0x00, 0x00}, SZ_SE , "se_bmaski r6 0x0"},
	{{0x2F, 0x14, 0x00, 0x00}, SZ_SE , "se_andi r4 0x11"},
	{{0x40, 0x0E, 0x00, 0x00}, SZ_SE , "se_srw r0"},
	{{0x41, 0xE6, 0x00, 0x00}, SZ_SE , "se_sraw r30"},
	{{0x42, 0x65, 0x00, 0x00}, SZ_SE , "se_slw r6"},
	{{0x44, 0x10, 0x00, 0x00}, SZ_SE , "se_or r0 r1"},
	{{0x45, 0x32, 0x00, 0x00}, SZ_SE , "se_andc r2 r3"},
	{{0x46, 0x10, 0x00, 0x00}, SZ_SE , "se_and r0 r1"},
	{{0x47, 0x01, 0x00, 0x00}, SZ_SE , "se_and. r1 r0"},
	{{0x4C, 0xF4, 0x00, 0x00}, SZ_SE , "se_li r4 0x4f"},
	{{0x61, 0x2B, 0x00, 0x00}, SZ_SE , "se_bclri r27 0x12"},
	{{0x63, 0x17, 0x00, 0x00}, SZ_SE , "se_bgeni r7 0x11"},
	{{0x64, 0x10, 0x00, 0x00}, SZ_SE , "se_bseti r0 0x1"},
	{{0x66, 0x74, 0x00, 0x00}, SZ_SE , "se_btsti r4 0x7"},
	{{0x69, 0x9D, 0x00, 0x00}, SZ_SE , "se_srwi r29 0x19"},
	{{0x6A, 0x89, 0x00, 0x00}, SZ_SE , "se_srawi r25 0x8"},
	{{0x6C, 0x77, 0x00, 0x00}, SZ_SE , "se_slwi r7 0x7"},
	{{0x88, 0x18, 0x00, 0x00}, SZ_SE , "se_lbz r1 0x8(r8)"},
	{{0x9A, 0x02, 0x00, 0x00}, SZ_SE , "se_stb r0 0xa(r2)"},
	{{0xA9, 0x84, 0x00, 0x00}, SZ_SE , "se_lbh r24 0x12(r4)"},
	{{0xB6, 0x1E, 0x00, 0x00}, SZ_SE , "se_sth r1 0xc(r14)"},
	{{0xCF, 0x60, 0x00, 0x00}, SZ_SE , "se_lwz r6 0x3c(r0)"},
	{{0xD0, 0x7D, 0x00, 0x00}, SZ_SE , "se_stw r7 0x0(r13)"},
	{{0xE7, 0x14, 0x00, 0x00}, SZ_SE , "se_bso 0x800009e"},
	{{0xE8, 0xFA, 0x00, 0x00}, SZ_SE , "se_b 0x800006c"},
	{{0xE9, 0x00, 0x00, 0x00}, SZ_SE , "se_bl 0x800007a"},
	{{0xE9, 0xC2, 0x00, 0x00}, SZ_SE , "se_bl 0x8000000"},
};

const test_t test_e_only[] = {
	{{0x18, 0x03, 0x09, 0x04}, SZ_E  , "e_stmw r0 0x4(r3)"},
	{{0x18, 0x15, 0xB2, 0x37}, SZ_E  , "e_subfic r0 r21 0x370000"},
	{{0x18, 0x37, 0x05, 0xFF}, SZ_E  , "e_sthu r1 0xffffffff(r23)"},
	{{0x18, 0x46, 0x88, 0x37}, SZ_E  , "e_addi. r2 r6 0x37"},
	{{0x18, 0x46, 0xA9, 0x37}, SZ_E  , "e_cmpi cr2 r6 0x3700"},
	{{0x18, 0x65, 0x81, 0x37}, SZ_E  , "e_addi r3 r5 0x3700"},
	{{0x18, 0x75, 0xE1, 0x37}, SZ_E  , "e_xori r21 r3 0x3700"},
	{{0x18, 0x84, 0x9A, 0x37}, SZ_E  , "e_addic. r4 r4 0x370000"},
	{{0x18, 0xA3, 0x08, 0x18}, SZ_E  , "e_lmw r5 0x18(r3)"},
	{{0x18, 0xA3, 0xAB, 0x37}, SZ_E  , "e_cmpli cr1 r3 0x37000000"},
	{{0x18, 0xC2, 0x02, 0x72}, SZ_E  , "e_lwzu r6 0x72(r2)"},
	{{0x18, 0xE0, 0x01, 0x3E}, SZ_E  , "e_lhzu r7 0x3e(r0)"},
	{{0x18, 0xE5, 0x00, 0xCC}, SZ_E  , "e_lbzu r7 0xffffffcc(r5)"},
	{{0x18, 0xE8, 0x93, 0x37}, SZ_E  , "e_addic r7 r8 0x37000000"},
	{{0x19, 0x01, 0x03, 0xFF}, SZ_E  , "e_lhau r8 0xffffffff(r1)"},
	{{0x19, 0x07, 0xD1, 0x37}, SZ_E  , "e_ori r8 r7 0x3700"},
	{{0x19, 0x27, 0xD8, 0x37}, SZ_E  , "e_ori. r9 r7 0x37"},
	{{0x19, 0x2A, 0xA0, 0x37}, SZ_E  , "e_mulli r9 r10 0x37"},
	{{0x19, 0xAB, 0xC8, 0x39}, SZ_E  , "e_andi. r11 r13 0x39"},
	{{0x19, 0xEC, 0xC2, 0x37}, SZ_E  , "e_andi r12 r15 0x370000"},
	{{0x1A, 0x76, 0x04, 0xFC}, SZ_E  , "e_stbu r19 0xfffffffc(r22)"},
	{{0x1A, 0x80, 0xE8, 0x37}, SZ_E  , "e_xori. r0 r20 0x37"},
	{{0x1A, 0xC0, 0xBB, 0x37}, SZ_E  , "e_subfic. r22 r0 0x37000000"},
	{{0x1A, 0xC4, 0x06, 0xEE}, SZ_E  , "e_stwu r22 0xffffffee(r4)"},
	{{0x1C, 0x83, 0x00, 0x1B}, SZ_E  , "e_add16i r4 r3 0x1b"},
	{{0x30, 0xE3, 0xCC, 0x0D}, SZ_E  , "e_lbz r7 0xffffcc0d(r3)"},
	{{0x34, 0x61, 0x55, 0xF0}, SZ_E  , "e_stb r3 0x55f0(r1)"},
	{{0x39, 0x0A, 0x01, 0xFF}, SZ_E  , "e_lha r8 0x1ff(r10)"},
	{{0x50, 0xA3, 0x27, 0x28}, SZ_E  , "e_lwz r5 0x2728(r3)"},
	{{0x54, 0x60, 0x3F, 0x21}, SZ_E  , "e_stw r3 0x3f21(r0)"},
	{{0x58, 0xE0, 0x18, 0x38}, SZ_E  , "e_lhz r7 0x1838(r0)"},
	{{0x5C, 0x15, 0x02, 0x9A}, SZ_E  , "e_sth r0 0x29a(r21)"},
	{{0x70, 0x01, 0xA6, 0x68}, SZ_E  , "e_mull2i r1 0x668"},
	{{0x70, 0x06, 0x1B, 0x33}, SZ_E  , "e_li r0 0x33333"},
	{{0x70, 0x26, 0xE3, 0x33}, SZ_E  , "e_lis r1 0x3333"},
	{{0x70, 0x4D, 0xBA, 0x34}, SZ_E  , "e_cmphl16i r13 0x1234"},
	{{0x70, 0xA4, 0xC3, 0x45}, SZ_E  , "e_or2i r5 0x2345"},
	{{0x70, 0xB4, 0xD3, 0x45}, SZ_E  , "e_or2is r5 0xa345"},
	{{0x70, 0xC0, 0x8C, 0x56}, SZ_E  , "e_add2i. r0 0x3456"},
	{{0x70, 0xC2, 0x9B, 0x33}, SZ_E  , "e_cmp16i r2 0x3333"},
	{{0x71, 0x01, 0x93, 0x21}, SZ_E  , "e_add2is r1 0x4321"},
	{{0x71, 0x3F, 0xCE, 0xED}, SZ_E  , "e_and2i. r9 0xfeed"},
	{{0x71, 0x40, 0xE8, 0x05}, SZ_E  , "e_and2is. r10 0x5"},
	{{0x73, 0xE1, 0xAE, 0xE0}, SZ_E  , "e_cmpl16i r1 0xfee0"},
	{{0x73, 0xEC, 0xB5, 0xEF}, SZ_E  , "e_cmph16i r12 0xfffffdef"},
	{{0x74, 0x24, 0x68, 0x63}, SZ_E  , "e_rlwinm r4 r1 0xd 0x1 0x11"},
	{{0x76, 0x64, 0x6A, 0x1E}, SZ_E  , "e_rlwimi r4 r19 0xd 0x8 0xf"},
	{{0x78, 0x00, 0x00, 0x01}, SZ_E  , "e_bl 0x0"},
	{{0x78, 0x00, 0x00, 0xEC}, SZ_E  , "e_b 0xec"},
	{{0x79, 0xFF, 0xFE, 0x67}, SZ_E  , "e_bl 0xfdfffe66"},
	{{0x79, 0xFF, 0xFF, 0x82}, SZ_E  , "e_b 0xfdffff82"},
	{{0x7A, 0x03, 0xFF, 0xCC}, SZ_E  , "e_bns cr0 0xffffffcc"},
	{{0x7A, 0x03, 0x80, 0x00}, SZ_E  , "e_bns cr0 0xffff8000"},
	{{0x7A, 0x1F, 0x00, 0x01}, SZ_E  , "e_beql cr3 0x0"},
	{{0x7C, 0x00, 0x01, 0x82}, SZ_E  , "e_crxor cr0 cr0 cr0"},
	{{0x7C, 0x02, 0xE9, 0x02}, SZ_E  , "e_crandc cr0 cr2 cr29"},
	{{0x7C, 0x06, 0x40, 0x5C}, SZ_E  , "e_cmphl cr0 r6 r8"},
	{{0x7D, 0x4C, 0xA0, 0x71}, SZ_E  , "e_slwi. r12 r10 0x14"},
	{{0x7E, 0x6C, 0x30, 0x70}, SZ_E  , "e_slwi r12 r19 0x6"},
	{{0x7C, 0x20, 0x5C, 0x71}, SZ_E  , "e_srwi. r0 r1 0xb"},
	{{0x7C, 0x20, 0x84, 0x70}, SZ_E  , "e_srwi r0 r1 0x10"},
	{{0x7C, 0x48, 0x02, 0x31}, SZ_E  , "e_rlw. r8 r2 r0"},
	{{0x7E, 0xD2, 0x02, 0x30}, SZ_E  , "e_rlw r18 r22 r0"},
	{{0x7C, 0x62, 0xAA, 0x71}, SZ_E  , "e_rlwi. r2 r3 0x15"},
	{{0x7C, 0x74, 0xAA, 0x70}, SZ_E  , "e_rlwi r20 r3 0x15"},
	{{0x7C, 0x87, 0x58, 0x1C}, SZ_E  , "e_cmph cr0 r7 r11"},
	{{0x7C, 0x98, 0x00, 0x20}, SZ_E  , "e_mcrf cr1 cr6"},
	{{0x7D, 0x8D, 0x73, 0x82}, SZ_E  , "e_cror cr12 cr13 cr14"},
	{{0x7D, 0xE0, 0x18, 0x42}, SZ_E  , "e_crnor cr15 cr0 cr3"},
	{{0x7D, 0xE0, 0x19, 0xC2}, SZ_E  , "e_crnand cr15 cr0 cr3"},
	{{0x7D, 0xF0, 0x8A, 0x42}, SZ_E  , "e_creqv cr15 cr16 cr17"},
	{{0x7E, 0x72, 0x8B, 0x42}, SZ_E  , "e_crorc cr19 cr18 cr17"},
	{{0x7F, 0xA3, 0x02, 0x02}, SZ_E  , "e_crand cr29 cr3 cr0"},
	{{0x18, 0xa3, 0x10, 0x3c}, SZ_E  , "e_ldmvcsrrw 0x3c(r3)"},
	{{0x18, 0xc3, 0x10, 0x40}, SZ_E  , "e_ldmvdsrrw 0x40(r3)"},
	{{0x18, 0x03, 0x10, 0x30}, SZ_E  , "e_ldmvgprw 0x30(r3)"},
	{{0x18, 0x23, 0x10, 0x34}, SZ_E  , "e_ldmvgprw 0x34(r3)"},
	{{0x18, 0x83, 0x10, 0x38}, SZ_E  , "e_ldmvgprw 0x38(r3)"},
	{{0x18, 0xa3, 0x11, 0x24}, SZ_E  , "e_stmvcsrrw 0x24(r3)"},
	{{0x18, 0xc3, 0x11, 0x28}, SZ_E  , "e_stmvdsrrw 0x28(r3)"},
	{{0x18, 0x03, 0x11, 0x18}, SZ_E  , "e_stmvgprw 0x18(r3)"},
	{{0x18, 0x23, 0x11, 0x2c}, SZ_E  , "e_stmvgprw 0x2c(r3)"},
	{{0x18, 0x83, 0x11, 0x1c}, SZ_E  , "e_stmvgprw 0x1c(r3)"},
	{{0x18, 0x23, 0x10, 0x20}, SZ_E  , "e_ldmvgprw 0x20(r3)"},
	{{0x18, 0x83, 0x10, 0x0c}, SZ_E  , "e_ldmvgprw 0xc(r3)"},
	{{0x18, 0xa3, 0x11, 0x10}, SZ_E  , "e_stmvcsrrw 0x10(r3)"},
	{{0x18, 0xc3, 0x11, 0x00}, SZ_E  , "e_stmvdsrrw 0x0(r3)"},
	{{0x18, 0x03, 0x11, 0x14}, SZ_E  , "e_stmvgprw 0x14(r3)"},
	{{0x18, 0x23, 0x11, 0x04}, SZ_E  , "e_stmvgprw 0x4(r3)"},
	{{0x18, 0x83, 0x11, 0x08}, SZ_E  , "e_stmvgprw 0x8(r3)"},
};

const test_t test_powerpc_only[] = {
	{{0x7C, 0x12, 0x30, 0x50}, SZ_PPC, "subf r0 r18 r6"},
	{{0x7C, 0x12, 0x30, 0x51}, SZ_PPC, "subf. r0 r18 r6"},
	{{0x7C, 0x12, 0x34, 0x50}, SZ_PPC, "subfo r0 r18 r6"},
	{{0x7C, 0x12, 0x34, 0x51}, SZ_PPC, "subfo. r0 r18 r6"},
	{{0x7C, 0x12, 0x30, 0x10}, SZ_PPC, "subfc r0 r18 r6"},
	{{0x7C, 0x12, 0x30, 0x11}, SZ_PPC, "subfc. r0 r18 r6"},
	{{0x7C, 0x12, 0x34, 0x10}, SZ_PPC, "subfco r0 r18 r6"},
	{{0x7C, 0x12, 0x34, 0x11}, SZ_PPC, "subfco. r0 r18 r6"},
	{{0x7C, 0x12, 0x31, 0x10}, SZ_PPC, "subfe r0 r18 r6"},
	{{0x7C, 0x12, 0x31, 0x11}, SZ_PPC, "subfe. r0 r18 r6"},
	{{0x7C, 0x12, 0x35, 0x10}, SZ_PPC, "subfeo r0 r18 r6"},
	{{0x7C, 0x12, 0x35, 0x11}, SZ_PPC, "subfeo. r0 r18 r6"},
	{{0x7C, 0x62, 0x00, 0xD0}, SZ_PPC, "neg r3 r2"},
	{{0x7C, 0x62, 0x00, 0xD1}, SZ_PPC, "neg. r3 r2"},
	{{0x7C, 0x62, 0x04, 0xD0}, SZ_PPC, "nego r3 r2"},
	{{0x7C, 0x62, 0x04, 0xD1}, SZ_PPC, "nego. r3 r2"},
	{{0x7C, 0x60, 0x01, 0x06}, SZ_PPC, "wrtee r3"},
	{{0x7C, 0x00, 0x81, 0x46}, SZ_PPC, "wrteei 0x1"},
	{{0x7C, 0x00, 0x01, 0x46}, SZ_PPC, "wrteei 0x0"},
	{{0x7C, 0x62, 0x60, 0x96}, SZ_PPC, "mulhw r3 r2 r12"},
	{{0x7C, 0x62, 0x60, 0x97}, SZ_PPC, "mulhw. r3 r2 r12"},
	{{0x7C, 0x62, 0x60, 0x16}, SZ_PPC, "mulhwu r3 r2 r12"},
	{{0x7C, 0x62, 0x60, 0x17}, SZ_PPC, "mulhwu. r3 r2 r12"},
	{{0x7C, 0x62, 0x60, 0xAE}, SZ_PPC, "lbzx r3 r2 r12"},
	{{0x7C, 0x62, 0x60, 0xEE}, SZ_PPC, "lbzux r3 r2 r12"},
	{{0x7C, 0x62, 0x61, 0xEE}, SZ_PPC, "stbux r3 r2 r12"},
	{{0x7C, 0x62, 0x63, 0x2E}, SZ_PPC, "sthx r3 r2 r12"},
	{{0x7C, 0x62, 0x63, 0x6E}, SZ_PPC, "sthux r3 r2 r12"},
	{{0x7C, 0x62, 0x60, 0x30}, SZ_PPC, "slw r3 r2 r12"},
	{{0x7C, 0x62, 0x60, 0x31}, SZ_PPC, "slw. r3 r2 r12"},
	{{0x7C, 0x62, 0x64, 0x30}, SZ_PPC, "srw r3 r2 r12"},
	{{0x7C, 0x62, 0x64, 0x31}, SZ_PPC, "srw. r3 r2 r12"},
	{{0x7C, 0x62, 0x66, 0x30}, SZ_PPC, "sraw r3 r2 r12"},
	{{0x7C, 0x62, 0x66, 0x31}, SZ_PPC, "sraw. r3 r2 r12"},
	{{0x7C, 0x62, 0x66, 0x70}, SZ_PPC, "srawi r3 r2 r12"},
	{{0x7C, 0x62, 0x66, 0x71}, SZ_PPC, "srawi. r3 r2 r12"},
};

const test_t test_gh_issues[] = {
	/* VLE SE related */
	{{0x00, 0x04, 0x00, 0x00}, SZ_SE , "se_blr"},
	{{0x00, 0x04, 0x00, 0x00}, SZ_SE , "se_blr"},
	{{0x00, 0x80, 0x00, 0x00}, SZ_SE , "se_mflr r0"},
	{{0x00, 0x90, 0x00, 0x00}, SZ_SE , "se_mtlr r0"},
	{{0x00, 0xD3, 0x00, 0x00}, SZ_SE , "se_extsb r3"},
	{{0x02, 0x78, 0x00, 0x00}, SZ_SE , "se_mtar r16 r7"},
	{{0x20, 0xF1, 0x00, 0x00}, SZ_SE , "se_addi r1 0x10"},
	{{0x25, 0x77, 0x00, 0x00}, SZ_SE , "se_subi r7 0x18"},
	{{0x27, 0x77, 0x00, 0x00}, SZ_SE , "se_subi. r7 0x18"},
	{{0x2D, 0x07, 0x00, 0x00}, SZ_SE , "se_bmaski r7 0x10"},
	{{0x44, 0x30, 0x00, 0x00}, SZ_SE , "se_or r0 r3"},
	{{0x44, 0x30, 0x00, 0x00}, SZ_SE , "se_or r0 r3"},
	{{0x44, 0x70, 0x00, 0x00}, SZ_SE , "se_or r0 r7"},
	{{0x63, 0x17, 0x00, 0x00}, SZ_SE , "se_bgeni r7 0x11"},
	{{0x66, 0x40, 0x00, 0x00}, SZ_SE , "se_btsti r0 0x4"},
	{{0x6D, 0xC3, 0x00, 0x00}, SZ_SE , "se_slwi r3 0x1c"},
	{{0xC0, 0x06, 0x00, 0x00}, SZ_SE , "se_lwz r0 0x0(r6)"},
	{{0xC5, 0x01, 0x00, 0x00}, SZ_SE , "se_lwz r0 0x14(r1)"},
	{{0xD1, 0x06, 0x00, 0x00}, SZ_SE , "se_stw r0 0x4(r6)"},
	{{0xD1, 0x06, 0x00, 0x00}, SZ_SE , "se_stw r0 0x4(r6)"},
	{{0xD5, 0x01, 0x00, 0x00}, SZ_SE , "se_stw r0 0x14(r1)"},
	{{0xE2, 0xFE, 0x00, 0x00}, SZ_SE , "se_bne 0x8000026"},
	/* VLE E related */
	{{0x18, 0x21, 0x06, 0xF0}, SZ_E  , "e_stwu r1 0xfffffff0(r1)"},
	{{0x1C, 0xC3, 0xFF, 0xFF}, SZ_E  , "e_add16i r6 r3 0xffffffff"},
	{{0x1C, 0xC6, 0xC0, 0x00}, SZ_E  , "e_add16i r6 r6 0xffffc000"},
	{{0x1D, 0x81, 0x00, 0x10}, SZ_E  , "e_add16i r12 r1 0x10"},
	{{0x1F, 0xFF, 0x58, 0x00}, SZ_E  , "e_add16i r31 r31 0x5800"},
	{{0x51, 0xE3, 0x27, 0x28}, SZ_E  , "e_lwz r15 0x2728(r3)"},
	{{0x52, 0x03, 0x27, 0x28}, SZ_E  , "e_lwz r16 0x2728(r3)"},
	{{0x55, 0xCB, 0xFF, 0xB8}, SZ_E  , "e_stw r14 0xffffffb8(r11)"},
	{{0x55, 0xEB, 0xFF, 0xBC}, SZ_E  , "e_stw r15 0xffffffbc(r11)"},
	{{0x56, 0x0B, 0xFF, 0xC0}, SZ_E  , "e_stw r16 0xffffffc0(r11)"},
	{{0x56, 0x2B, 0xFF, 0xC4}, SZ_E  , "e_stw r17 0xffffffc4(r11)"},
	{{0x56, 0x4B, 0xFF, 0xC8}, SZ_E  , "e_stw r18 0xffffffc8(r11)"},
	{{0x56, 0x6B, 0xFF, 0xCC}, SZ_E  , "e_stw r19 0xffffffcc(r11)"},
	{{0x56, 0x8B, 0xFF, 0xD0}, SZ_E  , "e_stw r20 0xffffffd0(r11)"},
	{{0x56, 0xAB, 0xFF, 0xD4}, SZ_E  , "e_stw r21 0xffffffd4(r11)"},
	{{0x56, 0xCB, 0xFF, 0xD8}, SZ_E  , "e_stw r22 0xffffffd8(r11)"},
	{{0x56, 0xEB, 0xFF, 0xDC}, SZ_E  , "e_stw r23 0xffffffdc(r11)"},
	{{0x57, 0x0B, 0xFF, 0xE0}, SZ_E  , "e_stw r24 0xffffffe0(r11)"},
	{{0x57, 0x2B, 0xFF, 0xE4}, SZ_E  , "e_stw r25 0xffffffe4(r11)"},
	{{0x57, 0x4B, 0xFF, 0xE8}, SZ_E  , "e_stw r26 0xffffffe8(r11)"},
	{{0x57, 0x6B, 0xFF, 0xEC}, SZ_E  , "e_stw r27 0xffffffec(r11)"},
	{{0x57, 0x8B, 0xFF, 0xF0}, SZ_E  , "e_stw r28 0xfffffff0(r11)"},
	{{0x57, 0xAB, 0xFF, 0xF4}, SZ_E  , "e_stw r29 0xfffffff4(r11)"},
	{{0x57, 0xCB, 0xFF, 0xF8}, SZ_E  , "e_stw r30 0xfffffff8(r11)"},
	{{0x57, 0xEB, 0xFF, 0xFC}, SZ_E  , "e_stw r31 0xfffffffc(r11)"},
	{{0x70, 0x0B, 0x02, 0xF0}, SZ_E  , "e_li r0 0x5af0"},
	{{0x70, 0xD8, 0xE3, 0xFE}, SZ_E  , "e_lis r6 0xc3fe"},
	{{0x79, 0xFF, 0xAF, 0x09}, SZ_E  , "e_bl 0xfdffaf08"},
	{{0x7A, 0x20, 0xFF, 0xF8}, SZ_E  , "e_bdnz 0xfffffff8"},
	{{0x7A, 0x20, 0xFF, 0xF9}, SZ_E  , "e_bdnzl 0xfffffff8"},
	{{0x7A, 0x30, 0xFF, 0xF8}, SZ_E  , "e_bdz 0xfffffff8"},
	{{0x7A, 0x30, 0xFF, 0xF9}, SZ_E  , "e_bdzl 0xfffffff8"},
	/* PowerPC related */
	{{0x7C, 0x00, 0x04, 0xAC}, SZ_PPC, "msync"},
	{{0x7C, 0x00, 0x07, 0x64}, SZ_PPC, "tlbre"},
	{{0x7C, 0x00, 0x07, 0xA4}, SZ_PPC, "tlbwe"},
	{{0x7C, 0x00, 0x23, 0xB8}, SZ_PPC, "nand r0 r0 r4"},
	{{0x7C, 0x00, 0x23, 0xB9}, SZ_PPC, "nand. r0 r0 r4"},
	{{0x7C, 0x07, 0xD8, 0xEE}, SZ_PPC, "lbzux r0 r7 r27"},
	{{0x7C, 0x60, 0x82, 0xA6}, SZ_PPC, "mfspr r3 0x10"},
	{{0x7C, 0x60, 0x83, 0xA6}, SZ_PPC, "mtspr 0x10 r3"},
	{{0x7C, 0x64, 0x29, 0x2E}, SZ_PPC, "stwx r3 r4 r5"},
	{{0x7C, 0x80, 0x00, 0xA6}, SZ_PPC, "mfmsr r4"},
	{{0x7C, 0x80, 0x01, 0x24}, SZ_PPC, "mtmsr r4"},
	{{0x7C, 0xA0, 0x00, 0x26}, SZ_PPC, "mfcr r5"},
	{{0x7C, 0x00, 0x20, 0xF8}, SZ_PPC, "nor r0 r0 r4"},
	{{0x7C, 0x64, 0x18, 0xF8}, SZ_PPC, "nor r4 r3 r3"},
	{{0x7C, 0xC0, 0x20, 0xF8}, SZ_PPC, "nor r0 r6 r4"},
	{{0x7C, 0xC0, 0x20, 0xF9}, SZ_PPC, "nor. r0 r6 r4"},
	{{0x7C, 0x00, 0x20, 0xF9}, SZ_PPC, "nor. r0 r0 r4"},
	{{0x7C, 0xC0, 0x23, 0x78}, SZ_PPC, "or r0 r6 r4"},
	{{0x7C, 0xC0, 0x23, 0x79}, SZ_PPC, "or. r0 r6 r4"},
	{{0x7C, 0x00, 0x22, 0x78}, SZ_PPC, "xor r0 r0 r4"},
	{{0x7C, 0x00, 0x22, 0x79}, SZ_PPC, "xor. r0 r0 r4"},
	{{0x7D, 0x28, 0x01, 0x2E}, SZ_PPC, "stwx r9 r8 r0"},
};

int test_decoding(const char* name, const test_t* tests, const uint32_t n_tests) {
	fprintf (stderr, "Test: %s\n", name);
	vle_t* instr;
	int ok = 0;
	char tmp[256];
	uint32_t addr = 0x08000000;
	for (uint32_t i = 0; i < n_tests; ++i) {
		if ((instr = vle_decode_one(tests[i].bytes, tests[i].size))) {
			vle_snprint(tmp, 256, addr, instr);
			if (strcmp(tmp, tests[i].expected)) {
				ok = 1;
				if(instr->size == 2){
					fprintf (stderr, "[fail] %02X %02X       [%08x]  %s (expected %s)\n",
						tests[i].bytes[0], tests[i].bytes[1],
						addr, tmp, tests[i].expected);
				} else {
					fprintf (stderr, "[fail] %02X %02X %02X %02X [%08x]  %s (expected %s)\n",
						tests[i].bytes[0], tests[i].bytes[1], tests[i].bytes[2], tests[i].bytes[3],
						addr, tmp, tests[i].expected);
				}
			} else {
				if(instr->size == 2){
					printf ("[ ok ] %02X %02X       [%08x]  %s\n",
						tests[i].bytes[0], tests[i].bytes[1],
						addr, tmp);
				} else {
					printf ("[ ok ] %02X %02X %02X %02X [%08x]  %s\n",
						tests[i].bytes[0], tests[i].bytes[1], tests[i].bytes[2], tests[i].bytes[3],
						addr, tmp);
				}
			}
			addr += instr->size;
			vle_free(instr);
		} else {
			if(tests[i].size == 2) {
				fprintf (stderr, "[null] %02X %02X         [%08x]  %s\n",
					tests[i].bytes[0], tests[i].bytes[1],
					addr, tests[i].expected);
			} else {
				fprintf (stderr, "[null] %02X %02X %02X %02X [%08x]  %s\n",
					tests[i].bytes[0], tests[i].bytes[1], tests[i].bytes[2], tests[i].bytes[3],
					addr, tests[i].expected);
			}
			ok = 1;
			addr += tests[i].size;
		}
	};
	return ok;
}

#define TEST(name, retval) \
 if (test_decoding(#name , name, (sizeof(name) / sizeof(test_t)))) (retval) = 1

int main(int argc, char const *argv[]) {
	int ok = 0;
	TEST(test_se_only, ok);
	TEST(test_e_only, ok);
	TEST(test_powerpc_only, ok);
	TEST(test_gh_issues, ok);
	return ok;
}
