#include <stdio.h>
#include "../operations.h"

/**
 * Le palavras do arquivo com nome informado, e armazena o tamanho no ponteiro recebido.
 * @param fileName: nome do arquivo que contem as palavras.
 * @param size_ptr: ponteiro que vai armazenar o tamanho do array de palavras.
 * @return array com as palavras lidas.
*/
char **readWords(char *fileName, int *size_ptr);

/**
 * Libera um array de palavras de tamanho size.
 * @param words: array de palavras.
 * @param size: tamanho do array.
*/
void freeWords(char **words, int size);

/**
 * Escreve o resultado do reconhecimento de palavras (funcao de reconhecimento deste codigo), no arquivo de nome informado.
 * @param result: resultados de reconhecimento (0 para nao aceito, 1 para aceito).
 * @param fileName: nome do arquivo que vai receber os resultados.
 * @param size: tamanho do array de resultados.
*/
void writeReconhecerResult(int *result, char *fileName, int size);

/**
 * Aplica a funcao de transicao no AFD escolhido, lendo o simbolo a partir do estado informado, e retorna o estado resultante.
 * @param afd: afd alvo.
 * @param symbol: simbolo lido.
 * @param current_state: estado atual do AFD.
 * @return estado resultante da aplicacao da transicao.
*/
char *transitionFunction(AFD *afd, char *symbol, char *current_state);