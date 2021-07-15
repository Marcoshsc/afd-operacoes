#include <stdlib.h>
#include "../operations.h"
#include "../../string/stringutil.h"

char **getDoubleCircles(AFD *afd)
{
  char **double_circles = malloc(sizeof(char *) * (*afd->number_final_states));
  for (int i = 0; i < *afd->number_final_states; i++)
  {
    double_circles[i] = copyString(afd->states[afd->final_states[i]]);
  }
  return double_circles;
}

DOTTransition *getSingleTransition(AFD *afd, Transition *transition)
{
  char *from = afd->states[*transition->from];
  char *to = afd->states[*transition->to];
  char *read = afd->alphabet[*transition->read];

  DOTTransition *dotTransition = getDOTTransition(from, to, read);
  return dotTransition;
}

DOTTransition **getTransitionArray(AFD *afd)
{
  int size = *afd->number_transitions;
  DOTTransition **transitions = malloc(sizeof(DOTTransition *) * size);
  for (int i = 0; i < size; i++)
  {
    DOTTransition *transition = getSingleTransition(afd, afd->transitions[i]);
    transitions[i] = transition;
  }
  return transitions;
}

DOTFormat *visualizacao(AFD *afd)
{
  char **double_circles = getDoubleCircles(afd);
  DOTTransition **transitions = getTransitionArray(afd);
  DOTFormat *dotFormat = getDOTFormat(double_circles, *afd->number_final_states, transitions, *afd->number_transitions);
  return dotFormat;
}
