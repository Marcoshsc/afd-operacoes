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

void readInt(int *int_ptr, FILE *file)
{
  int value;
  fscanf(file, "%d\n", &value);
  *int_ptr = value;
}

void readString(char **str_ptr, FILE *file)
{
  char buffer[100];
  fscanf(file, "%s\n", buffer);
  *str_ptr = malloc(sizeof(char) * (strlen(buffer) + 1));
  strcpy(*str_ptr, buffer);
}

void readChars(char ***list_ptr, int *size_ptr, FILE *file)
{
  readInt(size_ptr, file);
  *list_ptr = malloc(sizeof(char *) * (*size_ptr));
  for (int i = 0; i < (*size_ptr); i++)
  {
    readString(&(*list_ptr)[i], file);
  }
}

void readTransitions(AFD *afd, FILE *file)
{
  readInt(&afd->number_transitions, file);
  afd->transitions = malloc(sizeof(Transition *) * afd->number_transitions);
  for (int i = 0; i < afd->number_transitions; i++)
  {
    char buffer1[100], buffer2[100], buffer3[100];
    fscanf(file, "%s %s %s\n", buffer1, buffer2, buffer3);

    int fromPosition = getStatePosition(*afd, buffer1);
    int readPosition = getSymbolPosition(*afd, buffer2);
    int toPosition = getStatePosition(*afd, buffer3);

    Transition *transition = malloc(sizeof(Transition));
    transition->from = fromPosition;
    transition->read = readPosition;
    transition->to = toPosition;
  }
}

void readInitialState(AFD *afd, FILE *file)
{
  char buffer[100];
  fscanf(file, "%s\n", buffer);
  int statePosition = getStatePosition(*afd, buffer);
  afd->initial_state = statePosition;
}

void readFinalStates(AFD *afd, FILE *file)
{
  readInt(&afd->number_final_states, file);
  afd->final_states = malloc(sizeof(int *) * afd->number_final_states);
  for (int i = 0; i < afd->number_final_states; i++)
  {
    char buffer[100];
    fscanf(file, "%s\n", buffer);
    int statePosition = getStatePosition(*afd, buffer);
    afd->final_states[i] = statePosition;
    printf("%d\n", afd->final_states[i]);
  }
}

AFD *readAFD(char *fileName)
{
  FILE *file = fopen(fileName, "r");
  if (!file)
  {
    return NULL;
  }
  AFD *afd = malloc(sizeof(AFD));
  readChars(&afd->states, &afd->number_states, file);
  readChars(&afd->alphabet, &afd->number_symbols, file);
  readTransitions(afd, file);
  readInitialState(afd, file);
  readFinalStates(afd, file);

  free(afd);
  return NULL;
}
