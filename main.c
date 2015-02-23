#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "base64.h"



int s1e1() {
	char* hex = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
	size_t size_bytes;
	uint8_t* bytes = hexToBytes(hex, &size_bytes);

	char* output = malloc(Base64encode_len(size_bytes));
	Base64encode(output, bytes,size_bytes);

	printf("%s\n", output);
	printf("SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t <-- EXPECTED RESULT\n");
	free(output);
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

	uint8_t results[0xff][size_bytes+1];
	for (int i = 0; i < 0xff; i++){
		XOR_singleCharKey(results[i], size_bytes, bytes, i);
		results[i][size_bytes] = '\0';
	}

	int bestScore = 0;
	int bestIdx;
	for (int i = 0; i < 0xff; i++) {
		int score = frequencyAnalysisScore(results[i], size_bytes);
		if (score > bestScore) {
			bestScore = score;
			bestIdx = i;
		}
	}

	printf("most likely has score %d and is: %s\n", bestScore, results[bestIdx]);

	return 0;
}


int s1e4() {
	int lines_alloc = 128;
	int line_length = 65;
	size_t line_bytes_length;

	uint8_t** lines = malloc(sizeof(uint8_t*)*lines_alloc);

	FILE *fp = fopen("data/s1e4.txt", "r");
	if (fp == NULL) {
		printf("no file...");
		return 1;
	}
	int total_lines = 0;
	while(1) {
		if (total_lines >= lines_alloc) {
			lines_alloc*=1.5;
			lines = realloc(lines, sizeof(uint8_t*)*lines_alloc);
			if (lines == NULL) {
				return 2;
			}
		}

		char line[line_length];
		if (fgets(line, line_length, fp) == NULL) {
			break; //no more lines
		}

		for (int i = strlen(line)-1; i >= 0; --i) {
			if (line[i] != '\n' && line[i] != '\r') {
				line[i+1] = '\0';
				break;
			}
		}

		lines[total_lines] = hexToBytes(line, &line_bytes_length);

		total_lines++;
	}
	fclose(fp);
	printf("READ %d LINES. Searching for secrets...\n", total_lines);

	uint8_t results[total_lines][0xff][line_bytes_length+1];
	for (int i = 0; i < total_lines; ++i) {
		for (int j = 0; j < 0xff; j++){
			XOR_singleCharKey(results[i][j], line_bytes_length, lines[i], j);
			results[i][j][line_bytes_length] = '\0';
		}
	}

	int bestScore = 1;
	int bestLine, bestKey;
	for (int i = 0; i < total_lines; ++i) {
		for (int j = 0; j < 0xff; j++){
			int score = frequencyAnalysisScore(results[i][j], line_bytes_length);
			if (score >= bestScore) {
				bestScore = score;
				bestLine = i;
				bestKey = j;

				printf("-> candidate is now line %d, key %c, score %d\n and is: %s\n", bestLine, bestKey, bestScore, results[bestLine][bestKey]);
			}
		}
	}

	printf("******\nTHE MOST LIKELY is line %d, with key %c, which has score %d and is: %s\n", bestLine, bestKey, bestScore, results[bestLine][bestKey]);

	for (int i = total_lines-1; i >= 0; --i) {
		free(lines[i]);
	}
	free(lines);

	return 0;
}

int s1e5() {
	char* input = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
	
	int size = strlen(input);
	uint8_t* output = malloc(size);
	XOR_repeatingKey(output, size, input, "ICE", 3);

	char* result_hex = bytesToHex(output, size);
	printf("%s\n", result_hex);

	printf("0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f <-- EXPECTED OUTPUT\n");
	return 0;
}


int main(int argc, char** argv) {
	s1e1();
	return 0;
}