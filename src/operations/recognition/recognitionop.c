#include "../../strings/stringutil.h"
#include "./recognition.h"
#include <string.h>
#include <stdlib.h>

char *transitionFunction(AFD *afd, char *symbol, char *current_state)
{
  for (int i = 0; i < *afd->number_transitions; i++)
  {
    Transition *transition = afd->transitions[i];
    char *fromState = afd->states[*transition->from];
    char *read = afd->alphabet[*transition->read];
    if (!strcmp(current_state, fromState) && !strcmp(symbol, read))
    {
      return afd->states[*transition->to];
    }
  }
}

char *extendedTransitionFunction(AFD *afd, char *word, char *current_state)
{
  int size = strlen(word);
  if (size == 0)
  {
    return current_state;
  }
  else
  {
    char symbol[2] = {word[size - 1], '\0'};
    char *copy = copyString(word);
    copy[size - 1] = '\0';
    char *state = transitionFunction(afd, symbol, extendedTransitionFunction(afd, copy, current_state));
    free(copy);
    return state;
  }
}

int isFinalState(AFD *afd, char *state)
{
  for (int i = 0; i < *afd->number_final_states; i++)
  {
    char *finalState = afd->states[afd->final_states[i]];
    if (!strcmp(finalState, state))
      return 1;
  }
  return 0;
}

int *reconhecer(AFD *afd, char **words, int size)
{
  int *results = calloc(size, sizeof(int));
  for (int i = 0; i < size; i++)
  {
    char *initial_state = afd->states[*afd->initial_state];
    char *wordCopy = copyString(words[i]);
    char *state = extendedTransitionFunction(afd, wordCopy, initial_state);
    results[i] = isFinalState(afd, state);
    free(wordCopy);
  }
  return results;
}