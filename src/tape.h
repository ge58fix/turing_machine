#ifndef INFO_H
#define INFO_H

typedef struct Tape
{
   char content;
   struct Tape *prev;
   struct Tape *next;
};
#endif
