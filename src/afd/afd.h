#include <stdio.h>

/**
 * Estrutura responsavel por representar uma transicao. Utiliza os indices dos elementos em seus respectivos arrays no afd.
 * from: estado em que o afd se encontra no momento da transicao
 * read: simbolo que o afd faz a leitura para ativar a transicao
 * to: estado que o afd assume apos realizar a transicao 
 */
typedef struct transition_est
{
  int *from;
  int *read;
  int *to;
} Transition;

/** 
 * Estrutura que representa um AFD.
 * states: array de estados de tamanho number_states.
 * alphabet: array de simbolos de tamanho number_symbols.
 * initial_state: estado inicial, indice sobre o array de estados.
 * final_states: estados finais, array de indices sobre o array de estados, de tamanho number_final_states
 * transitions: array de transicoes de tamanho number_transitions. 
*/
typedef struct afd_est
{

  char **states;
  int *number_states;

  char **alphabet;
  int *number_symbols;

  int *initial_state;

  int *final_states;
  int *number_final_states;

  Transition **transitions;
  int *number_transitions;

} AFD;

/**
 * Factory method que retorna uma instancia de transicao, dados os parametros de transicao em sua forma string,
 * convertendo cada um deles para indices sobre os arrays de estados e simbolos no AFD recebido.
 * @param afd: AFD alvo
 * @param from: equivalente ao campo "from" da estrutura de transicao.
 * @param read: equivalente ao campo "read" da estrutura de transicao.
 * @param to: equivalente ao campo "to" da estrutura de transicao.
 * @return transicao correspondente.
*/
Transition *getTransition(AFD afd, char *from, char *to, char *read);

/**
 * Aloca memoria e retorna uma transicao sem valores.
 * @return uma transicao sem valores.
*/
Transition *getEmptyTransition();

/**
 * Busca e retorna a posicao do estado no AFD provido.
 * @param afd: afd alvo
 * @param state: estado a ser procurado
 * @return o indice caso encontre, -1 caso contrario.
*/
int getStatePosition(AFD afd, char *state);

/**
 * Busca e retorna a posicao do simbolo no AFD provido.
 * @param afd: afd alvo
 * @param symbol: estado a ser procurado
 * @return o indice caso encontre, -1 caso contrario.
*/
int getSymbolPosition(AFD afd, char *symbol);

/**
 * Retorna um afd vazio.
 * @return um afd vazio.
*/
AFD *getEmptyAFD();

/**
 * Faz a leitura de um AFD a partir do arquivo de nome informado.
 * @param fileName: nome do arquivo que contem o afd.
 * @return o afd correspondente.
*/
AFD *readAFD(char *fileName);

/**
 * Escreve o afd informado no arquivo com o nome provido.
 * @param afd: o afd que se quer escrever no arquivo.
 * @param fileName: nome do arquivo que vai receber o afd.
*/
void writeAFD(AFD afd, char *fileName);

/**
 * Libera a memoria alocada por um afd.
 * @param afd: afd cuja memoria alocada sera liberada.
*/
void freeAFD(AFD *afd);