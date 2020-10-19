#include <mpi.h>
#include <iostream>
#include <random>
#include <sys/time.h>

int main(int argc, char const *argv[]){

    int tamanho_problema;
    double acumulador;
    double pi_global;
    double pi_local;

    int my_rank, comm_sz; // variáveis MPI

    struct timeval start, stop; /* código fornecido pelo professor para registrar o tempo de execução */
    double tempo_exec;
    
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank == 0)
    {
        std::cout << "Informe agora o tamanho do problema para calcular PI" << std::endl;
        std::cin >> tamanho_problema;
    }

    /*função que envia para todos os processos o valor da variável tamanho_problema. Fazendo com que 
    todos os processos recebam o valor para iniciarem o sorteio dos números e o calculo de Pi*/
    MPI_Bcast(&tamanho_problema, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (tamanho_problema <= 0)
    {
        MPI_Finalize();
        return 1;
    }else {

        gettimeofday(&start, 0);//início do registro do tempo de execução

        /* Cálculo de Pi */

        for (int i = my_rank +1; i <= tamanho_problema; i=comm_sz + i)
        {

            std::random_device rd;
            std::default_random_engine gen(rd());
            std::uniform_real_distribution<> real_dis(0, 1);

            double x_real_randomico = real_dis(gen);
            double y_real_randomico = real_dis(gen);

            if (x_real_randomico * x_real_randomico + y_real_randomico * y_real_randomico < 1.0)
            {
                acumulador++;
            }
 
        }
            /* Fim do cálculo de Pi */
        pi_local = (4.0 * acumulador) / tamanho_problema; 

        
        /*função responsável por somar e reduzir todos os dados gerados nos processos paralelos em um
        conjunto menor de números. Na prátia essa função está recebendo todos os valores calculados
        somando e atribuindo a variável global pi_global*/
        MPI_Reduce(&pi_local, &pi_global, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

        gettimeofday(&stop, 0); //fim do registro do tempo de execução

        if (my_rank == 0)
        {
            std::cout << "O valor aproximado de Pi é: " << pi_global << std::endl; 

            tempo_exec = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);

            std::cout << "O tempo de execução foi " << (std::scientific) << tempo_exec << std::endl;
        }
        
    }
    
    MPI_Finalize();
    return 0;
}