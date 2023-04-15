#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "tape.h"

Tape create_tape(char *input) {
    int len = strlen(input);
    Tape *t = calloc(1, sizeof(Tape));
    for (int i = 0; i < len; i++) {
        t = tape_add(t, '>', input[i]);
    }
    return t;
}

Tape tape_add(Tape *t, char direction, char input) {
    Tape *head = t;
    Tape *t_new = calloc(1, sizeof(Tape));
    t->content = input;
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