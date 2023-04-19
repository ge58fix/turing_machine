#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tape.h"

Tape* create_tape(char *input) {
    int len = (int)strlen(input);
    Tape *t = calloc(1, sizeof(Tape));
    for (int i = 0; i < len; i++) {
        t = tape_add(t, '>', input[i]);
    }
    return t;
}

Tape* tape_add(Tape *t, char direction, char input) {
    Tape *head = t;
    if (head->content == '\0') {
        head->content = input;
        return head;
    }
    Tape *t_new = calloc(1, sizeof(Tape));
    t_new->content = input;
    if (direction == '<') {
        while (t->prev != NULL) {
            t = t->prev;
        }
        t_new->next = t;
        t_new->prev = NULL;
        t->prev = t_new;
        return t_new;
    }
    else if (direction == '>') {
        while (t->next != NULL) {
            t = t->next;
        }
        t_new->prev = t;
        t_new->next = NULL;
        t->next = t_new;
    }
    return head;
}

Tape* move(Tape *t, char dir, char blank) {
    if (dir == '<') {
        if (t->prev == NULL) {
            t = tape_add(t, '<', blank);
        }
        return t->prev;
    }
    if (dir == '>') {
        if (t->next == NULL) {
            t = tape_add(t, '>', blank);
        }
        return t->next;
    }
    return NULL;
}

void tape_print(Tape* head) {
    Tape* h = head;
    printf("|%c|", h->content);
    while(h->next != NULL) {
        h = h->next;
        printf("%c|", h->content);
    }
    printf("\n");
}