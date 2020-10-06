#include <iostream>
#include <random>
#include <string>
#include <sys/time.h>

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
    
    comando = argv[1];

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
       
    struct timeval start, stop;
    double tempo_exec;
    gettimeofday(&start, 0);

    double pi;
    double pontos = sorteio(tamanho_problema);

    pi = (4.0 * pontos) / tamanho_problema; // onde divisor é igual a quantidade de pontos sorteados

    gettimeofday(&stop, 0);
    tempo_exec = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);

    std::cout << "o valor de pi e " << (double)pi << std::endl;
    std::cout << "O tempo de execução foi " << tempo_exec << std::endl;
    return 0;
}