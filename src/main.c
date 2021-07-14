#include <stdio.h>
#include <string.h>
#include "./operations/operations.h"

CLI_Params *createCLIParams()
{
  CLI_Params *params = getParams(10);

  registerParam(params, DOT, 1);
  registerParam(params, OUTPUT, 1);
  registerParam(params, COMPLEMENTO, 1);
  registerParam(params, INTERSECAO, 2);
  registerParam(params, UNIAO, 2);
  registerParam(params, MINIMIZACAO, 1);
  registerParam(params, RECONHECER, 2);

  return params;
}

int main(int argc, char *argv[])
{
  CLI_Params *params = createCLIParams();
  CLI_Result *result = readCLI(params, argc, argv);

  ApplicationContext *appContext = getAppContext(*result);
  if (appContext->err)
  {
    printf("Invalid input provided. Error log: %s\n", appContext->message);
    return 1;
  }

  validateAppContext(appContext);
  if (appContext->err)
  {
    printf("Invalid input provided. Error log: %s\n", appContext->message);
    return 1;
  }

  executeOperation(*appContext);

  freeAppContext(appContext);
  freeCLI(result);
  return 0;
}