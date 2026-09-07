#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *arguments[]) {
    
    char *argv[MAX_ARG];
    FILE *entrada = stdin;


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
        
        
        
        
        
        

        if (strcmp(arguments[1], "rate")==0){
            //do the thing
        }
        if (strcmp(arguments[1], "edf")==0){
            //do the thing
        }

    } else {
        fprintf(stderr,"Numero incorreto de argumentos ao iniciar o Scheduler\n");
        exit(1);
    }

    
        

}