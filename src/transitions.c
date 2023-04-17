#include "transitions.h"
#include <stdio.h>
#include <stdlib.h>

Transitions add(Transitions *head, Transition *t) {
   Transitions *link = (Transitions*) calloc(1, sizeof(Transitions));
	
   link->transition = t;
   link->next = head;
   link->prev = NULL; // obsolete due to calloc?
   if (head->transition == NULL) {
    head = (Transitions*) calloc(1, sizeof(Transitions));
    return *link;
   }
   head->prev = link;
   return *link;
}