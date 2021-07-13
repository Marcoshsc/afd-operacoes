#include <stdio.h>
#include <string.h>
#include "./cli/cli.h"

CLI_Params *createCLIParams()
{
  CLI_Params *params = getParams(10);

  registerParam(params, "--dot", 1);
  registerParam(params, "--output", 1);
  registerParam(params, "--complemento", 1);
  registerParam(params, "--intersecao", 2);
  registerParam(params, "--uniao", 2);
  registerParam(params, "--minimizacao", 1);
  registerParam(params, "--reconhecer", 2);

  return params;
}

int main(int argc, char *argv[])
{
  CLI_Params *params = createCLIParams();
  CLI_Result *result = readCLI(params, argc, argv);

  freeCLI(result);
}