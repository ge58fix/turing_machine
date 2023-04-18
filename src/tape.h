typedef struct tape
{
   char content;
   struct tape *prev;
   struct tape *next;
} Tape;

Tape* create_tape(char* input);
Tape* tape_add(Tape* tape, char direction, char input);
Tape* move(Tape *t, char dir, char blank);

