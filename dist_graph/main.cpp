#include <mpi.h>
#include <stdio.h>

#include <cstdlib>
#include <cassert>

int main(int argc, char** argv) {

	const int randseed = 1337;

	// Initialize the MPI environment
	int mpi_provided_thread_level = 0;
	MPI_Init_thread(&argc, &argv, MPI_THREAD_SINGLE, &mpi_provided_thread_level);
	assert(MPI_THREAD_SINGLE <= mpi_provided_thread_level);

	// Get the number of processes
	int world_rank, world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	srand(randseed+world_rank);

	// Get the name of the processor
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int name_len;
	MPI_Get_processor_name(processor_name, &name_len);

	// Print off a hello world message
	printf("Hello world from processor %s, rank %d out of %d processors\n",
				processor_name, world_rank, world_size);

	MPI_Comm star_graph;
	MPI_Info unused_info;
	int star_create_result=0;

	MPI_Info_create(&unused_info);

	if(0 == world_rank){
		int *destinations = (int*)malloc((world_size)*sizeof(int));
		for(int i = 0;i<world_size;++i){
			destinations[i] = i;
		}

		star_create_result = MPI_Dist_graph_create_adjacent(MPI_COMM_WORLD,
                                   0, NULL,
                                   MPI_UNWEIGHTED,
                                   world_size - 1, destinations+1,
                                   MPI_UNWEIGHTED,
                                   unused_info, 0, &star_graph);
		free(destinations);

	}else{
		int source = 0;
		star_create_result = MPI_Dist_graph_create_adjacent(MPI_COMM_WORLD,
                                   1, &source,
                                   MPI_UNWEIGHTED,
                                   0, NULL,
                                   MPI_UNWEIGHTED,
                                   unused_info, 0, &star_graph);
	}

	int star_rank, star_size;
	MPI_Comm_rank(star_graph,&star_rank);
	MPI_Comm_size(star_graph,&star_size);
	// Print off a hello world message
	printf("Hello world from processor %s, rank %d out of %d processors, star %d of %d\n",
				processor_name, world_rank, world_size, star_rank, star_size);

	int foobar = rand() % 2000;
	int foobaz = 0;
	MPI_Reduce(&foobar, &foobaz, 1, MPI_INT, MPI_SUM, 0, star_graph);

	printf("rank %d : %d \n", world_rank, foobar);
	MPI_Barrier(MPI_COMM_WORLD);
	if(0 == star_rank){
		printf("Sum is %d \n",foobaz);
	}

	//////
	/// DISCONNECTED GRAPH???
	////

	// Finalize the MPI environment.
	MPI_Finalize();
}
