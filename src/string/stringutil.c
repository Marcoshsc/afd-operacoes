#include <stdlib.h>
#include <string.h>
#include "./stringutil.h"

char *copyString(char *src)
{
  char *newString = malloc(sizeof(char) * strlen(src) + 1);
  strcpy(newString, src);
  return newString;
}