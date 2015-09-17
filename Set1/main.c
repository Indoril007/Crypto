#include <set1.h>

char *String_Hex_Base64(char *hexString) {
	size_t len = strlen(hexString);
	assert(len >= 2);
	
	char *output;
	uint8_t A, B, C;
	size_t i = 0;
	size_t n = 0;
	output = (char *) malloc(len + 1);
	
	size_t pad = len % 3;
	len = len - pad;
	
	while(n != len) {
		A = ASCII_Hex(*(hexString + n++));
		B = ASCII_Hex(*(hexString + n++));
		C = ASCII_Hex(*(hexString + n++));
		*(output + i++) = Base64_ASCII(Hex_HighBase64(A, B));
		*(output + i++) = Base64_ASCII(Hex_LowBase64(B, C));
	}
	
	if(pad == 1) {
		A = ASCII_Hex(*(hexString + n++));
		B = 0;
		*(output + i++) = Base64_ASCII(Hex_HighBase64(A, B));
		*(output + i++) = '=';
	} else if (pad == 2) {
		A = ASCII_Hex(*(hexString + n++));
		B = ASCII_Hex(*(hexString + n++));
		C = 0;
		*(output + i++) = Base64_ASCII(Hex_HighBase64(A, B));
		*(output + i++) = Base64_ASCII(Hex_LowBase64(B, C));
		*(output + i++) = '=';
		*(output + i++) = '=';
	}

	*(output + i) = '\0';
	
	return output;
}

int single_xor_cipher_find(char *inputString) {
	uint16_t len = strlen(inputString);
	uint16_t i, j, n, alpha_count, space_count, nonalphanum_count;
	
	
	uint8_t *xor;
	xor = (uint8_t *) malloc((len / 2) + 1);
	
	for (i = 255; i > 0; i-- ) {
		j = 0;
		n = 0;
		alpha_count = 0;
		space_count = 0;
		nonalphanum_count = 0;
		
		while(j < len) {
			*(xor + n) = i ^ Hex_combine(ASCII_Hex(*(inputString + j)), ASCII_Hex(*(inputString + j + 1)));
			if (isLowAlpha(*(xor + n))) {
				alpha_count++;
			} else if (*(xor + n) == 32) {
				space_count++;
			} else if(!isAlphaNum(*(xor + n))) {
				nonalphanum_count++;
			}
			
			j += 2;
			n++;
		}
		
		if(alpha_count > (len / 3) && space_count >= 2 && nonalphanum_count <= 5) {
			printf("%s\n", xor);
		}	
	}
	
	
	return 0;
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
	printf("%s\n", encryptedString);
	
}

int main() {
	repeating_xor_encrypt("ICE","Burning 'em, if you ain't quick and nimble I go crazy when I hear a cymbal");

	// single_xor_cipher_find("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736");
	
	// FILE *fp;
	// char *hexString;
	// char *chuck;
	// hexString = (char *) malloc(61);
	// chuck = (char *) malloc(1);
	// *(hexString + 60) = '\0';
	
	// fp = fopen("input.txt", "r");
	// while (fgets(hexString, 61, fp)) {
		// single_xor_cipher_find(hexString);
		// fgets(chuck, 2, fp);
	// }
	
	// fclose(fp);
	return 0;
}
