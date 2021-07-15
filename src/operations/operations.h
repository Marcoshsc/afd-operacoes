#include <stdio.h>
#include "../afd/afd.h"
#include "../context/context.h"
#include "./dot/dot.h"

#define OPERATIONS_H

DOTFormat *visualizacao(AFD *afd);
AFD *complemento(AFD *afd);
AFD *intersecao(AFD *afd1, AFD *afd2);
AFD *uniao(AFD *afd1, AFD *afd2);
AFD *minimizacao(AFD *afd);
int *reconhecer(AFD *afd, char **words);

void executeOperation(ApplicationContext context);
char **readWords(char *fileName);
void freeWords(char **words);
void writeReconhecerResult(int *result, char *fileName);
