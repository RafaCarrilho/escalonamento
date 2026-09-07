#ifndef EXECUTOR_H
#define EXECUTOR_H
#include "common.h"

 

void simulador_rate (job vetor[], int time, int qtd_jobs, FILE* saida);
void simulador_edf (job vetor[], int time, int qtd_jobs, FILE* saida);

#endif


