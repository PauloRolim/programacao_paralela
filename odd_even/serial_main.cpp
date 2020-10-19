#include <iostream>
#include <random>

#define tamanho_problema 17

int main(){

   

    int vetor[tamanho_problema];
    int estagio; 
    int i;
    int var_local;

    std::cout << "Númermos que serão ordenados: " << std::endl;

    for (i = 0; i < tamanho_problema; i++)
    {
        std::random_device rd;
        std::default_random_engine gen(rd());
        std::uniform_int_distribution<>dis(0,16);
        int valor_aleatorio = std::round(dis(gen));

        vetor[i] = valor_aleatorio;
        std::cout << vetor[i] << " ";

    }
    
    std::cout << std::endl;
    std::cout << "Números após ordenação: "  << std::endl;

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
    
    for (int o = 0; o < tamanho_problema; o++)
    {
        std::cout << vetor[o] << " " << std::endl;
    }
    

    return 0;
}
