#include <stdio.h>
#include "../cli/cli.h"
#include "../params/params.h"

/**
 * Estrutura que representa o contexto de aplicacao, basicamente armazenando quais parametros foram informados e 
 * seus respectivos valores. A aplicacao so consegue receber no maximo dois arquivos de entrada e um de saida, e somente
 * uma operacao pode ocorrer por vez. 
*/
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

/**
 * Gera o contexto de aplicacao a partir de um resultado de CLI.
 * @param result: o resultado de CLI.
 * @return o contexto de aplicacao correspondente.
*/
ApplicationContext *getAppContext(CLI_Result result);

/**
 * Recebe e valida o contexto recebido. Basicamente verifica se somente uma opcao foi selecionada, e tambem se a quantidade
 * correta de valores para cada opcao selecionada foi informado. Caso nao seja valido, preenche o campo err e message da
 * estrutura ApplicationContext, informando que ocorreu um erro.
 * @param appContext: contexto da aplicacao.
*/
void validateAppContext(ApplicationContext *appContext);

/**
 * Libera a memoria alocada pelo contexto de aplicacao.
 * @param context: contexto da aplicacao.
*/
void freeAppContext(ApplicationContext *context);