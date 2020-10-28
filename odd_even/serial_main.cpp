#include <iostream>
#include <stdlib.h>
#include <random>
#include <sys/time.h>

#define tamanho_problema 200000

int ordenacao(int vetor[tamanho_problema]){

    int var_local;
    int estagio;
    int i;

    for (estagio = 0; estagio < tamanho_problema; estagio++){
        if (estagio % 2 == 0){ // Fase par da ordenação
        
            for (i = 1; i < tamanho_problema; i+=2){
            
                if (vetor[i-1] > vetor[i]){
                
                    var_local = vetor[i];
                    vetor[i] = vetor[i - 1];
                    vetor[i - 1] = var_local;
                }
            }         
        }else{ // Fase ímpar da ordenação
        
            for (i = 1; i < tamanho_problema - 1; i+=2){
            
                if (vetor[i] > vetor[i+1]){
                
                    var_local = vetor[i];
                    vetor[i] = vetor[i+1];
                    vetor[i+1] = var_local;
                }   
            }   
        }    
    }
    
    return vetor[tamanho_problema];
}


int main(int argc, char *argv[]){

    struct timeval start, stop;
    
    int vetor_entrada[tamanho_problema];
        
    //std::cout << "Númermos que serão ordenados: " << std::endl;

    gettimeofday(&start, 0);

    for (int i = 0; i < tamanho_problema; i++){

        std::random_device rd;
        std::default_random_engine gen(rd());
        std::uniform_int_distribution<>dis(1,16);
        int valor_aleatorio = std::round(dis(gen));

        vetor_entrada[i] = valor_aleatorio;
       // std::cout << vetor_entrada[i] << " ";

    }
    //std::cout << std::endl;
    //std::cout << "Números após ordenação: "  << std::endl;

    ordenacao(vetor_entrada);
    /*
    for (int o = 0; o < tamanho_problema; o++)
    {
        std::cout << vetor_entrada[o] << " ";
    }
    std::cout << std::endl;
    */
    gettimeofday(&stop, 0);

    FILE *fp;
		char outputFilename[] = "tempo_de_exe_serial.txt";
	
		fp = fopen(outputFilename, "a");
		if (fp == NULL) {
			fprintf(stderr, "Can't open output file %s!\n", outputFilename);
			exit(1);
		}
	
		//testes de impressão no arquivo
		fprintf(fp, "\t%1.2e ", (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec));
		fprintf(fp, "\t%d ",tamanho_problema); //tamanho do problema+1

		fclose(fp);

    return 0;
}
