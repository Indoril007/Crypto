#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef NDEBUG
#  include <assert.h>
#else               /* debugging not enabled */
#  define assert(x) /* empty macro to prevent errors */
#endif

// Convert a Base64 value to its ASCII Base64 representation
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

char Hex_ASCII(uint8_t val) {
	assert(val < 16);
	if (val < 10) {
		return val + 48;
	} else if (val < 16) {
		return val + 87;
	}
	
	return -1;
}

// combine two hex values into a single byte
uint8_t Hex_combine(uint8_t ms4b, uint8_t ls4b) {
	assert(ms4b < 16 && ls4b < 16);
	return (ms4b << 4) | ls4b;
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

// String formatting and padding performed before converting from ASCII -> hex -> base64 -> ASCII
char *String_Hex_Base64(char *hexString) {
	char *outString;
	size_t size = strlen(hexString);
	size_t i;
	uint8_t padding = (size % 3);
	uint8_t *input, *output;
	input = (uint8_t *) malloc(size + (padding * 2));
	outString = (char *) malloc((((size + (padding * 2)) / 3) * 2) + 1);
	
	for(i = 0; i < size; i++) {
		*(input + i) = ASCII_Hex(*(hexString + i));
	}
	for(i = size; i < (size + (padding * 2)); i++) {
		*(input + i) = 0;
	}
	
	output = Hex_Base64(input, size + padding * 2);
	for(i = 0; i < ((((size + padding * 2) / 3) * 2) - padding); i++) {
		*(outString + i) = Base64_ASCII(*(output + i));
	}
	for ( ; i < (((size + padding * 2) / 3) * 2); i++){
		*(outString + i) = '=';
	}
	
	*(outString + i) = '\0';
	
	return outString;
}	

char *XOR_Hex_String(char *A, char *B) {
	assert(strlen(A) == strlen(B));
	size_t len = strlen(A);
	size_t i;
	char *output;
	output = (char *) malloc(len + 1);
	
	for(i = 0; i < len; i++) {
		*(output + i) = Hex_ASCII(ASCII_Hex(*(A + i)) ^ ASCII_Hex(*(B + i)));
	}
	*(output + i) = '\0';
	
	return output;
}