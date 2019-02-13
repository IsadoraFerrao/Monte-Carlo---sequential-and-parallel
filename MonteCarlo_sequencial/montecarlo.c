/*
Cálculo do número PI - Sequencial
Compilação em Linux: gcc -o monte montecarlo.c -lm
Execução do programa: ./monte
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
 
double calcular_PI(double tolerancia){

    double valor, x, y, erro;
  
    unsigned long i, numPontos= 0, numAcertos = 0;
    
    do{
        for (i = 1000000000; i; i--, numPontos++){
              
            /*Geração de números aleatórios -  x e y
            +1 devido o parâmetro de probabilidade sorteia um número real de 0 a 1*/
            
            x = rand() / (RAND_MAX + 1.0); 
            y = rand() / (RAND_MAX + 1.0); 

            // Verifica se um ponto está dentro da circunferência

            if (x * x + y * y <= 1){ 
                numAcertos ++;
            }
        }
        
        valor = (double) numAcertos/numPontos;
        erro = (sqrt(valor*(1 - valor)/numPontos) * 4); 
        valor *=4;

        //fprintf(f, "Pi = %f, Erro = +/- %5.3e, %ldM Pontos \n", valor, erro, (numPontos/1000000000)); // Pi, Erro, numPontos escreve no arquivo

    } while (!numAcertos || erro > tolerancia);

    //fclose(f); //fechando o ponteiro  
    return valor;

}
 
int main(){

    FILE *saida;
    saida = fopen("tempo.txt", "a");
    
        
    //Coleta de tempo
    clock_t start_t, end_t;
    double total_t;
    start_t = clock(); //Coleta Inicio
    
    
    //1e-4 é a taxa de erro aceitável na probabilidade

    printf("Valor de Pi = %f\n", calcular_PI(1e-4)); /* Tolerancia 1e-4*/
    
        
	end_t = clock(); //Coleta Final
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    fprintf(saida, "%f\n", total_t);
    return 0;

}
