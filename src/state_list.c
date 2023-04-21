#include "state_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

State_List *insert_state(State_List* h, char* state) {
    State_List* elem = calloc(1, sizeof(State_List));
    char* p;
    if ((p = strchr(state, '\n')) != NULL) {
        p[0] = '\0';
    }
    if (h->state[0] == '\0') {
        snprintf(elem->state, sizeof (elem->state), "%s", state);
        return elem;
    }
    State_List* head = h;
    while(head->next != NULL) {
        head = head->next;
    }
    snprintf(elem->state, sizeof (elem->state), "%s", state);
    elem->next = NULL;
    head->next = elem;
    return h;
}

int accept(State_List *h, char* state) {
    if (strcmp(h->state, state) == 0) {
        return 1;
    }
        while (h->next != NULL) {
        if (strcmp(h->state, state) == 0) {
            return 1;
        }
        h = h->next;
    }
    return 0;
}

