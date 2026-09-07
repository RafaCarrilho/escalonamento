#include "common.h"
#include "job.h"
#include "executor.h"

int main (){
    job vetor [50];
    FILE* entrada;
    entrada = fopen ("voo.txt", "r");

    int time = get_time (entrada);
    printf("%d\n", time);

    int qtd_jobs = load_jobs(entrada, vetor);

    simulador_rate (vetor, time, qtd_jobs);


    return 0;
}