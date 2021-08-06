#include "./product.h"
#include "../../strings/stringutil.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int doubleTransitionFunction(AFD *productAfd, AFD *afd1, AFD *afd2, char *state1, char *state2, char *symbol)
{
  char *value1 = transitionFunction(afd1, symbol, state1);
  char *value2 = transitionFunction(afd2, symbol, state2);
  char *concattedValue = concatWithComma(value1, value2);

  int foundIndex = -1;
  for (int i = 0; i < *productAfd->number_states; i++)
  {
    if (!strcmp(concattedValue, productAfd->states[i]))
    {
      foundIndex = i;
      break;
    }
  }
  free(concattedValue);
  return foundIndex;
}

AFD *afdProduct(AFD *afd1, AFD *afd2)
{
  AFD *productAfd = getEmptyAFD();
  *productAfd->number_symbols = *afd1->number_symbols;
  productAfd->alphabet = malloc((*afd1->number_symbols) * sizeof(char *));
  for (int i = 0; i < *afd1->number_symbols; i++)
  {
    char *symbol = afd1->alphabet[i];
    char *newSymbol = copyString(symbol);
    productAfd->alphabet[i] = newSymbol;
  }

  int numberOfStates = (*afd1->number_states) * (*afd2->number_states);
  *productAfd->number_states = numberOfStates;
  productAfd->states = malloc(sizeof(char *) * numberOfStates);
  int currentStateIndex = 0;
  for (int i = 0; i < *afd1->number_states; i++)
  {
    char *state1 = afd1->states[i];
    for (int j = 0; j < *afd2->number_states; j++)
    {
      char *state2 = afd2->states[j];
      char *productState = concatWithComma(state1, state2);
      productAfd->states[currentStateIndex] = productState;
      if (i == *afd1->initial_state && j == *afd2->initial_state)
      {
        *productAfd->initial_state = currentStateIndex;
      }
      currentStateIndex++;
    }
  }

  *productAfd->number_transitions = numberOfStates * (*productAfd->number_symbols);
  productAfd->transitions = malloc(sizeof(Transition *) * (*productAfd->number_transitions));
  int currentTransitionIndex = 0;
  for (int i = 0; i < *productAfd->number_states; i++)
  {
    char *state = productAfd->states[i];
    puts(state);
    char **splitted = splitByComma(state);
    puts("here");
    puts(splitted[0]);
    puts(splitted[1]);
    for (int j = 0; j < *productAfd->number_symbols; j++)
    {
      char *symbol = productAfd->alphabet[j];
      int result = doubleTransitionFunction(productAfd, afd1, afd2, splitted[0], splitted[1], symbol);
      Transition *transition = getEmptyTransition();
      *transition->from = i;
      *transition->to = result;
      *transition->read = j;
      productAfd->transitions[currentTransitionIndex] = transition;
      currentTransitionIndex++;
    }
    freeSplit(splitted);
  }

  return productAfd;
}