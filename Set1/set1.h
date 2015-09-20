#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef NDEBUG
#  include <assert.h>
#else               /* debugging not enabled */
#  define assert(x) /* empty macro to prevent errors */
#endif

/*****************************************************************************************************************
* CHAR CHECK FUNCTIONS:
* isLowAlpha		-> Is the character a lower case letter?
* isCapAlpha		-> Is the character a capital letter?
* isAlpha			-> Is the character a letter?	
* isNum				-> Is the character a number?
* isAlphaNum		-> Is the character a number or a letter?
*
* CONVERSION FUNCTIONS:
* ASCII_Hex 		-> A single ASCII hex representative character to a hex value
* Hex_ASCII 		-> A single Hex value to its correct ASCII character representation
* Hex_Combine		-> Two hex values combined into a single byte
* Byte_HighHex		-> Take Hex value from most significant 4 bits of a byte
* Byte_LowHex		-> Take Hex value from least significant 4 bits of a byte
* ASCII_HexByte 	-> Two ASCII hex representative characters to a single byte
* Byte_HighHexASCII	-> Get the ASCII representation of the Hex value of the most significant 4 bits of a byte
* Byte_LowHexASCII	-> Get the ASCII representation of the Hex value of the least significant 4 bits of a byte
* ASCII_Hex_ByteStream
* ASCII_Base64		-> Convert ASCII into Base 64
* Base64_ASCII		-> Convert Base64 into ASCII
* Hex_Base64		-> Convert Hex to Base64
* Base64_Hex		-> Convert Base64 to Hex
* Hex_HighBase64	-> Take the most significant 6 bits of three hex values and return the Base64 value
* Hex_LowBase64		-> Take the least significant 6 bits of three hex values and return the Base64 value
* Byte_HighBase64	-> Take the most significant 6 bits of 3 bytes and return the Base64 value
* Byte_HighMidBase64-> Take the second most significant 6 bits of 3 bytes and return the Base64 value
* Byte_LowMidBase64	-> Take the second least significant 6 bits of 3 bytes and return the Base64 value 
* Byte_LowBase64	-> Take the least significant 6 bits of 3 bytes and return the Base64 value
* Base64_HighByte	->
* Base64_MidByte	->
* Base64_LowByte	->
******************************************************************************************************************/

// Is the character a lower case letter?
bool isLowAlpha(char val) {
	return ((val >= 97 && val <= 122));
}

// Is the character a capital letter?
bool isCapAlpha(char val) {
	return ((val >= 65 && val <= 90));
}

// Is the character a letter?	
bool isAlpha(char val) {
	return (isLowAlpha(val) || isCapAlpha(val));
}

// Is the character a number?
bool isNum(char val) {
	return ((val >= 48 && val <= 57));
}

// Is the character a number or a letter?
bool isAlphaNum(char val) {
	return (isAlpha(val) || isNum(val));
}

// A single ASCII hex representative character to a hex value
uint8_t ASCII_Hex(char val) {
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

// A single Hex value to its correct ASCII character representation
char Hex_ASCII(uint8_t val) {
	assert(val < 16);
	if (val < 10) {
		return val + 48;
	} else if (val < 16) {
		return val + 87;
	}
	
	return -1;
}

// Two hex values combined into a single byte
uint8_t Hex_combine(uint8_t A, uint8_t B) {
	assert(A < 16 && B < 16);
	return (A << 4) | B;
}

// Take Hex value from most significant 4 bits of a byte
uint8_t Byte_HighHex(uint8_t val) {
	return val >> 4;
}

// Take Hex value from least significant 4 bits of a byte
uint8_t Byte_LowHex(uint8_t val) {
	return val & 15;
}

// Two ASCII hex representative characters to a single byte
uint8_t ASCII_HexByte(char A, char B) {
	return Hex_combine(ASCII_Hex(A), ASCII_Hex(B));
}

// Get the ASCII representation of the Hex value of the most significant 4 bits
char Byte_HighHexASCII(uint8_t val){
	return Hex_ASCII(Byte_HighHex(val));
}

// Get the ASCII representation of the Hex value of the least significant 4 bits
char Byte_LowHexASCII(uint8_t val){
	return Hex_ASCII(Byte_LowHex(val));
}

uint8_t *ASCII_Hex_ByteStream(char *input, size_t size) {
	assert(size % 2 == 0);
	size = size / 2;
	uint8_t *output = (uint8_t *) malloc(size);
	size_t i;
	size_t j = 0;
	
	for(i = 0; i < size; i++) {
		*(output + i) = ASCII_HexByte(*(input + j), *(input + j + 1));
		j+=2;
	}
	
	return output;
}

// Convert ASCII into Base 64
uint8_t ASCII_Base64(char val) {
	assert(((val >= 65) && (val <=90)) || ((val >= 97) && (val <=122)) || ((val >= 48) && (val <= 57)) || (val == 43) || (val == 47));
	
	if (val >= 65 && val <=90) {
		return val - 65;
	} else if (val >=97 && val <= 122) {
		return val - 71;
	} else if (val >= 48 && val <= 57) {
		return val + 4;
	} else if (val == 43) {
		return 62;
	} else if (val == 47) {
		return 63;
	}
	
	return -1;
}

// Convert Base64 into ASCII
char Base64_ASCII(uint8_t val) {
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

// Take the most significant 6 bits of three hex values and return the Base64 value
uint8_t Hex_HighBase64(uint8_t A, uint8_t B) {
	assert(A < 16 && B < 16);
	return (A << 2) | (B >> 2);
}

// Take the least significant 6 bits of three hex values and return the Base64 value
uint8_t Hex_LowBase64(uint8_t B, uint8_t C) {
	assert(B < 16 && C < 16);
	return ((B << 4) | C) & 63;
}

// Take the most significant 6 bits of 3 bytes and return the Base64 value
uint8_t Byte_HighBase64(uint8_t A) {
	return (A >> 2);
}

// Take the second most significant 6 bits of 3 bytes and return the Base64 value
uint8_t Byte_HighMidBase64(uint8_t A, uint8_t B) {
	return ((A << 4) | (B >> 4)) & 63;
}

// Take the second least significant 6 bits of 3 bytes and return the Base64 value
uint8_t Byte_LowMidBase64(uint8_t B, uint8_t C) {
	return ((B << 2) | (C >> 6) & 63);
}

// Take the least significant 6 bits of 3 bytes and return the Base64 value
uint8_t Byte_LowBase65(uint8_t C) {
	return (C & 63);
}
 
uint8_t Base64_HighByte(uint8_t A, uint8_t B) {
	assert(A < 64 && B < 64);
	return ((A << 2) | (B >> 4));
}

uint8_t Base64_MidByte(uint8_t B, uint8_t C) {
	assert(B < 64 && C < 64);
	return ((B << 4) | (C >> 2));
}

uint8_t Base64_LowByte(uint8_t C, uint8_t D) {
	assert(C < 64 && D < 64);
	return ((C << 6) | D);
}

uint8_t *ASCII_Base64_ByteStream(char *input, size_t size) {
	assert(size % 4 == 0);
	uint8_t *output = (uint8_t *) malloc((size / 4) * 3);
	size_t i = 0, j = 0;
	
	while(i < size && (*(input + i + 3)) != '=') {
		*(output + j++) = Base64_HighByte(ASCII_Base64(*(input + i)), ASCII_Base64(*(input + i + 1)));
		*(output + j++) = Base64_MidByte(ASCII_Base64(*(input + i + 1)), ASCII_Base64(*(input + i + 2)));
		*(output + j++) = Base64_LowByte(ASCII_Base64(*(input + i + 2)), ASCII_Base64(*(input + i + 3)));
		i+=4;
	} 
	if ((*(input + i + 3)) == '=') {
		if ((*(input + i + 2)) == '=') {
			*(output + j++) = Base64_HighByte(ASCII_Base64(*(input + i)), ASCII_Base64(*(input + i + 1)));
			*(output + j++) = Base64_MidByte(0, 0);
			*(output + j++) = Base64_LowByte(0, 0);
		} else {
			*(output + j++) = Base64_HighByte(ASCII_Base64(*(input + i)), ASCII_Base64(*(input + i + 1)));
			*(output + j++) = Base64_MidByte(ASCII_Base64(*(input + i + 1)), ASCII_Base64(*(input + i + 2)));
			*(output + j++) = Base64_LowByte(0, 0);
		}
	}
	
	return output;
}

