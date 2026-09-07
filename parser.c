#include "parser.h"


void parse(char *linha, char *argv[]){
    
    char *token = strtok (linha, " \n");
    
    int i=0;
    while (token != NULL && i < MAX_ARG - 1){
        argv[i] = token;
        token = strtok (NULL, " \n");
        i++;
    }
    argv[i] = NULL;
}
