#include <stdlib.h>
#include "../operations.h"

void executeOperation(ApplicationContext context)
{
  AFD *afd = readAFD(context.input1);
  AFD *result = NULL;
  if (context.dot)
  {
    DOTFormat *dotFormat = visualizacao(afd);
    writeDot(dotFormat, context.output);
    freeDot(dotFormat);
  }
  if (context.complemento)
  {
    result = complemento(afd);
  }
  if (context.intersecao)
  {
    AFD *afd2 = readAFD(context.input2);
    result = intersecao(afd, afd2);
    freeAFD(afd2);
  }
  if (context.uniao)
  {
    AFD *afd2 = readAFD(context.input2);
    result = uniao(afd, afd2);
    freeAFD(afd2);
  }
  if (context.minimizacao)
  {
    result = minimizacao(afd);
  }
  if (context.reconhecer)
  {
    char **words = readWords(context.input2);
    int *results = reconhecer(afd, words);
    writeReconhecerResult(results, context.output);
    free(results);
  }
  if (result)
  {
    writeAFD(*result, context.output);
    freeAFD(result);
  }
  freeAFD(afd);
}