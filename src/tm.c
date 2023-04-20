#include <stdio.h>
#include <stdlib.h>
#include "tm.h"
#include "tape.h"
#include <string.h>
#define SIZE_A 16



// TODO: Create data structure for accepting states.
// TODO: Fixing the Transitions.

int create_tm(char *filename, Turing_Machine* tm) {
    FILE *fd;
    char *str = NULL;
    size_t len = 0;
    char *token;
    Transitions *head = (Transitions *) calloc(1, sizeof(Transitions));
    head->transition = NULL;

    if ((fd = fopen(filename, "r")) == NULL) {
        printf("Error! File %s could not be opened.\n", filename);
        return EXIT_FAILURE;
    }

    if (getline(&str, &len, fd) != -1) {
        char temp[SIZE_A];
        snprintf(temp, 16, str, "%s");

        if (!(strcmp("input_alphabet:", temp) == 0 && strtok(str, " ") != NULL &&
              (token = strtok(NULL, "\n")) != NULL)) {
            printf("Compilation failed.\n");
            return EXIT_FAILURE;
        }
        snprintf(tm->input_alphabet, sizeof(tm->input_alphabet), "%s", token);
        printf("input_alphabet: %s\n", tm->input_alphabet);
    } else {
        printf("Compilation failed.\n");
        return EXIT_FAILURE;
    }

    if (getline(&str, &len, fd) != -1) {
        char temp[SIZE_A];
        snprintf(temp, 16, "%s", str);

        if (!(strcmp("tape_alphabet: ", temp) == 0 && strtok(str, " ") != NULL &&
              (token = strtok(NULL, "\n")) != NULL)) {
            printf("Compilation failed.\n");
            return EXIT_FAILURE;
        }
        snprintf(tm->tape_alphabet, sizeof(tm->tape_alphabet), "%s", token);
        printf("tape_alphabet: %s\n", tm->tape_alphabet);
    } else {
        printf("Compilation failed.\n");
        return EXIT_FAILURE;
    }

    /* Extracting the initial state of the TM. */
    if (getline(&str, &len, fd) != -1) {
        char temp[8];
        snprintf(temp, 7, "%s", str);

        if (!(strcmp("init: ", temp) == 0 && strtok(str, " ") != NULL && (token = strtok(NULL, "\n")) != NULL)) {
            printf("Compilation failed.\n");
            exit(1);
        }
        snprintf(tm->current_state, sizeof (tm->current_state), "%s", token);
        printf("init: %s\n", tm->current_state);

    }
    /* Extracting the accepting states of the TM. */
    if (getline(&str, &len, fd) != -1) {
        char temp[SIZE_A];
        State_List *states = calloc(1, sizeof (State_List));
        snprintf(temp, 9, "%s", str);
        if (strcmp("accept: ", temp) == 0) {
            strtok(str, " ");
            token = strtok(NULL, ",");
            while (token) {
                states = insert_state(states, token);
                printf("accept: %s\n", token);
                token = strtok(NULL, ",");
            }
        }
        tm->accepted_states = states;
    }

    while (1) {
        Transition *t = NULL;
        if (getline(&str, &len, fd) != -1) {
            if (strcmp("\n", str) == 0)
                continue;
            t = (Transition*) calloc(1,sizeof(Transition));
            if (str[0] == 'q') {
                if (!strstr(str, ",")) {
                    printf("Compilation failed.\n");
                    free(t);
                    return EXIT_FAILURE;
                }
                token = strtok(str, ",");
                snprintf(t->current_state, sizeof (t->current_state), "%s", token);
                printf("%s,", token);
                if(token == NULL) {
                    printf("Compilation failed.\n");
                    free(t);
                    return EXIT_FAILURE;
                }
                token = strtok(NULL, "\n");
                strncpy(&t->symbol, &token[0], 1);
                printf("%s\n", token);
            }
            else {
                printf("Compilation failed.\n");
                free(t);
                return EXIT_FAILURE;
            }
        }
        else
            break;

        if (getline(&str, &len, fd) != -1) {
            if (strcmp("\n", str) == 0) {
                continue;
            }
            if (str[0] == 'q') {
                token = strtok(str, ",");
                snprintf(t->next_state, sizeof (t->next_state), "%s", token);
                if(token == NULL) {
                    printf("Compilation failed.\n");
                    free(t);
                    return EXIT_FAILURE;
                }
                printf("%s,", token);
                token = strtok(NULL, ",");
                strncpy(&t->write_symbol, &token[0], 1);
                if(token == NULL) {
                    printf("Compilation failed.\n");
                    free(t);
                    return EXIT_FAILURE;
                }
                printf("%s,", token);
                token = strtok(NULL, "\n");
                char c = token[0];
                if(token == NULL || !(c == '-'|| c == '<'|| c == '>')) {
                    printf("Compilation failed.\n");
                    free(t);
                    return EXIT_FAILURE;
                }
                strncpy(&t->direction, &token[0], 1);
                head = add(head, t); // TODO: Head muss auch befüllt werden mit Transition
                printf("%s\n\n", token);
            }
            else {
                printf("Compilation failed.\n");
                return EXIT_FAILURE;
            }
        }
        else
            break;
    }
    tm->head = head;
    fclose(fd);
    free(str);
    return EXIT_SUCCESS;
}

int validate(char* input_alpha, const char* input) {
    int i=0;
    char c;
    while(1) {
        c = input[i];
        if(c == '\0') break;
        if(strchr(input_alpha, c) == NULL) return EXIT_FAILURE;
        i++;
    }
    return EXIT_SUCCESS;
}

void simulate(Turing_Machine *tm, char* input) {
    char blank = tm->input_alphabet[0];
    char *current_state = tm->current_state;
    Tape *tape = create_tape(input);
    Tape *current_tape = tape;
    char current_tape_symbol;
    Transition *current_transition;

    while (1) {
        tape_print(current_tape);
        if (accept(tm->accepted_states, current_state)) {
            printf("ACCEPT\n");
            break;
        }
        current_tape_symbol = (current_tape == NULL || current_tape->content == '\0') ? blank : current_tape->content;
        current_transition = get_transition(tm->head, current_state, current_tape_symbol);
        if (current_transition == NULL && !accept(tm->accepted_states, current_state)) {
            printf("REJECT\n");
            return;
        }
        current_state = current_transition->next_state;
        current_tape->content = current_transition->write_symbol;
        current_tape = move(current_tape, current_transition ->direction, blank);
    }
}

