#include <iostream>
#include <mpi.h>

int main(void) {

	int my_rank, comm_sz;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	std::cout << "Proc" << my_rank << " of " << comm_sz " > Hello World!" 
	<< std::endl;

	MPI_Finalize();
	return 0;
}
