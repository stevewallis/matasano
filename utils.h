#include <stdint.h>

uint8_t nibbleFromHexChar(char hex);
uint8_t* hexToBytes(char* hex, size_t *new_size);
char* bytesToHex(uint8_t* bytes, size_t size);

int fixedXOR(uint8_t* output, size_t size, uint8_t* input1, uint8_t* input2);