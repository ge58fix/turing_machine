#ifndef INFO_H
#define INFO_H

typedef struct tape
{
   char content;
   struct tape *prev;
   struct tape *next;
} Tape;
#endif
