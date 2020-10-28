#include <iostream>
#include <mpi.h>
#include <algorithm>
#include <stdlib.h>
#include <random>
#include <sys/time.h>

#define tamanho_problema 9000

int main(int argc, char *argv[]){

    int my_rank, comm_sz;
    int vetor_entrada[tamanho_problema];
    int var_local;
    int estagio;
    int i;
    int tamanho_msg;

    struct timeval start, stop;

    for (int i = 0; i < tamanho_problema; i++) //Vetor randomico de entrada
    {
        std::random_device rd;
        std::default_random_engine gen(rd());
        std::uniform_int_distribution<>dis(0,999);
        
        int valor_aleatorio = std::round(dis(gen));

        vetor_entrada[i] = valor_aleatorio;

    }

    /*Área Paralela*/
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); //Tamanho do comunicador ou quantos processos inicializados
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); //Número do processo em execução

    tamanho_msg = tamanho_problema / comm_sz; /*variável responsável por armazenar o tamanho 
                                                do vetor que será enviado para cada processo*/
    int vetor_local[tamanho_msg];
    /*
    if (my_rank == 0)
    {   
        std::cout << "Vetor INICIAL desordenado: ";
        for (int i = 0; i < tamanho_problema; i++)
        {
            std::cout << vetor_entrada[i] << " ";   //Imprime na tela o vetor entrada
        }
        std::cout << " " << std::endl;
       
        
    }*/
    // separa o vetor entrada em partes e envia para cada processo
    gettimeofday(&start, 0);

    MPI_Scatter (vetor_entrada, tamanho_msg, MPI_INT, &vetor_local, tamanho_msg, MPI_INT, 0, MPI_COMM_WORLD);
    
        /*
        std::cout << "Processo " << my_rank << " recebido: ";

        for (int i = 0; i < tamanho_msg; i++)
        {
            std::cout << vetor_local[i] << " ";
        }
        
        std::cout << " " << std::endl;
        */
    for (estagio = 0; estagio < tamanho_msg; estagio++)
    {
        if (estagio % 2 == 0) // Fase par da ordenação
        {
            for (i = 1; i < tamanho_msg; i+=2)
            {
                if (vetor_local[i-1] > vetor_local[i])
                {
                    var_local = vetor_local[i];
                    vetor_local[i] = vetor_local[i - 1];
                    vetor_local[i - 1] = var_local;
                }
            }          
        }else // Fase ímpar da ordenação
        {
            for (i = 1; i < tamanho_msg - 1; i+=2)
            {
                if (vetor_local[i] > vetor_local[i+1])
                {
                    var_local = vetor_local[i];
                    vetor_local[i] = vetor_local[i+1];
                    vetor_local[i+1] = var_local;
                }   
            }   
        }    
    }
    /*
        std::cout << "Processo " << my_rank << " ordenado: ";

        for (int i = 0; i < tamanho_msg; i++)
        {
            std::cout << vetor_local[i] << " ";
        }
          
    std::cout << " " << std::endl;       
    */ 
    //junta as partes de vetores num único vetor e envia para o processo mestre
    MPI_Gather(vetor_local,tamanho_msg,MPI_INT,vetor_entrada,tamanho_msg,MPI_INT,0,MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD); //sincroniza as mensagens antes de enviar
    
    if (my_rank == 0)
    {
        for (estagio = 0; estagio < tamanho_problema; estagio++)
        {
            if (estagio % 2 == 0) // Fase par da ordenação
            {
                for (i = 1; i < tamanho_problema; i+=2)
                {
                    if (vetor_entrada[i-1] > vetor_entrada[i])
                    {
                        var_local = vetor_entrada[i];
                        vetor_entrada[i] = vetor_entrada[i - 1];
                        vetor_entrada[i - 1] = var_local;
                    }
                }         
            } else // Fase ímpar da ordenação
            {
                for (i = 1; i < tamanho_problema - 1; i+=2)
                {
                    if (vetor_entrada[i] > vetor_entrada[i+1])
                    {
                        var_local = vetor_entrada[i];
                        vetor_entrada[i] = vetor_entrada[i+1];
                        vetor_entrada[i+1] = var_local;
                    }   
                }   
            }    
        }

        gettimeofday(&stop, 0);
        /*
        std::cout << "Vetor FINAL ordenado: ";
        for (int i = 0; i < tamanho_problema; i++)
        {
            std::cout << vetor_entrada[i] << " ";
        }
        
        std::cout << " " << std::endl;
        */
        FILE *fp;
		char outputFilename[] = "tempo_de_exe_mpi.txt";

        fp = fopen(outputFilename, "a");
		if (fp == NULL) {
			fprintf(stderr, "Can't open output file %s!\n", outputFilename);
			exit(1);
		}

        fprintf(fp, "\t%1.2e ", (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec));
        fprintf(fp, "\t%d ",comm_sz); //número de tasks mpi
		fprintf(fp, "\t%d ",tamanho_problema); //tamanho do problema+1

        fclose(fp);
    }

    MPI_Finalize();
    return 0;
}