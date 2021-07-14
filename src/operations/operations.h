#include <stdio.h>
#include "../afd/afd.h"
#include "../context/context.h"

#define OPERATIONS_H

typedef struct dotformat_est
{
  // put something here
} DOTFormat;

DOTFormat *visualizacao(AFD *afd);
AFD *complemento(AFD *afd);
AFD *intersecao(AFD *afd1, AFD *afd2);
AFD *uniao(AFD *afd1, AFD *afd2);
AFD *minimizacao(AFD *afd);
int *reconhecer(AFD *afd, char **words);

void executeOperation(ApplicationContext context);
void freeDot(DOTFormat *DOTFormat);
void writeDot(DOTFormat *DOTFormat, char *fileName);
char **readWords(char *fileName);
void freeWords(char **words);
void writeReconhecerResult(int *result, char *fileName);
