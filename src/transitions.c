#include "transitions.h"
#include <stdio.h>
#include <stdlib.h>

Transitions add(Transitions *head, Transition *t) {
   Transitions *link = (Transitions*) malloc(sizeof(Transitions));
	
   link->transition = t;
   link->next = head;
   link->prev = NULL;
   if (head->transition == NULL) {
    head = (Transitions*) malloc(sizeof(Transitions));
    return *link;
   }
   head->prev = link;
   return *link;
}