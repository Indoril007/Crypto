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

int main() {
	char *input, *output;
	input = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
	
	printf("\nINPUT:\n%s\n\n", input);
	output = String_Hex_Base64(input);
	printf("OUTPUT:\n%s\n", output);
	
	return 0;
}
