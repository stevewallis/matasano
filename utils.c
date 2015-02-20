#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint8_t nibbleFromHexChar(char hex) {
	if (hex >= '0' && hex <= '9') { return hex - '0'; }
	if (hex >= 'A' && hex <= 'F') { return hex - 'A' + 10; }
	if (hex >= 'a' && hex <= 'f') { return hex - 'a' + 10; }
	return 0;
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