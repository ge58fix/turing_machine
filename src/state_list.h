typedef struct state_list
{
    char state[16];
    struct state_list *next;
    struct state_list *prev;
} State_List;



State_List *insert_state(State_List*, char*);