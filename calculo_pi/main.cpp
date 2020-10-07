#include <iostream>
#include <iomanip>
#include <random>
#include <string>
#include <sys/time.h>

//função responsável por mostrar ao usuário como usar o programa
void como_usar(const std::string &programa)
{
    std::cout << "Uso do programa " << programa << " tamanho <valor> " << std::endl;
}

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

int main(int argc, char const *argv[])
{      
    int tamanho_problema;
    std::string comando;

    if (argc == 1)
    {
        como_usar(argv[0]);
        return 1;
    }
    
    comando = argv[1];    //testes das entradas fornecidas pelo usuário

    if (comando != "tamanho")
    {
        como_usar(argv[0]);
        return 1;
    }

    if (argc == 2)
    {
        std::cout << "Informe agora o tamanho do problema para calcular PI" << std::endl;
        std::cin >> tamanho_problema;
    } else
    {
        comando = atoi(argv[2]);
    }
       
    struct timeval start, stop; /* código fornecido pelo professor para registrar o tempo de execução */
    double tempo_exec;
    gettimeofday(&start, 0);//início do registro do tempo de execução
    
    double pi; //variável criada para armazenar o resultado do cálculo

    double pontos = sorteio(tamanho_problema);

    /* utilizei o método de Monte Carlo para calcular o valor aproximado de Pi */
    pi = (4.0 * pontos) / tamanho_problema; // onde divisor é a quantidade de pontos sorteados (x²+y²)

    gettimeofday(&stop, 0); //fim do registro do tempo de execução

    //cálculo do tempo de execução
    tempo_exec = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    
    //exibe na tela o valor aproximado de Pi
    std::cout << "o valor de pi e " << (double)pi << std::endl;
    
    //exibe na tela o tempo de execução em notação científica
    std::cout << "O tempo de execução foi " << (std::scientific) << tempo_exec << std::endl; 
    return 0;
}