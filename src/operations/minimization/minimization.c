#include "../recognition/recognition.h"
#include "../../strings/stringutil.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int isContained(int *values, int value, int size)
{
  for (int i = 0; i < size; i++)
  {
    if (value == values[i])
    {
      return 1;
    }
  }
  return 0;
}

int getEquivalenceGroup(int **groups, int groupsSize, int *sizes, int value)
{
  for (int i = 0; i < groupsSize; i++)
  {
    for (int j = 0; j < sizes[i]; j++)
    {
      if (groups[i][j] == value)
      {
        return i;
      }
    }
  }
  return -1;
}

char *mergeStates(AFD *afd, int *states, int size)
{
  int numberSeparators = size - 1;
  int currentSize = numberSeparators + 1;
  char *newState = malloc(sizeof(char) * currentSize);
  int currentIndex = 0;
  for (int i = 0; i < size; i++)
  {
    int stateIndex = states[i];
    char *state = afd->states[stateIndex];
    int stateLength = strlen(state);
    currentSize += stateLength;
    newState = realloc(newState, sizeof(char) * currentSize);
    for (int j = 0; j < stateLength; j++)
    {
      newState[currentIndex] = state[j];
      currentIndex++;
    }
    if (i != size - 1)
    {
      newState[currentIndex] = '_';
      currentIndex++;
    }
  }
  newState[currentIndex] = '\0';
  return newState;
}

Transition *getTransitionFromIndexes(AFD *afd, int from, int read)
{
  for (int i = 0; i < *afd->number_transitions; i++)
  {
    if (*afd->transitions[i]->from == from && *afd->transitions[i]->read == read)
    {
      return afd->transitions[i];
    }
  }
  return NULL;
}

void updateReachableList(AFD *afd, int **reachables, int *reachableSize, int element)
{
  for (int i = 0; i < *afd->number_symbols; i++)
  {
    Transition *transition = getTransitionFromIndexes(afd, element, i);
    if (!isContained(*reachables, *transition->to, *reachableSize))
    {
      (*reachableSize)++;
      *reachables = realloc(*reachables, *reachableSize);
      (*reachables)[(*reachableSize) - 1] = *transition->to;
      updateReachableList(afd, reachables, reachableSize, *transition->to);
    }
  }
}

AFD *copyAFDWithoutUnreachableStates(AFD *afd)
{
  AFD *newAfd = getEmptyAFD();
  int *reachables = malloc(sizeof(int));
  int reachableSize = 1;
  reachables[0] = *afd->initial_state;
  updateReachableList(afd, &reachables, &reachableSize, *afd->initial_state);

  *newAfd->number_states = reachableSize;
  newAfd->states = malloc(sizeof(char *) * reachableSize);
  newAfd->final_states = malloc(sizeof(int));
  int finalStateAllocSize = 1;
  int finalStates = 0;
  for (int i = 0; i < reachableSize; i++)
  {
    char *state = afd->states[reachables[i]];
    newAfd->states[i] = copyString(state);
    if (isContained(afd->final_states, reachables[i], *afd->number_final_states))
    {
      if (finalStateAllocSize == finalStates)
      {
        finalStateAllocSize++;
        newAfd->final_states = realloc(newAfd->final_states, sizeof(int) * finalStateAllocSize);
      }
      newAfd->final_states[finalStates] = i;
      finalStates++;
    }
  }
  *newAfd->number_final_states = finalStates;

  int numberTransitions = 0;
  int allocSize = 1;
  newAfd->transitions = malloc(sizeof(Transition *));
  for (int i = 0; i < reachableSize; i++)
  {
    int element = reachables[i];
    for (int j = 0; j < *afd->number_transitions; j++)
    {
      Transition *transition = afd->transitions[j];
      if (*transition->to == element)
      {
        Transition *newTransition = getEmptyTransition();
        char *state = afd->states[*transition->from];
        int position = getStatePosition(*newAfd, state);
        *newTransition->from = position;
        *newTransition->read = *transition->read;
        *newTransition->to = i;
        if (allocSize == numberTransitions)
        {
          allocSize++;
          newAfd->transitions = realloc(newAfd->transitions, sizeof(Transition *) * allocSize);
        }
        newAfd->transitions[numberTransitions] = newTransition;
        numberTransitions++;
      }
    }
  }
  *newAfd->number_transitions = numberTransitions;

  *newAfd->number_symbols = *afd->number_symbols;
  newAfd->alphabet = malloc(sizeof(char *) * (*newAfd->number_symbols));
  for (int i = 0; i < *newAfd->number_symbols; i++)
  {
    newAfd->alphabet[i] = copyString(afd->alphabet[i]);
  }
  *newAfd->initial_state = *afd->initial_state;

  return newAfd;
}

AFD *minimizacao(AFD *initialAfd)
{
  AFD *afd = copyAFDWithoutUnreachableStates(initialAfd);

  printf("%d\n", *afd->number_transitions);
  for (int i = 0; i < *afd->number_transitions; i++)
  {
    Transition *transition = afd->transitions[i];
    printf("From %d to %d, reading %d\n", *transition->from, *transition->to, *transition->read);
    printf("From %s to %s, reading %s\n\n", afd->states[*transition->from], afd->states[*transition->to], afd->alphabet[*transition->read]);
  }

  int **equivalenceGroups = malloc(sizeof(int *) * 2);
  int *sizes = malloc(sizeof(int) * 2);
  sizes[0] = *afd->number_final_states;
  sizes[1] = *afd->number_states - (*afd->number_final_states);
  int totalGroups = !sizes[0] || !sizes[1] ? 1 : 2;
  equivalenceGroups[0] = sizes[0] ? malloc(sizeof(int) * sizes[0]) : NULL;
  equivalenceGroups[1] = sizes[1] ? malloc(sizeof(int) * sizes[1]) : NULL;

  if (!sizes[0])
  {
    sizes[0] = sizes[1];
    equivalenceGroups[0] = equivalenceGroups[1];
  }

  for (int i = 0; i < *afd->number_final_states; i++)
  {
    equivalenceGroups[0][i] = afd->final_states[i];
  }
  int currentStartStateIndex = 0;
  for (int i = 0; i < *afd->number_states; i++)
  {
    if (isContained(afd->final_states, i, *afd->number_final_states))
    {
      continue;
    }
    equivalenceGroups[1][currentStartStateIndex] = i;
    currentStartStateIndex++;
  }
  int changed = 0;
  do
  {
    if (!sizes[0] || !sizes[1])
    {
      break;
    }
    changed = 0;
    for (int i = 0; i < totalGroups; i++)
    {
      int *x = NULL;
      int xSize = 0;

      int element = equivalenceGroups[i][0];
      int *elementEquivalenceGroups = malloc(sizeof(int) * (*afd->number_symbols));
      for (int k = 0; k < *afd->number_symbols; k++)
      {
        char *state = transitionFunction(afd, afd->alphabet[k], afd->states[element]);
        int stateIndex = getStatePosition(*afd, state);
        int group = getEquivalenceGroup(equivalenceGroups, totalGroups, sizes, stateIndex);
        elementEquivalenceGroups[k] = group;
      }

      for (int j = 0; j < sizes[i]; j++)
      {
        for (int l = 0; l < *afd->number_symbols; l++)
        {
          char *state = transitionFunction(afd, afd->alphabet[l], afd->states[equivalenceGroups[i][j]]);
          int stateIndex = getStatePosition(*afd, state);
          int group = getEquivalenceGroup(equivalenceGroups, totalGroups, sizes, stateIndex);
          if (group != elementEquivalenceGroups[l])
          {
            xSize++;
            if (!xSize)
            {
              x = malloc(sizeof(int));
            }
            else
            {
              x = realloc(x, sizeof(int) * xSize);
            }
            x[xSize - 1] = equivalenceGroups[i][j];
            for (int k = j; k < sizes[i] - 1; k++)
            {
              equivalenceGroups[i][k] = equivalenceGroups[i][k + 1];
            }
            sizes[i]--;
            break;
          }
        }
      }
      if (xSize)
      {
        changed = 1;
        totalGroups++;
        equivalenceGroups = realloc(equivalenceGroups, sizeof(int *) * totalGroups);
        equivalenceGroups[totalGroups - 1] = x;
        sizes = realloc(sizes, sizeof(int) * totalGroups);
        sizes[totalGroups - 1] = xSize;
      }
    }
  } while (changed);

  AFD *newAfd = getEmptyAFD();
  *newAfd->number_states = totalGroups;
  newAfd->states = malloc(sizeof(char *) * totalGroups);
  for (int i = 0; i < totalGroups; i++)
  {
    newAfd->states[i] = mergeStates(afd, equivalenceGroups[i], sizes[i]);
  }
  *newAfd->number_symbols = *afd->number_symbols;
  newAfd->alphabet = malloc(sizeof(char *) * (*afd->number_symbols));
  for (int i = 0; i < *afd->number_symbols; i++)
  {
    newAfd->alphabet[i] = copyString(afd->alphabet[i]);
  }

  int initialState = getEquivalenceGroup(equivalenceGroups, totalGroups, sizes, *afd->initial_state);
  *newAfd->initial_state = initialState;

  newAfd->final_states = malloc(sizeof(int));
  int allocatedSize = 1;
  int totalFinalStates = 0;

  for (int i = 0; i < totalGroups; i++)
  {
    int contained = 1;
    for (int j = 0; j < sizes[i]; j++)
    {
      int element = equivalenceGroups[i][j];
      if (!isContained(afd->final_states, element, *afd->number_final_states))
      {
        contained = 0;
        break;
      }
    }
    if (contained)
    {
      if (totalFinalStates == allocatedSize)
      {
        allocatedSize++;
        newAfd->final_states = realloc(newAfd->final_states, sizeof(int) * allocatedSize);
      }
      newAfd->final_states[totalFinalStates] = i;
      totalFinalStates++;
    }
  }
  *newAfd->number_final_states = totalFinalStates;

  int numberTransitions = *newAfd->number_states * (*afd->number_symbols);
  newAfd->transitions = malloc(sizeof(Transition *) * numberTransitions);
  *newAfd->number_transitions = numberTransitions;
  int currentTransitionIndex = 0;
  for (int i = 0; i < totalGroups; i++)
  {
    if (!sizes[i])
    {
      continue;
    }
    for (int j = 0; j < *afd->number_symbols; j++)
    {
      Transition *transition = getEmptyTransition();
      *transition->from = i;
      char *state = transitionFunction(afd, afd->alphabet[j], afd->states[equivalenceGroups[i][0]]);
      int stateIndex = getStatePosition(*afd, state);
      int group = getEquivalenceGroup(equivalenceGroups, totalGroups, sizes, stateIndex);
      *transition->to = group;
      *transition->read = j;
      newAfd->transitions[currentTransitionIndex] = transition;
      currentTransitionIndex++;
    }
  }

  for (int i = 0; i < totalGroups; i++)
  {
    free(equivalenceGroups[i]);
  }
  free(equivalenceGroups);
  free(sizes);

  freeAFD(afd);
  printf("%d\n", *newAfd->number_transitions);
  printf("%d\n", *newAfd->number_states);
  for (int i = 0; i < *newAfd->number_transitions; i++)
  {
    Transition *transition = newAfd->transitions[i];
    printf("%d - %d - %d\n", *transition->from, *transition->to, *transition->read);
  }

  puts("here");
  return newAfd;
}
