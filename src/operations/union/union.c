#include "../product/product.h"
#include <stdlib.h>
#include <stdio.h>

int isAfdFinalState(AFD *afd, int index)
{
  for (int i = 0; i < *afd->number_final_states; i++)
  {
    if (index == afd->final_states[i])
      return 1;
  }
  return 0;
}

AFD *uniao(AFD *afd1, AFD *afd2)
{
  AFD *product = afdProduct(afd1, afd2);
  int numberFinalStates = ((*afd1->number_final_states) * (*afd2->number_states)) +
                          ((*afd2->number_final_states) * (*afd1->number_states)) - (*afd1->number_final_states * (*afd2->number_final_states));
  product->final_states = malloc(sizeof(int) * numberFinalStates);
  *product->number_final_states = numberFinalStates;
  int currentIndex = 0;
  for (int i = 0; i < *afd1->number_final_states; i++)
  {
    int finalState = afd1->final_states[i];
    int startingPoint = finalState * (*afd2->number_states);
    for (int j = 0; j < *afd2->number_states; j++)
    {
      int index = startingPoint + j;
      product->final_states[currentIndex] = index;
      currentIndex++;
    }
  }

  for (int i = 0; i < *afd2->number_final_states; i++)
  {
    int finalState = afd2->final_states[i];
    for (int j = 0; j < *afd1->number_states; j++)
    {
      int index = (j * (*afd2->number_states)) + finalState;
      if (isAfdFinalState(afd1, j))
      {
        continue;
      }
      product->final_states[currentIndex] = index;
      currentIndex++;
    }
  }

  return product;
}