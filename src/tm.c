#include <stdio.h>
#include <stdlib.h>
#include "tm.h"
#include <string.h>
#include "state_list.h"
#define SIZE_A 16
#define SIZE_B 32



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
                //printf("States: %s", states->next->state);
            }
        }
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
                snprintf(t->symbol, sizeof (t->symbol), "%s", token);
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
                snprintf(t->write_symbol, sizeof (t->write_symbol), "%s", token);
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

int simulate(Turing_Machine tm, char* input) {
    return EXIT_SUCCESS;
}

