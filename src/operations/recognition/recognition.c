#include <stdlib.h>
#include "./recognition.h"
#include "../../strings/stringutil.h"

char **readWords(char *fileName, int *size_ptr)
{
  FILE *file = fopen(fileName, "r");
  if (!file)
    return NULL;
  int size = 0;
  char **words = NULL;
  char buffer[100];
  while (fscanf(file, "%s\n", buffer) != EOF)
  {
    char *word = copyString(buffer);
    if (words)
    {
      words = realloc(words, sizeof(char *) * size);
    }
    else
    {
      words = malloc(sizeof(char *));
    }
    words[size] = word;
    size++;
  }
  *size_ptr = size;
  fclose(file);
  return words;
}

void freeWords(char **words, int size)
{
  for (int i = 0; i < size; i++)
  {
    free(words[i]);
  }
  free(words);
}

void writeReconhecerResult(int *result, char *fileName, int size)
{

  FILE *file = fopen(fileName, "w");
  if (!file)
    return;
  for (int i = 0; i < size; i++)
  {
    fprintf(file, "%d\n", result[i]);
  }
  fclose(file);
}