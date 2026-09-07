#include "common.h"
#include "job.h"

int main (){
    job vetor [5];
    FILE* entrada;
    entrada = fopen ("voo.txt", "r");

    int time = get_time (entrada);
    printf("%d\n", time);

    int sucesso1 = get_job (entrada, &vetor[0]);
    int sucesso2 = get_job (entrada, &vetor[1]);

    printf ("%d   %d\n", sucesso1, sucesso2);

    printf("%s %d %d %d %d\n",vetor[0].nome, vetor[0].periodo, vetor[0].deadline_relativo, vetor[0].burst, vetor[0].deadline_absoluto);
    printf("%s %d %d %d %d\n",vetor[1].nome, vetor[1].periodo, vetor[1].deadline_relativo, vetor[1].burst, vetor[1].deadline_absoluto);


    return 0;
}