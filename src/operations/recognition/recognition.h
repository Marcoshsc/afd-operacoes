#include <stdio.h>
#include "../operations.h"

char **readWords(char *fileName, int *size_ptr);
void freeWords(char **words, int size);
void writeReconhecerResult(int *result, char *fileName, int size);
char *transitionFunction(AFD *afd, char *symbol, char *current_state);