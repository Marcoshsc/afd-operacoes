#include <stdio.h>

typedef struct transition_est
{
  char *from;
  char *symbol;
  char *to;
} Transition;

typedef struct afd_est
{
  int n_states;
  char **states;
  int n_symbols;
  char **symbols;
  int n_transitions;
  Transition **transitions;
  char *initial_state;
  int n_final_states;
  char **final_states;
} AFD;
