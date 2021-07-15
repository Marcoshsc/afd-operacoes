#include <stdlib.h>
#include <string.h>
#include "./filter.h"

void filterTransitions(DOTFormat *dotFormat)
{
  int size = dotFormat->number_transitions;
  int removed[size];
  for (int i = 0; i < size; i++)
  {
    removed[i] = 0;
  }

  int indexes[size];
  int indexesSize = 0;
  int newSize = 0;
  DOTTransition *newTransitions[size];
  for (int i = 0; i < size; i++)
  {
    if (removed[i])
      continue;
    DOTTransition *outerTransition = dotFormat->transitions[i];
    int labelSize = strlen(outerTransition->label + 1);
    for (int j = 0; j < size; j++)
    {
      if (i == j || removed[j])
        continue;
      DOTTransition *innerTransition = dotFormat->transitions[j];
      if (!strcmp(outerTransition->from, innerTransition->from) && !strcmp(outerTransition->to, innerTransition->to))
      {
        indexes[indexesSize] = j;
        indexesSize++;
        removed[j] = 1;
        labelSize += strlen(innerTransition->label + 2);
      }
    }

    if (indexesSize)
    {
      char *newLabel = malloc(sizeof(char) * labelSize);
      sprintf(newLabel, "%s, ", outerTransition->label);
      free(outerTransition->label);
      int currentSize = strlen(newLabel);
      for (int k = 0; k < indexesSize; k++)
      {
        DOTTransition *transition = dotFormat->transitions[indexes[k]];
        for (int j = 0; j < strlen(transition->label); j++, currentSize++)
        {
          newLabel[currentSize] = transition->label[j];
        }
        if (k != indexesSize - 1)
        {
          newLabel[currentSize] = ',';
          newLabel[currentSize + 1] = ' ';
          currentSize += 2;
        }
        freeDotTransition(transition);
      }
      newLabel[currentSize] = '\0';
      outerTransition->label = newLabel;
      newTransitions[newSize] = outerTransition;
      newSize++;
    }
    else
    {
      newTransitions[newSize] = outerTransition;
      newSize++;
    }

    removed[i] = 1;
    indexesSize = 0;
  }
  DOTTransition **newTransitionsPointer = malloc(sizeof(DOTTransition *) * newSize);
  for (int i = 0; i < newSize; i++)
  {
    newTransitionsPointer[i] = newTransitions[i];
  }
  free(dotFormat->transitions);
  dotFormat->transitions = newTransitionsPointer;
  dotFormat->number_transitions = newSize;
}