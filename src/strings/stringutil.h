#include <stdio.h>
#define STRINGUTIL_H

/**
 * Retorna uma copia completa da string recebida como parametro.
 * @param src: string que sera copiada.
 * @return string correspondente a copia de src.
*/
char *copyString(char *src);

/**
 * Retona a string correspondente a concatenacao das duas strings por algum simbolo. Atualmente eh o "_", mas pode mudar.
 * @param str1: primeiro fator da concatenacao
 * @param str2: segundo fator da concatenacao
 * @return string concatenada
*/
char *concatWithComma(char *str1, char *str2);

/**
 * Pega uma string concatenada por algum simbolo (atualmente "_", mas pode mudar, sempre consulte a documentacao) e retorna 
 * as strings que formam a concatenacao, sem o simbolo especial.
 * @param str: string concatenada
 * @return strings que formam a concatenacao. Tamanho sempre 2.
*/
char **splitByComma(char *str);

/**
 * Libera a memoria alocada para um array de strings de tamanho 2.
 * @param split: array de strings de tamanho 2.
*/
void freeSplit(char **split);