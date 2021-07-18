#include <stdio.h>

char **readWords(char *fileName, int *size_ptr);
void freeWords(char **words, int size);
void writeReconhecerResult(int *result, char *fileName, int size);