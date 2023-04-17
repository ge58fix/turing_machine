#include <stdio.h>
#include <stdlib.h>
#include "tm.h"
#include <string.h>



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
        char temp[32];
        strncpy(temp, str, 16);
        temp[16] = '\0';

        if (!(strcmp("input_alphabet: ", temp) == 0 && strtok(str, " ") != NULL &&
              (token = strtok(NULL, "\n")) != NULL)) {
            printf("Compilation failed.\n");
            return EXIT_FAILURE;
        }
        strncpy(tm->input_alphabet, token, 31);
        tm->input_alphabet[31] = '\0';
        printf("input_alphabet: %s\n", tm->input_alphabet);
    } else {
        printf("Compilation failed.\n");
        return EXIT_FAILURE;
    }

    if (getline(&str, &len, fd) != -1) {
        char temp[16];
        strncpy(temp, str, 15);
        temp[15] = '\0';

        if (!(strcmp("tape_alphabet: ", temp) == 0 && strtok(str, " ") != NULL &&
              (token = strtok(NULL, "\n")) != NULL)) {
            printf("Compilation failed.\n");
            return EXIT_FAILURE;
        }
        strncpy(tm->tape_alphabet, token, 31);
        tm->tape_alphabet[31] = '\0';
        printf("tape_alphabet: %s\n", tm->tape_alphabet);
    } else {
        printf("Compilation failed.\n");
        return EXIT_FAILURE;
    }

    /* Extracting the initial state of the TM. */
    if (getline(&str, &len, fd) != -1) {
        char temp[8];
        strncpy(temp, str, 6);
        temp[6] = '\0';

        if (!(strcmp("init: ", temp) == 0 && strtok(str, " ") != NULL && (token = strtok(NULL, "\n")) != NULL)) {
            printf("Compilation failed.\n");
            exit(1);
        }
        strncpy(tm->current_state, token, 15);
        tm->current_state[15] = '\0';
        printf("init: %s\n", tm->current_state);

    }
    /* Extracting the accepting states of the TM. */
    if (getline(&str, &len, fd) != -1) {
        char temp[16];
        strncpy(temp, str, 8);
        temp[8] = '\0';
        if (strcmp("accept: ", temp) == 0) {
            strtok(str, " ");
            token = strtok(NULL, ",");
            while (token) {
                printf("accept: %s\n", token);
                token = strtok(NULL, ",");
            }
        }
    }

    while (1) {
        Transition *t = NULL;
        if (getline(&str, &len, fd) != -1) {
            if (strcmp("\n", str) == 0)
                continue;
            t = (Transition*) malloc(sizeof(Transition));
            if (str[0] == 'q') {
                if (!strstr(str, ",")) {
                    printf("Compilation failed.\n");
                    free(t);
                    return EXIT_FAILURE;
                }
                token = strtok(str, ",");
                t->current_state = token;
                if(token == NULL) {
                    printf("Compilation failed.\n");
                    free(t);
                    return EXIT_FAILURE;
                }
                printf("%s,", token);
                token = strtok(str, "\n");
                t->symbol = token;
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
                t->next_state = token;
                if(token == NULL) {
                    printf("Compilation failed.\n");
                    free(t);
                    return EXIT_FAILURE;
                }
                printf("%s,", token);
                token = strtok(NULL, ",");
                t->write_symbol = token;
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
                t->direction = token[0];
                add(head, t);
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

int validate(char* input_alpha, char* input) {
    int i=0;
    char c;
    while(1) {
        c = input[i];
        if(c == '\0') break;
        if(strchr(input, c) != NULL) return 0;
        i++;
    }
    return 1;
}

