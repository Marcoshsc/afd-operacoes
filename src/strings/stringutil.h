#include <stdio.h>
#define STRINGUTIL_H

char *copyString(char *src);
char *concatWithComma(char *str1, char *str2);
char **splitByComma(char *str);
void freeSplit(char **split);