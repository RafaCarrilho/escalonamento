#include "common.h"
#include "job.h"  
  

int get_time (FILE* entrada){
    char linha[256] = "lesgooo";
    char* argv[MAX_ARG];

    if (fgets(linha, sizeof(linha), entrada)==NULL){ //aqui eu faço a linha com o conteúdo do arquivo
            fprintf(stderr, "Arquivo vazio!\n");
            exit(1);
        }
    
    parse(linha, argv);

    if (argv[0] == NULL){
            fprintf(stderr, "Arquivo preenchido incorretamente (Sem limite de simulação)\n");
            exit(1);
        }
    char *sobra;
    long time = strtol(argv[0], &sobra, 10);
    if (*sobra != '\0') {
        fprintf(stderr, "Arquivo preenchido incorretamente\n");
        exit(1);
    }
    if (time<=0 || time > INT_MAX){
        fprintf(stderr, "Limite de simulação incorreto (não pode ser menor ou igual a zero ou maior que limite de INT.\n");
        exit(1);
    }
    int tempo = (int) time;

    return tempo;
}

int get_job (FILE* entrada, job* task){
    char linha[256] = "lesgooo";
    char* argv[MAX_ARG];
    char *sobra;
    if (fgets(linha, sizeof(linha), entrada)==NULL){ //aqui eu faço a linha com o conteúdo do arquivo
            return 0;
        }
    parse(linha, argv);
    
    if (argv[0] == NULL || argv[1] == NULL || argv[2] == NULL || argv[3] == NULL) {
        fprintf(stderr, "Linha do arquivo preenchida incorretamente");
        exit(1);
    }

    
    
    long period = strtol(argv[1], &sobra, 10);
    if (*sobra != '\0') {
        fprintf(stderr, "Arquivo preenchido incorretamente\n");
        exit(1);
    }
    if (period<=0 || period > INT_MAX){
        fprintf(stderr, "Limite de simulação incorreto (não pode ser menor ou igual a zero ou maior que limite de INT.\n");
        exit(1);
    }
    int periodo = (int) period;

    long deadline_r = strtol(argv[2], &sobra, 10);
    if (*sobra != '\0') {
        fprintf(stderr, "Arquivo preenchido incorretamente\n");
        exit(1);
    }
    if (deadline_r<=0 || deadline_r > INT_MAX){
        fprintf(stderr, "Limite de simulação incorreto (não pode ser menor ou igual a zero ou maior que limite de INT.\n");
        exit(1);
    }
    int deadline_relativo = (int) deadline_r;

    long rajada = strtol(argv[3], &sobra, 10);
    if (*sobra != '\0') {
        fprintf(stderr, "Arquivo preenchido incorretamente\n");
        exit(1);
    }
    if (rajada<=0 || rajada > INT_MAX){
        fprintf(stderr, "Limite de simulação incorreto (não pode ser menor ou igual a zero ou maior que limite de INT.\n");
        exit(1);
    }
    int burst =  (int) rajada;

    if ((periodo >= deadline_relativo  &&  deadline_relativo >= burst)==0){
        fprintf(stderr, "Regra P>D>C não respeitada.\n");
        exit(1);
    }
    
    strncpy (task->nome, argv[0], MAX_NOME);
    task->periodo = periodo;
    task->deadline_relativo = deadline_relativo;
    task->burst = burst;
    task->realizado = 0;
    task->deadline_absoluto = 0 + deadline_relativo;
    task->lost = 0;
    task->complete = 0;
    task-> killed = 0;
    
    return 1;
}

int load_jobs(FILE* entrada, job vetor[]){
    int i = 0;
    while (i < 50 && get_job(entrada, &vetor[i]) == 1){
        i++;
    }
    return i;
}

