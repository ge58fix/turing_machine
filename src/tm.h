#ifndef INFO_H
#define INFO_H
#include "transitions.h"

typedef struct tm
{
    char input_alphabet[32];
    char tape_alphabet[32];
    char current_state[16];
    Transitions *head;
    
} Turing_Machine;

int create_tm(char*, Turing_Machine*);
int validate(char*, char*);
#endif