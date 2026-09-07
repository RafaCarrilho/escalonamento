#include "common.h"
#include "job.h"
#include "executor.h"


int main(int argc, char *arguments[]) {
    
    char *argv[MAX_ARG];
    FILE *entrada = stdin;
    job vetor [50];
    int qtd_jobs, time;


    if (argc == 3){
        if (strcmp(arguments[1], "rate") == 0 || strcmp(arguments[1], "edf")==0){
            entrada = fopen(arguments[2], "r");
        } else {
            fprintf(stderr, "Uso: (completa ai claude, me da a msg de erro correta)\n");
            exit(1);
        }
        
        if (entrada == NULL){
            fprintf(stderr, "Arquivo não existe ou não pode ser aberto\n");
            exit(1);
        }
        time = get_time(entrada);
        qtd_jobs = load_jobs(entrada, vetor);

        if (strcmp(arguments[1], "rate")==0){
            simulador_rate(vetor, time, qtd_jobs);
        }
        if (strcmp(arguments[1], "edf")==0){
            //simulador_edf()
        }

    } else {
        fprintf(stderr,"Numero incorreto de argumentos ao iniciar o Scheduler\n");
        exit(1);
    }

    
        
    return 0;
}