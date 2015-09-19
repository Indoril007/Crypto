#include <set1.h>

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

int main() {
	char *input_1, *input_2, *output;
	input_1 = "1c0111001f010100061a024b53535009181c";
	input_2 =  "686974207468652062756c6c277320657965";
	
	printf("\nINPUT:\n%s\n%s\n\n", input_1, input_2);
	output = XOR_Hex_String(input_1, input_2);
	printf("OUTPUT:\n%s\n", output);
	
	return 0;
}
