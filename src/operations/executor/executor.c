#include <stdlib.h>
#include "../operations.h"
#include "../recognition/recognition.h"

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
    int size;
    char **words = readWords(context.input2, &size);
    if (!words)
    {
      return;
    }
    int *results = reconhecer(afd, words, size);
    writeReconhecerResult(results, context.output, size);
    free(results);
    freeWords(words, size);
  }
  if (result)
  {
    writeAFD(*result, context.output);
    freeAFD(result);
  }
  freeAFD(afd);
}