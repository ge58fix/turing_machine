#include <stdio.h>
#include <stdlib.h>
#include "tm.h"
#include <string.h>

int create_tm(char *filename) {
    FILE *fd;
    char *str = NULL;
    size_t len = 0;
    char *token;
    char *init;

    if ((fd = fopen(filename, "r")) == NULL) {
        printf("Error! File %s could not be opened.\n", filename);
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
        if (getline(&str, &len, fd) != -1) {
            if (strcmp("\n", str) == 0)
                continue;
            if (str[0] == 'q') {
                if (!strstr(str, ",")) {
                    printf("Compilation failed.\n");
                    exit(1); 
                }
                token = strtok(str, ",");
                if(token == NULL) {
                    printf("Compilation failed.\n");
                    exit(1);
                }
                printf("%s,", token);
                token = strtok(str, "\n");
                printf("%s\n", token);
            }
            else {
                printf("Compilation failed.\n");
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
                if(token == NULL) {
                    printf("Compilation failed.\n");
                    exit(1);
                }
                printf("%s,", token);
                token = strtok(NULL, ",");
                if(token == NULL) {
                    printf("Compilation failed.\n");
                    exit(1);
                }
                printf("%s,", token);
                token = strtok(NULL, "\n");
                if(token == NULL) {
                    printf("Compilation failed.\n");
                    exit(1);
                }
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
    fclose(fd);
    free(str);
    exit(0);
}