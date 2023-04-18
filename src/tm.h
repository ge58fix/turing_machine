#ifndef INFO_H
#define INFO_H
#include "transitions.h"
#include "state_list.h"

typedef struct tm
{
    char input_alphabet[32];
    char tape_alphabet[32];
    char current_state[16];
    State_List *accepted_states;
    Transitions *head;
} Turing_Machine;

int create_tm(char*, Turing_Machine*);
int validate(char*, const char*);
void simulate(Turing_Machine *tm, char* input);
#endif