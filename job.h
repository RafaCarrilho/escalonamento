#ifndef JOB_H
#define JOB_H
#include "common.h"
#include "parser.h"
 

int get_time (FILE* entrada);
int get_job (FILE* entrada, job* task);
int load_jobs(FILE* entrada, job vetor[]);

#endif