#include <set1.h>
#include <bag.h>

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

void determine_keysize(uint8_t *input) {
	uint8_t i, j, min, dist;
	Bag *keyBag;
	keyBag = Bag_create(10);
	
	for(i = 2; i <= 40; i++) {
		dist = 0;
		for (j = 0; j < 5; j++) {
			dist += hamming_distance((j * i) + input, (j * i) + input+i, i);
		}
		
		if((dist < keyBag->max) || (keyBag->size < keyBag->capacity)) {
			if(keyBag->size < keyBag->capacity) {
				Bag_addelement(keyBag, dist, i);
			} else {
				Bag_removemax(keyBag);
				Bag_addelement(keyBag, dist, i);
			}
		}
	}
	
	while(keyBag->size != 0) {
		printf("%d ", Bag_pop(keyBag));
	}
	printf("\n");
	
	return;
}

int main() {
	FILE *fp;
	char *input;
	uint8_t *line_output, *output;
	input = (char *) malloc(61);
	line_output = (uint8_t *) malloc(40);
	output = (uint8_t *) malloc((40 * 64) - 4);
	size_t i = 0;
	uint8_t j;
	
	
	fp = fopen("input2.txt", "r");
	while (fscanf(fp, "%s ", input) == 1) {
		line_output = ASCII_Base64_ByteStream(input, strlen(input));
		for(j = 0; j < 40; j++) {
			*(output + j + i) = *(line_output + j); 
		}
		i += 40;
	}
	
	fclose(fp);
	
	determine_keysize(output);
	
	
	
	return 0;
}
