// converts a hex string to actual bytes. 
// result must be free()'d
char* hexToBytes(char* hex, size_t *new_size);

// converts a buffer to a hex string representation
// result must be free()'d
char* bytesToHex(char* bytes, size_t size);

// will read a file into a continuous buffer
// result must be free()'d
char* readFileToBuffer(char** ptr, char* filename, int ignoreWhitespace);


int frequencyAnalysisScore(char* bytes, size_t size);
int hammingDistance(char* input1, char* input2, size_t size);

int XOR_fixedBlock(char* output, size_t size, char* input1, char* input2);
int XOR_singleCharKey(char* output, size_t size, char* input, char key);
int XOR_repeatingKey(char* output, size_t size, char* input, char* key, size_t key_size);