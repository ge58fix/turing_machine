

typedef struct transition
{
    char current_state[16];
    char next_state[16];
    char symbol;
    char write_symbol;
    char direction;
} Transition;

