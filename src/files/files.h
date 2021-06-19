#include <stdio.h>
#include "../afd/afd.h"

#ifndef FILES_H
#define FILES_H

AFD *readAfd(char *fileName);
void read_states(FILE *file, AFD *afd);
void read_alphabet(FILE *file, AFD *afd);
void read_transitions(FILE *file, AFD *afd);
Transition *read_transition(FILE *file);
void read_initial_state(FILE *file, AFD *afd);
void read_final_states(FILE *file, AFD *afd);

#endif