#include <iostream>

#define tamanho_problema 10

int main(){

    int vetor[tamanho_problema] = {29, 15, 36, 44, 92, 51, 67, 88, 33, 20};
    int estagio;
    int i;
    int var_local;

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
        std::cout << vetor[o] << std::endl;
    }
    

    return 0;
}
