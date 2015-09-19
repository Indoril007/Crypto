#include <set1.h>

char *repeating_xor_encrypt(char *key, char *rawString) {
	size_t key_len = strlen(key);
	size_t rawString_len = strlen(rawString);
	size_t i, j, n = 0;
	
	char *encryptedString;
	encryptedString = (char *) malloc(2 * rawString_len + 1);
	
	for (i = 0; i < rawString_len; i++) {
		j = i % key_len;
		*(encryptedString + n++) = Byte_HighHexASCII(*(rawString + i) ^ *(key + j));
		*(encryptedString + n++) = Byte_LowHexASCII(*(rawString + i) ^ *(key + j));
	}
	
	*(encryptedString + n) = '\0';
	return encryptedString;
	
}

int main() {
	char *input_1, *input_2, *output;
	input_1 = "Burning 'em, if you ain't quick and nimble I go crazy when I hear a cymbal";
	input_2 = "ICE";
	
	printf("\nINPUT:\n%s\n%s\n\n", input_1, input_2);
	output = repeating_xor_encrypt(input_2, input_1);
	printf("OUTPUT:\n%s\n", output);
	
	return 0;
}
