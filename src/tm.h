#ifndef INFO_H
#define INFO_H
#include "transitions.h"

typedef struct tm
{
    char *alphabet;
    char *current_state;
    Transitions *head;
    
} TURING_MACHINE;

int create_tm(char*);
#endif