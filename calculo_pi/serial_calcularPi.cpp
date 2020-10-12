#include <iostream>
#include <random>
#include <string>
#include <sys/time.h>

//função responsável por mostrar ao usuário como usar o programa
void como_usar(const std::string &programa)
{
    std::cout << "Uso do programa " << programa << " precisao <valor> " << std::endl;
}

/*Cálculo serial de Pi utilizando o método de integração de Monte Carlo*/

int main(int argc, char const *argv[]){

    int tamanho_problema;
    double acumulador;
    double pi_calculado;
    std::string comando;

    if (argc == 1)
    {
        como_usar(argv[0]);
        return 1;
    }

    comando = argv[1];

    if (comando != "precisao") 
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

    /*No laço são sorteados dois número reais. É realizado um teste para saber se o número sorteado
    está dentro da área circunferência de raio unitário*/
    for (int i = 0; i <= tamanho_problema; i++)
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

    pi_calculado = (4.0 * acumulador) / tamanho_problema;  

    gettimeofday(&stop, 0); //fim do registro do tempo de execução
    
    std::cout << "O valor aproximado de Pi é: " << pi_calculado << std::endl;  

    //cálculo do tempo de execução
    tempo_exec = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);

    std::cout << "O tempo de execução foi " << (std::scientific) << tempo_exec << std::endl;

    return 0;
}