#include <stdio.h>
#include <stdlib.h>
#include "tm.h"
#include <string.h>

int create_tm(char *filename, Turing_Machine* tm) {
    //tm = calloc(1, sizeof(Turing_Machine));
    FILE *fd;
    char *str = NULL;
    size_t len = 0;
    char *token;
    char *init;
    char input_alphabet[32];
    char tape_alphabet[32];
    Transitions *head = (Transitions*) calloc(1, sizeof(Transitions));
    head->transition = NULL;

    if ((fd = fopen(filename, "r")) == NULL) {
        printf("Error! File %s could not be opened.\n", filename);
        exit(1);
    }

    //TODO: replace token with variables specific

    if (getline(&str, &len, fd) != -1) {
        char temp[32];
        strncpy(temp, str, 16);
        temp[16] = '\0';

        if (!(strcmp("input_alphabet: ", temp) == 0 && strtok(str, " ") != NULL && (token = strtok(NULL, "\n")) != NULL)) {
            printf("Compilation failed.\n");
            exit(1);
        }
        strncpy(input_alphabet, token, 31);
        input_alphabet[31] = '\0';
        tm->input_alphabet = input_alphabet;
        printf("input_alphabet: %s\n", input_alphabet);
    }
    else {
        printf("Compilation failed.\n");
        exit(1);
    }

    if (getline(&str, &len, fd) != -1) {
        char temp[16];
        strncpy(temp, str, 15);
        temp[15] = '\0';

        if (!(strcmp("tape_alphabet: ", temp) == 0 && strtok(str, " ") != NULL && (token = strtok(NULL, "\n")) != NULL)) {
            printf("Compilation failed.\n");
            exit(1);
        }
        strncpy(tape_alphabet, token, 31);
        tape_alphabet[31] = '\0';
        tm->tape_alphabet = tape_alphabet;
        printf("tape_alphabet: %s\n", tape_alphabet);
    }
    else {
        printf("Compilation failed.\n");
        exit(1);
    }

    /* Extracting the initial state of the TM. */
    if (getline(&str, &len, fd) != -1) {
        char temp[8];
        strncpy(temp, str, 6);
        temp[6] = '\0';

        if (!(strcmp("init: ", temp) == 0 && strtok(str, " ") != NULL && (init = strtok(NULL, "\n")) != NULL)) {
            printf("Compilation failed.\n");
            exit(1);
        }
        printf("init: %s\n", init);
    }
    else {
        printf("Compilation failed.\n");
        exit(1);
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
                    exit(1); 
                }
                token = strtok(str, ",");
                t->current_state = token;
                if(token == NULL) {
                    printf("Compilation failed.\n");
                    free(t);
                    exit(1);
                }
                printf("%s,", token);
                token = strtok(str, "\n");
                t->symbol = token;
                printf("%s\n", token);
            }
            else {
                printf("Compilation failed.\n");
                free(t);
                exit(1);
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
                    exit(1);
                }
                printf("%s,", token);
                token = strtok(NULL, ",");
                t->write_symbol = token;
                if(token == NULL) {
                    printf("Compilation failed.\n");
                    free(t);
                    exit(1);
                }
                printf("%s,", token);
                token = strtok(NULL, "\n");
                char c = token[0];
                if(token == NULL || !(c == '-'|| c == '<'|| c == '>')) {
                    printf("Compilation failed.\n");
                    free(t);
                    exit(1);
                }
                t->direction = token[0];
                add(head, t);
                printf("%s\n\n", token);
            }
            else {
                printf("Compilation failed.\n");
                exit(1);
            }
        }
        else
            break;
    }
    tm->input_alphabet = input_alphabet;
    tm->current_state = init;
    tm->head = head;
    fclose(fd);
    free(str);
    exit(0);
}