#include <iostream>
#include <iomanip>
#include <random>
#include <string>
#include <sys/time.h>
#include <mpi.h>

//para compilar mpicxx

int main (int argc, char *argv[])
{
    int my_rank, comm_sz; 

    struct timeval start, stop; /* código fornecido pelo professor para registrar o tempo de execução */
    double tempo_exec;
    
    double pi;
    double acertos = 0.0;
   // int tamanho_problema;

    /*Início da região paralela */
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); //Tamanho do comunicador
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); //Número do processo em execução

    
        gettimeofday(&start, 0);//início do registro do tempo de execução

        std::random_device rd;
        std::default_random_engine gen(rd());
        std::uniform_real_distribution<> real_dis(0, 1);
            
        for (int i = 0; i < 4550000; i++)
        {
            double x_real_randomico = real_dis(gen);
            double y_real_randomico = real_dis(gen);

            if (x_real_randomico * x_real_randomico + y_real_randomico * y_real_randomico < 1.0)
            {
            acertos++;
            }
        }

   
        
        pi = (4.0 * acertos) / 4550000; // onde divisor é a quantidade de pontos sorteados (x²+y²)
       
        gettimeofday(&stop, 0); //fim do registro do tempo de execução
       
        //cálculo do tempo de execução
        tempo_exec = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);

        //exibe na tela o valor aproximado de Pi
        std::cout << "o valor de pi e " << (double)pi << std::endl;

        //exibe na tela o tempo de execução em notação científica
        std::cout << "O tempo de execução foi " << (std::scientific) << tempo_exec << std::endl; 

    MPI_Finalize();
    return 0;
}