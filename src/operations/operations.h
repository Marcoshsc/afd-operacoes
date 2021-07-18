#include <stdio.h>
#include "../afd/afd.h"
#include "../context/context.h"
#include "./visualization/filter/filter.h"

#define OPERATIONS_H

DOTFormat *visualizacao(AFD *afd);
AFD *complemento(AFD *afd);
AFD *intersecao(AFD *afd1, AFD *afd2);
AFD *uniao(AFD *afd1, AFD *afd2);
AFD *minimizacao(AFD *afd);
int *reconhecer(AFD *afd, char **words, int size);

void executeOperation(ApplicationContext context);
