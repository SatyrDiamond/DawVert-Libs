// code from https://github.com/zamaudio/ptformat

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

uint8_t gen_xor_delta(uint8_t xor_value, uint8_t mul, bool negative) {
	uint16_t i;
	for (i = 0; i < 256; i++) {
		if (((i * mul) & 0xff) == xor_value) {
				return (negative) ? i * (-1) : i;
		}
	}
	// Should not occur
	return 0;
}

int unxor(uint8_t *finput, uint8_t *foutput, long file_len) {
	unsigned char xxor[256];
	uint64_t i;
	uint8_t xor_type;
	uint8_t xor_value;
	uint8_t xor_delta;
	uint16_t xor_len;
	uint8_t xor_index;

	xor_type = finput[0x12];
	xor_value = finput[0x13];
	xor_len = 256;

	// xor_type 0x01 = ProTools 5, 6, 7, 8 and 9
	// xor_type 0x05 = ProTools 10, 11, 12
	switch(xor_type) {
	case 0x01:
		xor_delta = gen_xor_delta(xor_value, 53, false);
		break;
	case 0x05:
		xor_delta = gen_xor_delta(xor_value, 11, true);
		break;
	default:
		return -4;
	}

	/* Generate the xor_key */
	for (i=0; i < xor_len; i++)
		xxor[i] = (i * xor_delta) & 0xff;

	/* hexdump(xxor, xor_len); */

	/* Read file and decrypt rest of file */

	long curpos;
	curpos = 0;
	while (curpos != 0x14) {
		foutput[curpos] = finput[curpos];
		curpos++;
	}

	unsigned char ct;
	curpos = 0x14;
	while (curpos != file_len) {
		ct = finput[curpos];
		xor_index = (xor_type == 0x01) ? curpos & 0xff : (curpos >> 12) & 0xff;
		foutput[curpos] = ct ^ xxor[xor_index];
		curpos++;
	}

	return curpos;
}
