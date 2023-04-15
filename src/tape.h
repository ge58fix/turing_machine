#ifndef INFO_H
#define INFO_H

typedef struct tape
{
   char content;
   struct tape *prev;
   struct tape *next;
} Tape;
#endif

Tape create_tape(char*);
Tape *tape_add(Tape*, char, char) {

}

