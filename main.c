#include <stdint.h>
#include <stdlib.h>
#include "utils.h"



int s1e1() {
	char* hex = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
	size_t size_bytes;
	uint8_t* bytes = hexToBytes(hex, &size_bytes);

	free(bytes);
	return 0;
}

int main(int argc, char** argv) {
	s1e1();
	return 0;
}