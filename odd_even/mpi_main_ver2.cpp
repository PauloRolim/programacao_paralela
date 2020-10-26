#include <iostream>
#include <mpi.h>
#include <algorithm>
#include <stdlib.h>
#include <random>
#include <stdio.h>

#define tamanho_problema 16

int main(int argc, char *argv[]){

    int my_rank, comm_sz;
    int n = tamanho_problema; //tamanho do problema
    int localn; //tamanho do problema local
    int *data; //vetor de dados
    int recdata[100]; //vetor para receber as mensagens
    int recdata2[100]; //vetor auxiliar na ordenação
    int *temp;
    MPI_Status status;

     /*Área Paralela*/
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); //Tamanho do comunicador ou quantos processos inicializados
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); //Número do processo em execução

    /*local onde é gerado um vetor aleatorio para ser enviado aos processos*/
    if (my_rank == 0)
    {
        int avgn = n / comm_sz;
        localn = avgn;

        data = (int*)malloc(sizeof(int)*n);
        
        for (int i = 0; i < n; i++)
        {
            std::random_device rd;
            std::default_random_engine gen(rd());
            std::uniform_int_distribution<>dis(0,tamanho_problema);
            
            data[i] = std::round(dis(gen));

            std::cout << data[i] << " ";
        }

        std::cout << " " << std::endl;
    } else
    {
        data=NULL;
    }

    MPI_Bcast(&localn,1,MPI_INT,0,MPI_COMM_WORLD); // envio do tamanho do problema para cada processo

    MPI_Scatter(data, localn, MPI_INT, &recdata, 100, MPI_INT, 0, MPI_COMM_WORLD); //envio dos número para ordenação
    
    MPI_Barrier(MPI_COMM_WORLD);

    std::cout << "Processo " << my_rank << " recebido: ";

    for (int i = 0; i < localn; i++)
    {
        std::cout << recdata[i] << " ";
    }
  
    std::cout << " " << std::endl;   

    /*Início da ordenação do vetor entrada por meio do OddEven sort*/ 

    int rankImpar, rankPar;

    if (my_rank % 2 == 0)
    {
        rankImpar = my_rank - 1;
        rankPar = my_rank + 1;
    } else
    {
        rankImpar = my_rank + 1;
        rankPar = my_rank - 1;
    }
    
    /*Teste para resetar o numero do processos ao final da ordenação linear*/

    if (rankImpar == -1 || rankImpar == comm_sz)
    {
        rankImpar = MPI_PROC_NULL;
    }
    if (rankPar == -1 || rankPar == comm_sz)
    {
        rankPar = MPI_PROC_NULL;
    }
    
    int p;
    for (p = 0; p < comm_sz-1; p++)
    {
        if (p%2 == 1) // Fase ímpar
        {

            MPI_Sendrecv(recdata, localn, MPI_INT, rankImpar, 1, recdata2,
            localn, MPI_INT, rankImpar, 1, MPI_COMM_WORLD, &status);

        } else // Fase par
        {
            MPI_Sendrecv(recdata, localn, MPI_INT, rankPar, 1, recdata2,
            localn, MPI_INT, rankPar, 1, MPI_COMM_WORLD, &status);
        }
        
        temp = (int*)malloc(localn*sizeof(int)); // alocação de vetor auxiliar

            for(int i = 0; i < localn; i++)
            {
 	            temp[i]=recdata[i];
            }
        
    }
    
    if (status.MPI_SOURCE==MPI_PROC_NULL)
    {
        std::cout << " good ";
    } else if (my_rank < status.MPI_SOURCE)
    {
        /*momento onde é salvo o número menor após comparação*/
        int i,j,k;
        for (i=j=k=0; k < localn; k++)
        {
            if (j==localn || (i<localn && temp[i]<recdata2[j]))
            {
                recdata[k]=temp[i++];
            } else
            {
                recdata[k]=recdata2[j++];
            }
            
            
        }
        
    } else
    {
        /* momento onde é salvo o numero maior apos comparação */

        int i,j,k;
        for (i=j=k = localn -1; k >=0 ; k--)
        {
            if (j==-1||(i>=0 && temp[i]>=recdata2[j]))
            {
                recdata[k]=temp[i--];
            } else
            {
                recdata[k]=recdata2[j--];
            }
                     
        }
        
    }
    
    MPI_Gather(recdata,localn,MPI_INT,data,localn,MPI_INT,0,MPI_COMM_WORLD);

    if (my_rank == 0)
    {
        std::cout << "Vetor ordenado: ";
        for (int i = 0; i < n; i++)
        {
            std::cout << data[i] << " ";
        }
        
        std::cout << " " << std::endl;
    }
    
    MPI_Finalize();
    return 0;
}