#include <iostream>
#include <random>

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
    double pi;
    double pontos = sorteio(10000);

    pi = (4.0 * pontos) / 10000; // onde divisor é igual a quantidade de pontos sorteados

    std::cout << "o valor de pi e " << (double)pi << std::endl;

    return 0;
}