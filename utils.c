#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static uint8_t nibbleFromHexChar(char hex) {
	if (hex >= '0' && hex <= '9') { return hex - '0'; }
	if (hex >= 'A' && hex <= 'F') { return hex - 'A' + 10; }
	if (hex >= 'a' && hex <= 'f') { return hex - 'a' + 10; }
	return 0;
}

static char nibbleToHexChar(uint8_t nibble) {
	return nibble+((nibble<0xa)?'0':('a'-0xa));
}

uint8_t* hexToBytes(char* hex, size_t *new_size) {
	char* p;
	uint8_t* bytes;
	*new_size = strlen(hex)/2;
	bytes = malloc(*new_size+1);

	p = hex;
	for (int i = 0; i < *new_size; i++){
		bytes[i] = nibbleFromHexChar(*p)<<4 | nibbleFromHexChar(*(p+1));
		p += 2;
	}
	bytes[*new_size] = 0;

	return bytes;
}

char* bytesToHex(uint8_t* bytes, size_t size) {
	uint8_t* p;
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
	hex[new_size] = 0;

	return hex;
}


int XOR_fixedBlock(uint8_t* output, size_t size, uint8_t* input1, uint8_t* input2) {
	for (int i = 0; i < size; i++) {
		output[i] = input1[i]^input2[i];
	}
	return 0;
}

int XOR_singleCharKey(uint8_t* output, size_t size, uint8_t* input, char key) {
	for (int i = 0; i < size; i++) {
		output[i] = input[i]^key;
	}
	return 0;
}

