#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static char nibbleFromHexChar(char hex) {
	if (hex >= '0' && hex <= '9') { return hex - '0'; }
	if (hex >= 'A' && hex <= 'F') { return hex - 'A' + 10; }
	if (hex >= 'a' && hex <= 'f') { return hex - 'a' + 10; }
	return 0;
}

static char nibbleToHexChar(char nibble) {
	return nibble+((nibble<0xa)?'0':('a'-0xa));
}

char* hexToBytes(char* hex, size_t *new_size) {
	char* p;
	char* bytes;
	*new_size = strlen(hex)/2;
	bytes = malloc(*new_size+1);

	p = hex;
	for (int i = 0; i < *new_size; i++){
		bytes[i] = nibbleFromHexChar(*p)<<4 | nibbleFromHexChar(*(p+1));
		p += 2;
	}
	bytes[*new_size] = '\0';

	return bytes;
}

char* bytesToHex(char* bytes, size_t size) {
	char* p;
	char* hex;
	size_t new_size;

	new_size = size*2;
	hex = malloc(new_size+1);

	p = bytes;
	for (int i = 0; i < new_size; i+=2) {
		hex[i] = nibbleToHexChar(*p>>4);
		hex[i+1] = nibbleToHexChar(*p&0x0f);
		p++;
	}
	hex[new_size] = '\0';

	return hex;
}

int readFileToBuffer(char** ptr, char* filename, int ignoreWhitespace) {
	FILE* fp = fopen(filename, "rb");
	if (fp == NULL) {
		return 1;
	}
	fseek(fp, 0L, SEEK_END);
	long size = ftell(fp);
	rewind(fp);

	*ptr = malloc(size);
	if (*ptr == NULL) {
		fclose(fp);
		return 2;
	}

	long truesize = 0;
	int c;
	for (int i = 0; i < size; ++i) {
		c = fgetc(fp);
		if (c != EOF) {
			if (ignoreWhitespace && (c < 0x21 || c > 0x7e)) {
				continue;
			}
			(*ptr)[truesize] = c;
			truesize++;
		} else { break; }
	}

	fclose(fp);

	return 0;
}


int XOR_fixedBlock(char* output, size_t size, char* input1, char* input2) {
	for (int i = 0; i < size; ++i) {
		output[i] = input1[i]^input2[i];
	}
	return 0;
}

int XOR_singleCharKey(char* output, size_t size, char* input, char key) {
	for (int i = 0; i < size; ++i) {
		output[i] = input[i]^key;
	}
	return 0;
}

int XOR_repeatingKey(char* output, size_t size, char* input, char* key, size_t key_size) {
	for (int i = 0; i < size; ++i) {
		output[i] = input[i]^key[i%key_size];
	}

	return 0;
}

static char* ENGLISH_CHAR_FREQUENCY = "ETAOINSHRDLUCMWFGYPBVKJXQZ";
int frequencyAnalysisScore(char* bytes, size_t size) {

	int letter_freqs[26] = {0};
	for (int i = 0; i < size; i++) {
		if (bytes[i] < 32 || bytes[i] > 127) {
			if (bytes[i] != '\r' && bytes[i] != '\n' && bytes[i] != '\t')
			return 0; 	
		} 

		if (bytes[i] >= 'a' && bytes[i] <= 'z') {
			letter_freqs[bytes[i]-'a']++;
			continue;
		}

		if (bytes[i] >= 'A' && bytes[i] <= 'Z') {
			letter_freqs[bytes[i]-'A']++;
			continue;	
		}
	}

	char rankedAlphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	int temp_freq;
	char temp_char;
	for (int i = 0; i < 26-1; ++i) {
		for (int j = 0; j < 26-1-i; ++j) {
			if (letter_freqs[j] < letter_freqs[j+1]) {
				temp_freq = letter_freqs[j+1];
				temp_char = rankedAlphabet[j+1];

				letter_freqs[j+1] = letter_freqs[j];
				rankedAlphabet[j+1] = rankedAlphabet[j];

				letter_freqs[j] = temp_freq;
				rankedAlphabet[j] = temp_char;
			}
		}
	}

	int score = 0;
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 6; ++j) {
			if (ENGLISH_CHAR_FREQUENCY[i] == rankedAlphabet[j]) {
				score++;
			}
		}	
	}

	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 6; ++j) {
			if (ENGLISH_CHAR_FREQUENCY[26-i] == rankedAlphabet[26-j]) {
				score++;
			}
		}	
	}

	return score;
}

int hammingDistance(char* input1, char* input2, size_t size) {
	int hammingDistance = 0;
	for (int i = 0; i < size; ++i) {
		char xor = input1[i] ^ input2[i];
		for (unsigned char j = 0x1; j < 0x80; j<<=1) {
			if ((xor&j) > 0) {
				hammingDistance++;
			}
		}
	}
	return hammingDistance;
}















