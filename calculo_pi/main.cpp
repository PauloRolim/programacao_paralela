#include <iostream>
#include <random>





int main (){

    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_real_distribution<> real_dis(0, 1);
    
    double acertos = 0;
    double pi;
    
   // double Pontos_aleatorios = real_dis(gen);

    for (int i = 0; i < 10000; i++)
    {
        double x_real_randomico = real_dis(gen);
        double y_real_randomico = real_dis(gen);

        if (x_real_randomico * x_real_randomico + y_real_randomico * y_real_randomico < 1.0)
        {
            acertos++;
        }
        
    }
    
    pi = (4.0 * acertos)/ 10000;      // onde 10 é o numero de pontos sorteados

    std::cout << "o valor de pi e " << (double)pi << std::endl;

    return 0;
}