#include "transition.h"
typedef struct transitions
{
    struct transition *transition;
    struct transitions *next;
} Transitions;



Transitions *add(Transitions*, Transition*);
Transition *get_transition(Transitions* head, const char* state, char symbol);

