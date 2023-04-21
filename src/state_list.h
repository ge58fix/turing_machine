typedef struct state_list
{
    char state[16];
    struct state_list *next;
} State_List;



State_List *insert_state(State_List* h, char* state);
int accept(State_List *h, char* state);