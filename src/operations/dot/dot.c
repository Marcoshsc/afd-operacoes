#include <stdlib.h>
#include "../../strings/stringutil.h"
#include "./dot.h"

void writeDot(DOTFormat *dotFormat, char *fileName)
{
  FILE *file = fopen(fileName, "w");
  if (!file)
  {
    return;
  }
  fprintf(file, "digraph finite_state_machine {\nrankdir=LR;\nsize=\"8,5\"\nnode [shape = doublecircle]; ");
  for (int i = 0; i < dotFormat->number_double_circles; i++)
  {
    fprintf(file, "\"%s\" ", dotFormat->double_circles[i]);
  }
  fprintf(file, ";\nnode [shape = circle];\ninit [shape = point];\n");
  fprintf(file, "init -> \"%s\";\n", dotFormat->initial_state);
  for (int i = 0; i < dotFormat->number_transitions; i++)
  {
    DOTTransition *element = dotFormat->transitions[i];
    fprintf(file, "\"%s\" -> \"%s\" [label = \"%s\"];\n", element->from, element->to, element->label);
  }
  fprintf(file, "}");
}

DOTTransition *getDOTTransition(char *from, char *to, char *label)
{
  DOTTransition *transition = malloc(sizeof(DOTTransition));
  transition->from = copyString(from);
  transition->to = copyString(to);
  transition->label = copyString(label);
  return transition;
}

DOTFormat *getDOTFormat(char **double_circles, int number_double_circles, DOTTransition **transitions, int number_transitions, char *initial_state)
{
  DOTFormat *dotFormat = malloc(sizeof(DOTFormat));
  dotFormat->double_circles = double_circles;
  dotFormat->number_double_circles = number_double_circles;
  dotFormat->transitions = transitions;
  dotFormat->number_transitions = number_transitions;
  dotFormat->initial_state = initial_state;
  return dotFormat;
}

void freeDotTransition(DOTTransition *transition)
{
  free(transition->from);
  free(transition->to);
  free(transition->label);
  free(transition);
}

void freeDot(DOTFormat *dotFormat)
{
  for (int i = 0; i < dotFormat->number_transitions; i++)
  {
    freeDotTransition(dotFormat->transitions[i]);
  }
  for (int i = 0; i < dotFormat->number_double_circles; i++)
  {
    free(dotFormat->double_circles[i]);
  }
  free(dotFormat->double_circles);
  free(dotFormat->transitions);
  free(dotFormat);
}
