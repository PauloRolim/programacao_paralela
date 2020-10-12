#include <iostream>
#include <random>
#include <iomanip>
#include <sys/time.h>
#include <mpi.h>

//para compilar mpicxx

/*função responsável por sortear aleatoriamente pontos dentro da circunferência*/
double sorteio(double quantidade)
{
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_real_distribution<> real_dis(0, 1);
    
    double acertos;

    for (int i = 0; i < quantidade; i++)
    {
        double x_real_randomico = real_dis(gen);
        double y_real_randomico = real_dis(gen);

        if (x_real_randomico * x_real_randomico + y_real_randomico * y_real_randomico < 1.0)
        {
            acertos++;
        }
    }

    return acertos;
}

int main (int argc, char *argv[])
{
    int my_rank;
    int comm_sz;   
    int tamanho_problema = 450000;
    double pontos = 0.0;

    struct timeval start, stop; /* código fornecido pelo professor para registrar o tempo de execução */
    double tempo_exec; 

    /*Início da região paralela */
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); //Tamanho do comunicador ou quantos processos inicializados
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); //Número do processo em execução   

    if (my_rank != 0){

        gettimeofday(&start, 0);//início do registro do tempo de execução

        pontos = sorteio(tamanho_problema);

        MPI_Send(&pontos, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);

        gettimeofday(&stop, 0);

    } else {
        
        double pontos_total = 0.0;
        double pi = 0.0;

        for (int q = 1; q < comm_sz; q++)
        {
            MPI_Recv(&pontos, 1, MPI_DOUBLE, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            pontos_total += pontos;
            
        }

        pi = 4.0 * pontos_total / tamanho_problema;

        if (comm_sz >= 3)
        {
            tamanho_problema = tamanho_problema * (comm_sz - 1);
            pi = 4.0 * pontos_total / tamanho_problema;
        }

        std::cout << "O valor de Pi e " << pi << std::endl;

        

        tempo_exec = (stop.tv_usec - start.tv_usec) / 1000000 + (stop.tv_sec - start.tv_sec);

        //exibe na tela o tempo de execução em notação científica
        std::cout << "O tempo de execução foi " << (std::scientific) << tempo_exec << std::endl;

    }        

    MPI_Finalize();

    return 0;
}