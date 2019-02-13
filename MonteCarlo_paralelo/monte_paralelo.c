/* C�lculo do n�mero PI - Paralelo
Compila��o em Linux: gcc monte_paralelo.c -o paralelo -lpthread -lm
Execu��o do programa: ./paralelo */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include<time.h>

long long int num_pontos;
long int numThreads;
#define TOTAL_PONTOS 10000055  //Numero de Pontos
#define BILLION  1E9; // Para n�o passar desse valor 

// Aloca��o de tarefas para cada Thread

void *calcular(void *thread_id){

    long thrnum = (long)thread_id;
    int tid = (int)thrnum;  //O n�mero da Thread

    // Aloca��o din�mica do ponteiro que conta os pontos do c�rculo

    float *pontos_Circulo = (float *)malloc(sizeof(float));
    *pontos_Circulo=0;

    float total_iteracao= TOTAL_PONTOS/numThreads; //N�mero de itera��o por thread
    int contador = 0;

    //Gera��o de n�meros aleat�rios -  x e y

    for(contador=0;contador<total_iteracao;contador++){
        float x =  rand() / (RAND_MAX + 1.0);;
        float y =  rand() / (RAND_MAX + 1.0);;

        if (x * x + y * y < 1){  // Verificar se um ponto est� dentro da circunfer�ncia
            *pontos_Circulo+=1;
        }
    }

    pthread_exit((void *)pontos_Circulo); //retorna o n�mero de pontos no c�rculo
}

int main(int argc, char **argv){

    int rc;
    void *status;
    float TOTAL_CIRCULO=0; // Pontos do c�rculo
    
    FILE *saida;
    saida = fopen("tempo.txt", "a");

	if (argc < 2) {
		printf ("Errado! Utilize: programa <threads> <input-size>\n\n \tE.g. -> ./programa 2 400000\n\n");
		exit(1);
	}
	
	
    /* TRATANDO AS ENTRADAS */
    
	num_pontos = strtoul(argv[2], NULL, 10); //n de iteracoes
	long int i;
	numThreads = atol(argv[1]);
	pthread_t threads[numThreads]; //vetor de threads do tipo pthread
	

    //Coleta de tempo
    clock_t start_t, end_t;
    double total_t;
    start_t = clock(); //Coleta Inicio
    
    for(i=1;i<=numThreads;i++){
		rc = pthread_create(&threads[i], NULL, calcular, (void *)i); //criacao das threads
	}
	
    
    /* RECEBE A ESTRUTURA DE CONTROLE DA THREAD */
	
	for(i=1;i<=numThreads;i++){
		pthread_join(threads[i], &status); 
        TOTAL_CIRCULO+=*(float*)status;
	}


    end_t = clock(); //Coleta Final
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

    double aux = (1,4);

    /*RESULTADO*/
    printf("Valor do PI: %f \n",aux*(TOTAL_CIRCULO/TOTAL_PONTOS));
    fprintf(saida, "%f\n", total_t);
	return 0;

    pthread_exit(NULL);     /* Destrui��o das Threads*/

    return 0;
}
