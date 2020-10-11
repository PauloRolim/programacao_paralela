#include <iostream>
#include <math.h>

/*Local de inserção da função que será integrada*/
double funcao (double x){
    //função exponecial
    return x*x + x + 2;

}

int main(int argc, char *arrgv[]){

    double x_a, x_b; //ínicio e fim do intervalo
    double Int; //valor da integral;
    double incremento; 
    int n; //quantidade de trapézios
    
    /*Set manual dos valores de entrada*/
    x_a = 0.0; //ponto inicial
    x_b = 1.0; //ponto final 
    n = 100; //quantidade de trapézios ou intervalos

    incremento = (x_b - x_a)/n; //subdivide o cálculo conforme a quantidade de trapézios selecionada

    Int = 0.0;

    for (int i = 0; i < n; i++)
    {
        x_b = x_a + incremento; //diz até que ponto do intervalo o cálculo será feito

        Int = Int + (x_b - x_a)*(funcao(x_a) + funcao(x_b))/2.0; //cálculo da área do trapézio

        x_a = x_b; //atualiza a variável para o próximo vértice do trapézio ou ponto do intervalo
    }

    std::cout << "A área aproximada pela regra dos trapezios e: " << Int << std::endl;
   
    return 0;
}