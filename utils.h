#include <stdint.h>

// converts a hex string to actual bytes. 
// result must be free()'d
uint8_t* hexToBytes(char* hex, size_t *new_size);

// converts a buffer to a hex string representation
// result must be free()'d
char* bytesToHex(uint8_t* bytes, size_t size);


int frequencyAnalysisScore(unsigned char* bytes, size_t size);

int XOR_fixedBlock(uint8_t* output, size_t size, uint8_t* input1, uint8_t* input2);
int XOR_singleCharKey(uint8_t* output, size_t size, uint8_t* input, char key);