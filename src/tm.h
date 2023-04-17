#ifndef INFO_H
#define INFO_H
#include "transitions.h"

typedef struct tm
{
    char *input_alphabet;
    char *tape_alphabet;
    char *current_state;
    Transitions *head;
    
} Turing_Machine;

int create_tm(char*, Turing_Machine*);
#endif