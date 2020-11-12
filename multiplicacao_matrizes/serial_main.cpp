#include <iostream>

#define tamanho_problema 3

void multiplicar(int matrizA[tamanho_problema][tamanho_problema], 
                 int matrizB[tamanho_problema][tamanho_problema],
                 int matrizC[tamanho_problema][tamanho_problema]){
    
    for (int i = 0; i < tamanho_problema; i++)
    {
        for (int j = 0; j < tamanho_problema; j++)
        {
            matrizC[i][j] = matrizA[i][j] * matrizB[i][j];
        }
    }
}

void mostraMatriz(int matriz[tamanho_problema][tamanho_problema]){
    for (int i = 0; i < tamanho_problema; i++)
    {
        for (int j = 0; j < tamanho_problema; j++){
            std::cout << matriz[i][j] << " | ";
        }
        std::cout << "\n";
    }
    std::cout << "\n\n"; 
}

int main(){

    int matrizA[3][3] = {1, 2, 3,
                         4, 5, 6,
                         7, 8, 9 };

    int matrizB[3][3] = {9, 8, 7,
                         6, 5, 4,
                         3, 2, 1};

    int matrizC[3][3];

    multiplicar(matrizA, matrizB, matrizC);

    mostraMatriz(matrizA);
    mostraMatriz(matrizB);
    mostraMatriz(matrizC);

    return 0;
}