#include <iostream>
#include <math.h>
#include <iomanip>
#include <sys/time.h>
#include <mpi.h>

/*Local de inserção da função que será integrada*/
double funcao (double x){
    //função do segundo grau
    return x*x + x + 2;

}

int main(int argc, char *arrgv[]){

    double x_a, x_b; //ínicio e fim do intervalo
    double Int_global; //valor da integral;
    double Int_local;
    double incremento; 
    int n_global; //quantidade de trapézios ou tamanho do problema
    int n_local;

    /*Variaveis do Mpi*/
    int my_rank, comm_sz;

    /*Set manual dos valores de entrada*/
    x_a = 0.0; //ponto inicial
    x_b = 1.0; //ponto final 
    n_global = 200; //quantidade de trapézios ou tamanho do problema

    /*Área Paralela*/
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); //Tamanho do comunicador ou quantos processos inicializados
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); //Número do processo em execução

    incremento = (x_b - x_a)/n_global;

    n_local = n_global/comm_sz;
    Int_local = 0.0;

    for (int i = 0; i < n_local; i++)
    {
        x_b = x_a + incremento; //diz até que ponto do intervalo o cálculo será feito

        Int_local = Int_local + (x_b - x_a)*(funcao(x_a) + funcao(x_b))/2.0; //cálculo da área do trapézio

        x_a = x_b; //atualiza a variável para o próximo vértice do trapézio ou ponto do intervalo
    }

    if (my_rank != 0)
    {
        MPI_Send(&Int_local, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
       
    } else
    {
        Int_global = Int_local;

        for (int q = 1; q < comm_sz; q++)
        {
            MPI_Recv(&Int_local, 1, MPI_DOUBLE, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            Int_global += Int_local;

        }
        
    }

    if (my_rank == 0)
    {
        std::cout << "Com um quantidade de " << n_global << " trapezios ";
        std::cout << "a área aproximada é de: " << Int_global << std::endl;
    }
    
    
    MPI_Finalize();    

    return 0;
}