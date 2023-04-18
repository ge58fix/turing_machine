typedef struct transition
{
    char current_state[16];
    char next_state[16];
    char symbol[16];
    char write_symbol[16];
    char direction;
} Transition;
