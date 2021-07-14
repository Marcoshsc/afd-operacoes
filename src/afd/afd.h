#include <stdio.h>

typedef struct transition_est
{
  int *from;
  int *read;
  int *to;
} Transition;

typedef struct afd_est
{

  char **states;
  int *number_states;

  char **alphabet;
  int *number_symbols;

  int *initial_state;

  int *final_states;
  int *number_final_states;

  Transition **transitions;
  int *number_transitions;

} AFD;

Transition *getTransition(AFD afd, char *from, char *to, char *read);
int getStatePosition(AFD afd, char *state);
int getSymbolPosition(AFD afd, char *symbol);
AFD *getEmptyAFD();
AFD *readAFD(char *fileName);
void writeAFD(AFD afd, char *fileName);
void freeAFD(AFD *afd);