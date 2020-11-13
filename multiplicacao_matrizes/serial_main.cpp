#include <iostream>
#include <random>
#include <sys/time.h>

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

void preencherMatriz(int matriz[tamanho_problema][tamanho_problema]){
    
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<>dis(0,9);

    for (int i = 0; i < tamanho_problema; i++)
    {
        for (int j = 0; j < tamanho_problema; j++)
        {
            matriz[i][j] = std::round(dis(gen));
        }   
    }    
}

int main(){

    struct timeval start, stop;

    int matrizA[tamanho_problema][tamanho_problema];
    int matrizB[tamanho_problema][tamanho_problema];
    

    gettimeofday(&start, 0);

    preencherMatriz(matrizA);
    preencherMatriz(matrizB);

    mostraMatriz(matrizA);
    mostraMatriz(matrizB);

    gettimeofday(&stop, 0);

     FILE *fp;
		char outputFilename[] = "tempo_de_exe_serial.txt";
	
		fp = fopen(outputFilename, "a");
		if (fp == NULL) {
			fprintf(stderr, "Can't open output file %s!\n", outputFilename);
			exit(1);
		}
	
		//testes de impressão no arquivo
		fprintf(fp, "\t%1.2e ", (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec));
		fprintf(fp, "\t%d ",tamanho_problema); //tamanho do problema+1

		fclose(fp);

    return 0;
}