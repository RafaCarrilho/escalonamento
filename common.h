#ifndef COMMON_H
#define COMMON_H
#define MAX_NOME 50
#define MAX_ARG 5

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 



typedef struct {
    char nome[MAX_NOME];
    int periodo;
    int deadline_relativo;
    int burst;
    int realizado;
    
    int deadline_absoluto;
    int lost;
    int complete;
    int killed;


}job;
#endif