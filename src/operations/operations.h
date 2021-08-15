#include <stdio.h>
#include "../afd/afd.h"
#include "../context/context.h"
#include "./visualization/filter/filter.h"

#define OPERATIONS_H

/**
 * Operacao de visualizacao descrita no TP. Gera uma estrutura DOT correspondente ao AFD informado.
 * @param afd: afd alvo
 * @return estrutura DOT correspondente ao AFD informado.
*/
DOTFormat *visualizacao(AFD *afd);

/**
 * Gera um afd correspondente ao complemento do afd informado.
 * @param afd: afd cujo complemento sera gerado.
 * @return afd correspondente ao complemento do afd informado.
*/
AFD *complemento(AFD *afd);

/**
 * Gera um afd correspondente a intersecao entre os dois afds informados.
 * @param afd1: um dos afds que gerarao o afd de intersecao.
 * @param afd2: um dos afds que gerarao o afd de intersecao.
 * @return afd correspondente a intersecao entre os dois afds informados.
*/
AFD *intersecao(AFD *afd1, AFD *afd2);

/**
 * Gera um afd correspondente a uniao entre os dois afds informados.
 * @param afd1: um dos afds que gerarao o afd de uniao.
 * @param afd2: um dos afds que gerarao o afd de uniao.
 * @return afd correspondente a uniao entre os dois afds informados.
*/
AFD *uniao(AFD *afd1, AFD *afd2);

/**
 * Gera um afd que representa a minimizacao do afd informado.
 * @param afd: afd cuja minimizacao sera gerada.
 * @return afd correspondente a minimizacao do afd informado.
*/
AFD *minimizacao(AFD *afd);

/**
 * Executa o afd passado como parametro para cada uma das palavras informadas, e retorna um array com os resultados do 
 * reconhecimento de cada uma das palavras.
 * @param afd: afd que recebera as palavras como entrada.
 * @param words: palavras que serao inseridas no afd.
 * @param size: tamanho do array de palavras.
 * @return array correspondente aos resultados do reconhecimento das palavras, 1 para reconhecida e 0 para nao reconhecida.
*/
int *reconhecer(AFD *afd, char **words, int size);

/**
 * Aplica a operacao listada no contexto de aplicacao informado. Interessante notar que esse contexto ja eh considerado como
 * validado, portanto nao eh feita nenhuma validacao posterior. Logo, se for usar isso aqui nao esqueca de validar o contexto
 * antes.
 * @param context: contexto da aplicacao.
*/
void executeOperation(ApplicationContext context);
