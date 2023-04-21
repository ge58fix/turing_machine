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

int create_tm(char* filename, Turing_Machine* tm);
int validate(char* input_alpha, const char* input);
void simulate(Turing_Machine *tm, char* input);
void free_all(Turing_Machine *tm);