#include <stdlib.h>
#include "./operations.h"

DOTFormat *visualizacao(AFD *afd)
{
  puts("Visualisacao");
  return NULL;
}
AFD *complemento(AFD *afd)
{
  puts("Visualisacao");
  return NULL;
}

AFD *intersecao(AFD *afd1, AFD *afd2)
{
  puts("Intersecao");
  return NULL;
}

AFD *uniao(AFD *afd1, AFD *afd2)
{
  puts("Uniao");
  return NULL;
}

AFD *minimizacao(AFD *afd)
{
  puts("Minimizacao");
  return NULL;
}

int *reconhecer(AFD *afd, char **words)
{
  puts("Reconhecer");
  return NULL;
}

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

void freeDot(DOTFormat *DOTFormat)
{
}

void writeDot(DOTFormat *DOTFormat, char *fileName)
{
}

char **readWords(char *fileName)
{
}

void freeWords(char **words)
{
}

void writeReconhecerResult(int *result, char *fileName)
{
}