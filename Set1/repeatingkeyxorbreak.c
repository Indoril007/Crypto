#include <set1.h>

uint8_t *Base64_Byte(char *input) {
	size_t len = strlen(input);
	assert((len % 4) == 0);
	uint8_t *output;
	output = (uint8_t *) malloc((len / 4) * 3);
	size_t i, n = 0;
	
	for(i = 0; i < len; i+=4) {
		*(output + n++) = Base64_HighByte(*(input + i), *(input + i + 1));
		*(output + n++) = Base64_MidByte(*(input + i + 1), *(input + i + 2));
		*(output + n++) = Base64_LowByte(*(input + i +2), *(input + i + 3));
	}
	
	return output;
}

uint8_t hamming_distance(uint8_t *input_1, uint8_t *input_2, uint8_t len) {
	assert(len > 0);
	uint8_t i, j, xor, hamming_distance = 0;
	
	for(i = 0; i < len; i++) {
		xor = *(input_1 + i) ^ *(input_2 + i);
		for (j = 0; j < 8; j++) {
			hamming_distance += (xor >> j) & 1;
		}
	}
	
	return hamming_distance;
}

uint8_t determine_keysize(uint8_t *input, size_t size) {
	uint8_t i, keysize[5], min;
	
	
	
	for(i = 2; i <= 40; i++) {
		if((hamming_distance(input, input+i, i) / i) < min) {
			keysize = i;
		}
	}
}



int main() {
	char *input_1, *input_2;
	input_1 = "this is a test";
	input_2 = "wokka wokka!!!";
	
	size_t len = strlen(input_1);
	
	printf("\n%s\n%s\n%d", input_1, input_2, hamming_distance(input_1, input_2, len));
}
