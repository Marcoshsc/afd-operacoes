#include <stdio.h>
#define DOT_H

typedef struct dotformat_transition_est
{
  char *from;
  char *to;
  char *label;
} DOTTransition;

typedef struct dotformat_est
{
  char **double_circles;
  int number_double_circles;
  int number_transitions;
  DOTTransition **transitions;
} DOTFormat;

DOTTransition *getDOTTransition(char *from, char *to, char *label);
DOTFormat *getDOTFormat(char **double_circles, int number_double_circles, DOTTransition **transitions, int number_transitions);
void freeDotTransition(DOTTransition *transition);
void freeDot(DOTFormat *DOTFormat);
void writeDot(DOTFormat *DOTFormat, char *fileName);