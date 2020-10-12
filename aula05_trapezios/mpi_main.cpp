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
    double Int; //valor da integral;
    double incremento; 
    int n; //quantidade de trapézios ou tamanho do problema

    /*Variaveis do Mpi*/
    int my_rank, comm_sz;

    /*Set manual dos valores de entrada*/
    x_a = 0.0; //ponto inicial
    x_b = 1.0; //ponto final 
    n = 200; //quantidade de trapézios ou tamanho do problema

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); //Tamanho do comunicador ou quantos processos inicializados
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); //Número do processo em execução

    if (my_rank != 0)
    {
        incremento = (x_b - x_a)/n;

        x_b = x_a + incremento; //diz até que ponto do intervalo o cálculo será feito

        Int = Int + (x_b - x_a)*(funcao(x_a) + funcao(x_b))/2.0; //cálculo da área do trapézio

        x_a = x_b; //atualiza a variável para o próximo vértice do trapézio ou ponto do intervalo
    } else
    {
        for (int q = 1; q < comm_sz; q++)
        {
            MPI_Recv(&pontos, 1, MPI_DOUBLE, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);


        }
        
    }
    
    MPI_Finalize();    

    return 0;
}