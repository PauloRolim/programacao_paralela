#include <iostream>
#include <mpi.h>
#include <algorithm>
#include <stdlib.h>
#include <random>

#define tamanho_problema 16

int ordenacao(int vetor[8]){

    int var_local;
    int estagio;
    int i;

    for (estagio = 0; estagio < 8; estagio++)
    {
        if (estagio % 2 == 0) // Fase par da ordenação
        {
            for (i = 1; i < tamanho_problema; i+=2)
            {
                if (vetor[i-1] > vetor[i])
                {
                    var_local = vetor[i];
                    vetor[i] = vetor[i - 1];
                    vetor[i - 1] = var_local;
                }
            }         
        } else // Fase ímpar da ordenação
        {
            for (i = 1; i < 8 - 1; i+=2)
            {
                if (vetor[i] > vetor[i+1])
                {
                    var_local = vetor[i];
                    vetor[i] = vetor[i+1];
                    vetor[i+1] = var_local;
                }   
            }   
        }    
    }
    
    return vetor[8];
}


int main(int argc, char *argv[]){

    int my_rank, comm_sz;
    int vetor_entrada[tamanho_problema];
    
   // int tamanho_msg;

    for (int i = 0; i < tamanho_problema; i++)
    {
        std::random_device rd;
        std::default_random_engine gen(rd());
        std::uniform_int_distribution<>dis(1,16);
        
        int valor_aleatorio = std::round(dis(gen));

        vetor_entrada[i] = valor_aleatorio;

    }

   

    /*Área Paralela*/
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); //Tamanho do comunicador ou quantos processos inicializados
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); //Número do processo em execução

    int vetor_local[8];

    if (my_rank == 0)
    {
        for (int i = 0; i < tamanho_problema; i++)
        {
            std::cout << vetor_entrada[i] << " ";
        }

        std::cout << " " << std::endl;
    }
            
    MPI_Scatter (vetor_entrada, 8, MPI_INT, &vetor_local, 8, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);
    
    if (my_rank != 0 )
    {
        std::cout << "Processo " << my_rank << " recebido: ";

        for (int i = 0; i < 8; i++)
        {
            std::cout << vetor_local[i] << " ";
        }
        
        std::cout << std::endl;

        ordenacao(vetor_local);

        std::cout << "Processo " << my_rank << " ordenado: ";

        for (int i = 0; i < 8; i++)
        {
            std::cout << vetor_local[i] << " ";
        }
        
        MPI_Send(vetor_local, 8, MPI_INT, 0, my_rank, MPI_COMM_WORLD);

    }
  
    std::cout << " " << std::endl;       
   
    if (my_rank == 0)
    {   
        for (int q = 0; q < comm_sz; q++)
        {
            MPI_Recv(vetor_local, 8, MPI_INT, q, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        
       
        

        std::cout << " " << std::endl;

        MPI_Recv(vetor_local, 16, MPI_INT, 2, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (int i = 0; i < 16; i++)
        {
            a2[i] = vetor_local[i];
        }

       for (int i = 0; i < 16; i++)
       {
           a3[i] = a1[i];
       }
       
       for (int i = 16; i < 32; i++)
       {
           a3[i] = a2[i % 16];
       }
       
        for (int i = 0; i < 32; i++)
        {
            std::cout << a3[i] << " ";
        }
        

    }
    
    std::cout << " " << std::endl; 

    MPI_Finalize();
    return 0;
}

