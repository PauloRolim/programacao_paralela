#include <iostream>
#include <random>

#define tamanho_problema 16

int ordenacao(int vetor[tamanho_problema]){

    int var_local;
    int estagio;
    int i;

    for (estagio = 0; estagio < tamanho_problema; estagio++)
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
            for (i = 1; i < tamanho_problema - 1; i+=2)
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
    
    return vetor[tamanho_problema];
}


int main(){

    int vetor_entrada[tamanho_problema];
        
    std::cout << "Númermos que serão ordenados: " << std::endl;

    for (int i = 0; i < tamanho_problema; i++)
    {
        std::random_device rd;
        std::default_random_engine gen(rd());
        std::uniform_int_distribution<>dis(1,16);
        int valor_aleatorio = std::round(dis(gen));

        vetor_entrada[i] = valor_aleatorio;
        std::cout << vetor_entrada[i] << " ";

    }
    std::cout << std::endl;
    std::cout << "Números após ordenação: "  << std::endl;

    ordenacao(vetor_entrada);
   
    for (int o = 0; o < tamanho_problema; o++)
    {
        std::cout << vetor_entrada[o] << " ";
    }
    std::cout << std::endl;
    return 0;
}
