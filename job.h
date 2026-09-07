#ifndef JOB_H
#define JOB_H
#include "common.h"
#include "parser.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  

int get_time (FILE* entrada);
int get_job (FILE* entrada, job* task);

#endif