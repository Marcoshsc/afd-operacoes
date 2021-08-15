#include <stdio.h>
#include "../../dot/dot.h"

/**
 * Filtra as transicoes presentes no DOTFormat informado, de forma que transicoes que partem e alcancam estados correspondente
 * sejam representadas por somente um arco no grafo do arquivo DOT.
 * @param dotFormat: Informacoes DOT alvo.
*/
void filterTransitions(DOTFormat *dotFormat);