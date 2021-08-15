#include <stdio.h>
#include "../recognition/recognition.h"

/**
 * Funcao responsavel por gerar um produto de AFDs. Essa funcao nao modifica em nada nenhum dos dois AFDs recebidos.
 * O produto dos AFDs nao possui estado final algum, uma vez que os estados finais dependem da operacao a ser feita, e devem
 * ser preenchidos pelo usuario.
 * @param afd1: primeiro fator do produto
 * @param afd2: segundo fator do produto
 * @return afd correspondente ao produto de afd1 com afd2.
*/
AFD *afdProduct(AFD *afd1, AFD *afd2);