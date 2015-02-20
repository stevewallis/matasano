#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"



int s1e1() {
	char* hex = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
	size_t size_bytes;
	uint8_t* bytes = hexToBytes(hex, &size_bytes);

	//TODO base64 implementation
	
	free(bytes);
	return 0;
}

int s1e2() {
	char* hex_input_1 = "1c0111001f010100061a024b53535009181c";
	char* hex_input_2 = "686974207468652062756c6c277320657965";

	size_t size_bytes_1;
	uint8_t* bytes_1 = hexToBytes(hex_input_1, &size_bytes_1);

	size_t size_bytes_2;
	uint8_t* bytes_2 = hexToBytes(hex_input_2, &size_bytes_2);

	if (size_bytes_1 != size_bytes_2) {
		free(bytes_2);
		free(bytes_1);
		return 1;
	}

	uint8_t* output = malloc(size_bytes_1);
	XOR_fixedBlock(output, size_bytes_1, bytes_1, bytes_2);

	char* result_hex = bytesToHex(output, size_bytes_1);
	printf("%s\n", result_hex);

	printf("746865206b696420646f6e277420706c6179 <-- EXPECTED RESULT\n");

	free(result_hex);
	free(output);
	free(bytes_2);
	free(bytes_1);
	return 0;
}

int s1e3() {
	char* input = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

	size_t size_bytes;
	uint8_t* bytes = hexToBytes(input, &size_bytes);

	uint8_t results[0xff][size_bytes];

	for (int i = 0; i < 0xff; i++){
		XOR_singleCharKey(results[i], size_bytes, bytes, i);
	}

	return 0;
}

int main(int argc, char** argv) {
	s1e3();
	return 0;
}