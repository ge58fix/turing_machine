#ifndef INFO_H
#define INFO_H

typedef struct transition
{
    char *current_state;
    char *next_state;
    char *symbol;
    char *write_symbol;
    char direction;
} Transition;
#endif