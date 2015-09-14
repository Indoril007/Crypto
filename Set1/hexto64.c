#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef NDEBUG
#  include <assert.h>
#else               /* debugging not enabled */
#  define assert(x) /* empty macro to prevent errors */
#endif

// Convert a byte to its ASCII Base64 representation
uint8_t Base64_ASCII(uint8_t val) {
	assert(val <= 63);

	if (val <= 25) {
		return (val + 65);
	} else if (val <= 51) {
		return (val + 71);
	} else if (val < 62) {
		return (val - 4);
	} else if (val == 62) {
		return 43;
	} else {
		return 47;
	}
	
	return -1;
}

// Convert hex represented in ASCII to its actual value 
uint8_t ASCII_Hex(uint8_t val) {
	// check that value passed is a valid hexadecimal character
	assert((val >= 48) && (val <= 57) || (val >= 65 && val <= 70) || (val >= 97 && val <= 102));
	
	uint8_t out;
	
	if((val >= 48) && (val <= 57)) {
		return (val - 48);
	} else if ((val >= 65 && val <= 70)) {
		return (val - 55);
	} else {
		return (val - 87);
	}
	
	return -1;
}

//Convert hex values to the same values in Base64
uint8_t *Hex_Base64(uint8_t *input, uint32_t size){
	assert((size % 3) == 0); // Must be divisible by three to convert to Base64. Pad input if necessary.
	
	uint32_t i = 0;
	uint32_t j = 0;
	uint8_t *output;
	output = (uint8_t *) malloc((size / 3) * 2);
	
	while (i < (size - 2)) {
		output[j++] = (input[i] << 2) | (input[i+1] >> 2);
		output[j++] = ((input[i+1] << 4) | input[i+2]) & 63;
		i += 3;
	}
	
	return output;	
	
}

int main(int argc, char *argv[]) {
	char *hexString;
	hexString = "49276db3a2";
	uint8_t size = strlen(hexString);
	uint8_t padding = (size % 3);
	uint8_t *input, *output, i;
	input = (uint8_t *) malloc(size + (padding * 2));
	
	for(i = 0; i < size; i++) {
		*(input + i) = ASCII_Hex(*(hexString + i));
		printf("%d ", *(input + i));
	}
	for(i = size; i < (size + (padding * 2)); i++) {
		*(input + i) = 0;
	}
	
	
	printf("\n");
	
	output = Hex_Base64(input, size + padding * 2);
	for(i = 0; i < ((((size + padding * 2) / 3) * 2) - padding); i++) {
		printf("%c", Base64_ASCII(*(output + i)));
	}
	for (i = 0; i < padding; i++){
		printf("=");
	}
	
	printf("\n");
}	