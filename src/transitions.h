#include "transition.h"
typedef struct transitions
{
    struct transition *transition;
    struct transitions *next;
    struct transitions *prev;
} Transitions;



Transitions add(Transitions*, Transition*);

