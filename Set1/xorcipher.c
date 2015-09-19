#include <set1.h>

char *single_xor_cipher_find(char *inputString) {
	uint16_t len = strlen(inputString);
	uint16_t i, j, n, alpha_count, space_count, nonalphanum_count;
	
	
	char *xor;
	xor = (char *) malloc((len / 2) + 1);
	
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
			// printf("%s\n", xor);
			return xor;
		}	
	}
	
	
	return 0;
}

int main() {
	char *input, *output;
	input = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
	
	printf("\nINPUT:\n%s\n\n", input);
	output = single_xor_cipher_find(input);
	printf("OUTPUT:\n%s\n", output);
	
	return 0;
}
