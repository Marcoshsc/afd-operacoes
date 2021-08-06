#include "../operations.h"
#include <stdlib.h>
#include "../../strings/stringutil.h"

AFD *complemento(AFD *afd)
{
  AFD *newAfd = getEmptyAFD();
  newAfd->states = malloc((*afd->number_states) * sizeof(char *));
  for (int i = 0; i < *afd->number_states; i++)
  {
    char *state = afd->states[i];
    char *stateCopy = copyString(state);
    newAfd->states[i] = stateCopy;
  }
  *newAfd->number_states = *afd->number_states;

  newAfd->alphabet = malloc((*afd->number_symbols) * sizeof(char *));
  for (int i = 0; i < *afd->number_symbols; i++)
  {
    char *symbol = afd->alphabet[i];
    char *symbolCopy = copyString(symbol);
    newAfd->alphabet[i] = symbolCopy;
  }
  *newAfd->number_symbols = *afd->number_symbols;

  newAfd->transitions = malloc((*afd->number_transitions) * sizeof(Transition *));
  for (int i = 0; i < *afd->number_transitions; i++)
  {
    Transition *transition = afd->transitions[i];
    Transition *newTransition = getEmptyTransition();
    *newTransition->from = *transition->from;
    *newTransition->to = *transition->to;
    *newTransition->read = *transition->read;
    newAfd->transitions[i] = newTransition;
  }
  *newAfd->number_transitions = *afd->number_transitions;
  *newAfd->initial_state = *afd->initial_state;

  int numberFinalStates = (*afd->number_states) - (*afd->number_final_states);
  newAfd->final_states = malloc(sizeof(int) * numberFinalStates);
  *newAfd->number_final_states = numberFinalStates;
  int currentFinalState = 0;
  for (int i = 0; i < *afd->number_states; i++)
  {
    int isFinal = 0;
    for (int j = 0; j < *afd->number_final_states; j++)
    {
      int finalState = afd->final_states[j];
      if (i == finalState)
      {
        isFinal = 1;
        break;
      }
    }
    if (!isFinal)
    {
      newAfd->final_states[currentFinalState] = i;
      currentFinalState++;
    }
  }

  return newAfd;
}