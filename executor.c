#include "common.h"
#include "executor.h"

int ready (job task){
    if (task.burst > task.realizado){
        return 1;
    }
    return 0;
}

void simulador_rate (job vetor[], int time, int qtd_jobs, FILE* saida){
    int t;
    int menor_periodo, for_units =0, idle=0;
    job* ativo; 
    job* ultimo_ativo=NULL;
    job* job_lost= NULL;

    for (t=0; t<time; t++){
        menor_periodo = INT_MAX;
        ativo = NULL;
        
        for (int i =0; i<qtd_jobs; i++){ //spawna o job e reinicia ela
            if (t==0 || t % vetor[i].periodo ==0){
                vetor[i].realizado = 0;
                vetor[i].deadline_absoluto = t +vetor[i].deadline_relativo;

            }
        }

        for (int i =0; i<qtd_jobs; i++){ //verifico as deadlines de todas as ativas
            if (vetor[i].deadline_absoluto == t && ready(vetor[i])){
                vetor[i].realizado = vetor[i].burst;
                vetor[i].lost ++;
                if (&vetor[i] == ultimo_ativo){ // se foi o ativo quem perdeu a tarefa... 
                    job_lost = &vetor[i]; //anota o nome dele!
                }
                
            }

        }
        
        
        for (int i =0; i<qtd_jobs; i++){ // decisão de prioridade
            if (vetor[i].periodo < menor_periodo && ready(vetor[i])){
                ativo = &vetor[i];
                menor_periodo = ativo->periodo;                
                
            } 
        }

        if (ativo != ultimo_ativo){
            if (t ==0){ //se primeira iteração a gente já prepara o ultimo ativo mas não roda as outras condições
                ultimo_ativo = ativo;
            }else if (idle != 0){ // se tava idle antes, bora printar o idle CONDIÇÃO IDLE
                fprintf (saida,"idle for %d units\n", idle);
                idle =0;
            }else if (ready(*ultimo_ativo)){ // se o ultimo ainda estava trabalhando em algo CONDIÇÃO H
                fprintf (saida,"[%s] for %d units - H\n", ultimo_ativo->nome, for_units);
                for_units=0;
            }else if (job_lost != NULL){ //Se job_lost foi acionado, CONDIÇÃO L
                fprintf (saida,"[%s] for %d units - L\n", job_lost->nome, for_units);
                job_lost =NULL;
                for_units=0;                
            }  
            ultimo_ativo = ativo;
        }

        if (menor_periodo != INT_MAX){ 
            ativo->realizado++;
            for_units++;
            if (ativo->realizado == ativo->burst){
                ativo->complete ++;
                fprintf (saida,"[%s] for %d units - F\n", ativo->nome, for_units); // se finish, printa a CONDIÇÃO F
                for_units=0;
                
            }
        } else { //se o menor periodo for int_max, quer dizer que estamos em idle
            idle++;
            ativo = NULL;
        }

        
        if (t==time-1 && idle != 0){
            fprintf (saida,"idle for %d units\n", idle);
        }              
    } //fim do for principal

    for (int i =0; i<qtd_jobs; i++){ //após todos os laços de t eu verifico se sobrou algum ativo e mato!
        if (ready(vetor[i])){
            vetor[i].killed ++;
        }
    }
    
    fprintf (saida,"\nLOST DEADLINES\n");
    for (int i =0; i<qtd_jobs; i++){
        fprintf (saida,"[%s] %d\n", vetor[i].nome, vetor[i].lost);
    }
    fprintf (saida,"\nCOMPLETE EXECUTION\n");
    for (int i =0; i<qtd_jobs; i++){
        fprintf (saida,"[%s] %d\n", vetor[i].nome, vetor[i].complete);
    }
    
    fprintf (saida,"\nKILLED\n");
    for (int i =0; i<qtd_jobs; i++){
        fprintf (saida,"[%s] %d\n", vetor[i].nome, vetor[i].killed);
    }
}


void simulador_edf (job vetor[], int time, int qtd_jobs, FILE* saida){
    int t;
    int menor_deadline, for_units =0, idle=0;
    job* ativo; 
    job* ultimo_ativo=NULL;
    job* job_lost= NULL;

    for (t=0; t<time; t++){
        menor_deadline = INT_MAX;
        ativo = NULL;
        
        for (int i =0; i<qtd_jobs; i++){ //spawna o job e reinicia ela
            if (t==0 || t % vetor[i].periodo ==0){
                vetor[i].realizado = 0;
                vetor[i].deadline_absoluto = t +vetor[i].deadline_relativo;

            }
        }

        for (int i =0; i<qtd_jobs; i++){ //verifico as deadlines de todas as ativas
            if (vetor[i].deadline_absoluto == t && ready(vetor[i])){
                vetor[i].realizado = vetor[i].burst;
                vetor[i].lost ++;
                if (&vetor[i] == ultimo_ativo){ // se foi o ativo quem perdeu a tarefa... 
                    job_lost = &vetor[i]; //anota o nome dele!
                }
                
            }

        }
        
        
        for (int i =0; i<qtd_jobs; i++){ // decisão de prioridade
            if (vetor[i].deadline_absoluto < menor_deadline && ready(vetor[i])){
                ativo = &vetor[i];
                menor_deadline = ativo->deadline_absoluto;                
                
            } 
        }

        if (ativo != ultimo_ativo){
            if (t ==0){ //se primeira iteração a gente já prepara o ultimo ativo mas não roda as outras condições
                ultimo_ativo = ativo;
            }else if (idle != 0){ // se tava idle antes, bora printar o idle CONDIÇÃO IDLE
                fprintf (saida,"idle for %d units\n", idle);
                idle =0;
            }else if (ready(*ultimo_ativo)){ // se o ultimo ainda estava trabalhando em algo CONDIÇÃO H
                fprintf (saida,"[%s] for %d units - H\n", ultimo_ativo->nome, for_units);
                for_units=0;
            }else if (job_lost != NULL){ //Se job_lost foi acionado, CONDIÇÃO L
                fprintf (saida,"[%s] for %d units - L\n", job_lost->nome, for_units);
                job_lost =NULL;
                for_units=0;                
            }  
            ultimo_ativo = ativo;
        }

        if (menor_deadline != INT_MAX){ 
            ativo->realizado++;
            for_units++;
            if (ativo->realizado == ativo->burst){
                ativo->complete ++;
                fprintf (saida,"[%s] for %d units - F\n", ativo->nome, for_units); // se finish, printa a CONDIÇÃO F
                for_units=0;
                
            }
        } else { //se o menor deadline for int_max, quer dizer que estamos em idle
            idle++;
            ativo = NULL;
        }

        
        if (t==time-1 && idle != 0){
            fprintf (saida,"idle for %d units\n", idle);
        }              
    } //fim do for principal

    for (int i =0; i<qtd_jobs; i++){ //após todos os laços de t eu verifico se sobrou algum ativo e mato!
        if (ready(vetor[i])){
            vetor[i].killed ++;
        }
    }
    
    fprintf (saida,"\nLOST DEADLINES\n");
    for (int i =0; i<qtd_jobs; i++){
        fprintf (saida,"[%s] %d\n", vetor[i].nome, vetor[i].lost);
    }
    fprintf (saida,"\nCOMPLETE EXECUTION\n");
    for (int i =0; i<qtd_jobs; i++){
        fprintf (saida,"[%s] %d\n", vetor[i].nome, vetor[i].complete);
    }
    
    fprintf (saida,"\nKILLED\n");
    for (int i =0; i<qtd_jobs; i++){
        fprintf (saida,"[%s] %d\n", vetor[i].nome, vetor[i].killed);
    }
}