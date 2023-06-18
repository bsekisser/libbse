#pragma once

/* **** */

#include "bitfield.h"
#include "log.h"
#include "shift_roll.h"

/* **** */

#include <stdlib.h>

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
	ALUBOX_MOD,
	ALUBOX_MOV,
	ALUBOX_MUL,
	ALUBOX_MVN,
	ALUBOX_ORR,
	ALUBOX_ROR,
	ALUBOX_RSB,
	ALUBOX_RSC,
	ALUBOX_SBC,
	ALUBOX_SUB,
//
	ALUBOX_BCLR,
	ALUBOX_BEXT,
	ALUBOX_BSET,
	ALUBOX_BTST,
//
	ALUBOX_WB = 0x80,
	ALUBOX_CMN = ALUBOX_WB | ALUBOX_ADD,
	ALUBOX_CMP = ALUBOX_WB | ALUBOX_SUB,
	ALUBOX_TEQ = ALUBOX_WB | ALUBOX_EOR,
	ALUBOX_TST = ALUBOX_WB | ALUBOX_AND,
};

static inline unsigned alubox(unsigned* rd, unsigned op, unsigned s1, unsigned s2)
{
	unsigned result = 0;
	unsigned wb = op ^ ALUBOX_WB;

	switch(op & 0x1f) {
	case ALUBOX_ADC:
	case ALUBOX_ADD:
	case ALUBOX_CMN:
		result = s1 + s2;
		break;
	case ALUBOX_AND:
	case ALUBOX_TST:
		result = s1 & s2;
		break;
	case ALUBOX_ASR:
		result = _asr(s1, s2 & 0xff);
		break;
	case ALUBOX_BCLR:
		result = _BCLR(s1, s2);
		break;
	case ALUBOX_BEXT:
		result = BEXT(s1, s2);
		break;
	case ALUBOX_BIC:
		result = s1 & ~s2;
		break;
	case ALUBOX_BSET:
		result = _BSET(s1, s2);
		break;
	case ALUBOX_BTST:
		result = BTST(s1, s2);
		break;
	case ALUBOX_CMP:
	case ALUBOX_SBC:
	case ALUBOX_SUB:
		result = s1 - s2;
		break;
	case ALUBOX_EOR:
	case ALUBOX_TEQ:
		result = s1 ^ s2;
		break;
	case ALUBOX_LSL:
		result = _lsl(s1, s2 & 0xff);
		break;
	case ALUBOX_LSR:
		result = _lsr(s1, s2 & 0xff);
		break;
	case ALUBOX_MOD:
		result = s1 % s2;
		break;
	case ALUBOX_MOV:
		result = s2;
		break;
	case ALUBOX_MUL:
		result = s1 * s2;
		break;
	case ALUBOX_MVN:
		result = -s2;
		break;
	case ALUBOX_ORR:
		result = s1 | s2;
		break;
	case ALUBOX_RSB:
	case ALUBOX_RSC:
		result = s2 - s1;
		break;
	case ALUBOX_ROR:
		result = _ror(s1, s2);
		break;
	default:
		LOG("op = 0x%02x", op);
		LOG_ACTION(exit(-1));
	}

	if(rd)
		*rd = result;

	return(wb);
}
