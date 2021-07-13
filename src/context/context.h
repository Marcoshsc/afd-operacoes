#include <stdio.h>
#include "../cli/cli.h"
#include "../params/params.h"

typedef struct application_ctx
{
  int dot;
  int complemento;
  int intersecao;
  int uniao;
  int minimizacao;
  int reconhecer;
  int outputProvided;

  int err;
  char message[100];

  char *input1;
  char *input2;
  char *output;
} ApplicationContext;

ApplicationContext *getAppContext(CLI_Result result);
void validateAppContext(ApplicationContext *appContext);
void freeAppContext(ApplicationContext *context);