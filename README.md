Escalonamento — Rate-Monotonic × Earliest-Deadline-First

Simulador de escalonamento de tarefas periódicas de tempo real, implementando dois algoritmos preemptivos: Rate-Monotonic (RM) e Earliest-Deadline-First (EDF).

Implementação 3 — disciplina Infraestrutura de Software, CESAR School.

Compilação
bash
make

Gera o executável scheduler. Para remover:

bash
make clean
Uso
bash
./scheduler rate <arquivo>
./scheduler edf <arquivo>

Exemplo:

bash
./scheduler rate voo.txt
Formato do arquivo de entrada
1ª linha: tempo total de simulação (inteiro positivo).
Linhas seguintes, uma por tarefa: NOME PERIODO DEADLINE RAJADA (inteiros positivos, respeitando RAJADA ≤ DEADLINE ≤ PERIODO).
Todas as tarefas chegam pela primeira vez em t=0.

Exemplo (voo.txt):

100
ATT 20 12 8
NAV 50 30 15
Saída

O resultado é escrito em rate_rac4.out ou edf_rac4.out, conforme o algoritmo escolhido — nada é impresso no terminal durante a execução normal.

O arquivo contém o log de execução (segmentos por tarefa, marcados com F/H/L conforme terminaram, foram interrompidos por preempção ou perderam o deadline, além dos trechos ociosos) seguido de três contagens finais por tarefa: deadlines perdidos (LOST DEADLINES), execuções completas (COMPLETE EXECUTION) e tarefas ainda em execução quando a simulação termina (KILLED).

Tratamento de erros

O programa valida: número de argumentos, se o primeiro argumento é rate ou edf, se o arquivo de entrada existe e pode ser lido, se o conteúdo do arquivo está bem formado (campos presentes, numéricos, positivos) e se cada tarefa respeita C ≤ D ≤ P. Em qualquer erro, a mensagem vai para stderr, o programa encerra com código de saída diferente de zero e nenhum arquivo de saída é criado.

Estrutura dos arquivos
Arquivo	Responsabilidade
main.c	Valida argumentos da linha de comando, abre arquivo de entrada/saída, orquestra leitura e simulação
job.c / job.h	Leitura e validação do arquivo de entrada (get_time, get_job, load_jobs)
parser.c / parser.h	Tokenização de uma linha de texto
executor.c / executor.h	Os dois motores de simulação (simulador_rate, simulador_edf)
common.h	Struct job e constantes compartilhadas
Autor

Rafael Carrilho (rac4) — CESAR School