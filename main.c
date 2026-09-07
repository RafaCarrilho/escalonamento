#include "common.h"
#include "job.h"
#include "executor.h"


int main(int argc, char *arguments[]) {
    
    FILE *entrada;
    FILE *saida;
    job vetor [50];
    int qtd_jobs, time;
    


    if (argc == 3){
        if (strcmp(arguments[1], "rate") == 0 || strcmp(arguments[1], "edf")==0){
            entrada = fopen(arguments[2], "r");
        } else {
            fprintf(stderr, "Uso: ./scheduler rate / edf arquivo\n");
            exit(1);
        }
        
        if (entrada == NULL){
            fprintf(stderr, "Arquivo não existe ou não pode ser aberto\n");
            exit(1);
        }
        time = get_time(entrada);
        qtd_jobs = load_jobs(entrada, vetor);

        if (strcmp(arguments[1], "rate")==0){
            saida = fopen("rate_rac4.out", "w");
            if (saida == NULL){
                fprintf(stderr, "Falha ao abrir arquivo de saída\n");
                exit(1);
            }

            simulador_rate(vetor, time, qtd_jobs, saida);
        }
        if (strcmp(arguments[1], "edf")==0){
            saida = fopen("edf_rac4.out", "w");
            if (saida == NULL){
                fprintf(stderr, "Falha ao abrir arquivo de saída\n");
                exit(1);
            }
            simulador_edf (vetor, time, qtd_jobs, saida);
        }

    } else {
        fprintf(stderr,"Número incorreto de argumentos ao iniciar o Scheduler\n");
        exit(1);
    }


    fclose(entrada);
    fclose(saida);
    return 0;
}