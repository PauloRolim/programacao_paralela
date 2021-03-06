/* *********************************************************************                                                Exemplo teste     
 *   ******************************************************************** */

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //use sleep
#include "mpi.h"


MPI_Status status;

int main(int argc, char **argv)
{
	int numtasks,taskid;
  	struct timeval start, stop;

	int N = atoi(argv[1]); //tamanho do problema - parâmetro de entrada. Pode acusar warning porque não utilizei.

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

  
	/*---------------------------- master ----------------------------*/
	if (taskid == 0) {
    
		gettimeofday(&start, 0);
		sleep(1);
		gettimeofday(&stop, 0);

		FILE *fp;
		char outputFilename[] = "tempo_de_mm.txt";
	
		fp = fopen(outputFilename, "a");
		if (fp == NULL) {
			fprintf(stderr, "Can't open output file %s!\n", outputFilename);
			exit(1);
		}
	
		//testes de impressão no arquivo
		fprintf(fp, "\t%1.2e ", (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec));
		//fprintf(fp, "\t%d ",numtasks); //número de tasks mpi
		//fprintf(fp, "\t%d ",N+1); //tamanho do problema+1

		fclose(fp);
  }
  else{
		/*---------------------------- worker----------------------------*/
		//DO NOTHING
  }

  MPI_Finalize();
  return 0;
}
