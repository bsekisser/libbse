#pragma once

/* **** */

#include "alubox_fu_shifter.h"
#include "alubox_fu_s_parts.h"

/* **** */

#include "log.h"

/* **** */

enum {
	ALUBOX_ADC,
	ALUBOX_ADD,
	ALUBOX_AND,
	ALUBOX_ASR,
	ALUBOX_BIC,
	ALUBOX_EOR,
	ALUBOX_LSL,
	ALUBOX_LSR,
	ALUBOX_MAC,
	ALUBOX_MOD,
	ALUBOX_MOV,
	ALUBOX_MUL,
	ALUBOX_MUL_ACC,
	ALUBOX_MVN,
	ALUBOX_ORR,
	ALUBOX_ROR,
	ALUBOX_RRX,
	ALUBOX_RSB,
	ALUBOX_RSC,
	ALUBOX_SBC,
	ALUBOX_SUB,
//
	ALUBOX_BCLR,
	ALUBOX_BEXT,
	ALUBOX_BSET,
	ALUBOX_BTST,
	ALUBOX_BXOR,
//
	ALUBOX_S = 0x40,
	ALUBOX_WBx = 0x80,
//
	ALUBOX_CMN = ALUBOX_WBx | ALUBOX_S | ALUBOX_ADD,
	ALUBOX_CMP = ALUBOX_WBx | ALUBOX_S | ALUBOX_SUB,
	ALUBOX_TEQ = ALUBOX_WBx | ALUBOX_S | ALUBOX_AND,
	ALUBOX_TST = ALUBOX_WBx | ALUBOX_S | ALUBOX_EOR,
};

extern inline unsigned alubox(alubox_ref alu, const unsigned op, const unsigned s1, const unsigned s2)
{
	switch(op & 0x1f) {
	case ALUBOX_ADC:
		return(__alubox_fu_s_adc(alu, s1, s2));
	case ALUBOX_ADD:
		return(__alubox_fu_s_add(alu, s1, s2));
	case ALUBOX_AND:
		return(__alubox_fu_s_and(alu, s1, s2));
	case ALUBOX_ASR:
		return(__alubox_fu_s_asr(alu, s1, s2));
	case ALUBOX_BCLR:
		return(__alubox_fu_s_bclr(alu, s1, s2));
	case ALUBOX_BEXT:
		return(__alubox_fu_s_bext(alu, s1, s2));
	case ALUBOX_BIC:
		return(__alubox_fu_s_bic(alu, s1, s2));
	case ALUBOX_BSET:
		return(__alubox_fu_s_bset(alu, s1, s2));
	case ALUBOX_BTST:
		return(__alubox_fu_s_btst(alu, s1, s2));
	case ALUBOX_BXOR:
		return(__alubox_fu_s_bxor(alu, s1, s2));
	case ALUBOX_CMN:
		return(__alubox_fu_s_cmn(alu, s1, s2));
	case ALUBOX_CMP:
		return(__alubox_fu_s_cmp(alu, s1, s2));
	case ALUBOX_EOR:
		return(__alubox_fu_s_eor(alu, s1, s2));
	case ALUBOX_LSL:
		return(__alubox_fu_s_lsl(alu, s1, s2));
	case ALUBOX_LSR:
		return(__alubox_fu_s_lsr(alu, s1, s2));
	case ALUBOX_MOD:
		return(__alubox_fu_s_mod(alu, s1, s2));
	case ALUBOX_MOV:
		return(__alubox_fu_s_mov(alu, s1, s2));
	case ALUBOX_MUL:
		return(__alubox_fu_s_mul(alu, s1, s2));
	case ALUBOX_MUL_ACC:
		return(__alubox_fu_s_mul_acc(alu, s1, s2));
	case ALUBOX_MVN:
		return(__alubox_fu_s_mvn(alu, s1, s2));
	case ALUBOX_ORR:
		return(__alubox_fu_s_orr(alu, s1, s2));
	case ALUBOX_ROR:
		return(__alubox_fu_s_ror(alu, s1, s2));
	case ALUBOX_RRX:
		return(__alubox_fu_s_rrx(alu, s1, s2));
	case ALUBOX_RSB:
		return(__alubox_fu_s_rsb(alu, s1, s2));
	case ALUBOX_RSC:
		return(__alubox_fu_s_rsc(alu, s1, s2));
	case ALUBOX_SBC:
		return(__alubox_fu_s_sbc(alu, s1, s2));
	case ALUBOX_SUB:
		return(__alubox_fu_s_sub(alu, s1, s2));
	case ALUBOX_TEQ:
		return(__alubox_fu_s_teq(alu, s1, s2));
	case ALUBOX_TST:
		return(__alubox_fu_s_tst(alu, s1, s2));
	default:
		LOG("op = 0x%02x", op);
		LOG_ACTION(exit(-1));
	}

	return(0xdeadbeef);
}
