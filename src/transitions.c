#include "transitions.h"
#include <stdlib.h>
#include <string.h>

Transitions *add(Transitions *h, Transition *t) {
   Transitions *link = (Transitions*) calloc(1, sizeof(Transitions));
    Transitions * head = h;
    if (head->transition == NULL) {
        head->transition = t;
        return h;
    }
    while(head->next != NULL) {
        head = head->next;
    }
    link->transition = t;
    link->next = NULL;
    link->prev = head;
    head->next = link;
    return h;
}

Transition *get_transition(Transitions* head, const char* state, char symbol) {
    Transition *t;
    while(1) {
        if(head==NULL) return NULL;
        t = head->transition;
        if(t->current_state == state && t->symbol == symbol)
            return t;
        head = head->next;
    }
}