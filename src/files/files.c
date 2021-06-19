#include <stdio.h>
#include <stdlib.h>
#include "files.h"

AFD *readAfd(char *file_name)
{
  FILE *file = fopen(file_name, "r");
  AFD *afd = malloc(sizeof(AFD));
  read_states(file, afd);
  read_alphabet(file, afd);
  read_transitions(file, afd);
  read_initial_state(file, afd);
  read_final_states(file, afd);
  return afd;
}

void read_final_states(FILE *file, AFD *afd)
{
  int n_final_states;
  fscanf(file, "%d\n", &n_final_states);
  char **final_states = malloc(sizeof(char *) * n_final_states);
  for (int i = 0; i < n_final_states; i++)
  {
    fscanf(file, "%s\n", final_states[i]);
  }
  afd->final_states = final_states;
  afd->n_final_states = n_final_states;
}

void read_initial_state(FILE *file, AFD *afd)
{
  char *initial_state;
  fscanf(file, "%s\n", initial_state);
  afd->initial_state = initial_state;
}

void read_transitions(FILE *file, AFD *afd)
{
  int n_transitions;
  fscanf(file, "%d\n", &n_transitions);
  Transition **transitions = malloc(sizeof(Transition *) * n_transitions);
  for (int i = 0; i < n_transitions; i++)
  {
    Transition *transition = read_transition(file);
    transitions[i] = transition;
  }
  afd->transitions = transitions;
  afd->n_transitions = n_transitions;
}

Transition *read_transition(FILE *file)
{
  Transition *transition = malloc(sizeof(Transition));
  fscanf(file, "%s ", transition->from);
  fscanf(file, "%s ", transition->symbol);
  fscanf(file, "%s\n", transition->to);
  return transition;
}

void read_alphabet(FILE *file, AFD *afd)
{
  int n_symbols;
  fscanf(file, "%d\n", &n_symbols);
  char **symbols = malloc(n_symbols * sizeof(char *));
  for (int i = 0; i < n_symbols; i++)
  {
    fscanf(file, "%s\n", symbols[i]);
  }
  afd->n_symbols = n_symbols;
  afd->symbols = symbols;
}

void read_states(FILE *file, AFD *afd)
{
  int n_states;
  fscanf(file, "%d\n", &n_states);
  char **states = malloc(sizeof(char *) * n_states);
  for (int i = 0; i < n_states; i++)
  {
    fscanf(file, "%s\n", states[i]);
  }
  afd->n_states = n_states;
  afd->states = states;
}
