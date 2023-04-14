#ifndef INFO_H
#define INFO_H

typedef struct tm
{
    char *input_alphabet;
    char *init;
} TURING_MACHINE;

int create_tm(char*);
#endif