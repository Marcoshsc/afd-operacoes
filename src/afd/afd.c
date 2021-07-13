#include <stdlib.h>
#include <string.h>
#include "./afd.h"

Transition *getTransition(AFD afd, char *from, char *to, char *read)
{
  int fromPosition = getStatePosition(afd, from);
  int toPosition = getStatePosition(afd, to);
  int readPosition = getSymbolPosition(afd, read);
  Transition *transition = malloc(sizeof(Transition));
  transition->from = fromPosition;
  transition->to = toPosition;
  transition->read = readPosition;
  return transition;
}

int getStatePosition(AFD afd, char *state)
{
  for (int i = 0; i < afd.number_states; i++)
  {
    if (!strcmp(afd.states[i], state))
      return i;
  }
  return -1;
}

int getSymbolPosition(AFD afd, char *symbol)
{
  for (int i = 0; i < afd.number_symbols; i++)
  {
    if (!strcmp(afd.alphabet[i], symbol))
      return i;
  }
  return -1;
}

AFD *getAFD(char **states, int number_states, char **alphabet, int number_symbols, int initial_state,
            int *final_states, int number_final_states, Transition **transitions)
{
  AFD *afd = malloc(sizeof(AFD));
  afd->states = states;
  afd->number_states = number_states;
  afd->alphabet = alphabet;
  afd->number_symbols = number_symbols;
  afd->initial_state = initial_state;
  afd->final_states = final_states;
  afd->number_final_states = number_final_states;
  afd->transitions = transitions;
  return afd;
}
