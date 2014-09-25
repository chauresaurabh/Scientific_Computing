
/**
 *
 * Name : Saurabh Chaure
 * Assignment 1
 *
 */

#include "mpi.h"
#include <stdio.h>
#include "math.h"
int nprocs; /* Number of processors */
int myid; /* My rank */
double global_sum(double partial) {

	int i;
	int partnerid;		

	unsigned int a = myid;	  

	double number = partial;
	double receivenumber = 0 ;

	MPI_Status status;

	int bitmask = 1;	
	
	for(bitmask=1;bitmask<nprocs;bitmask*=2){
	
		partnerid = myid ^ bitmask;	
	       
		MPI_Send(&number, 1, MPI_DOUBLE, partnerid,  10, MPI_COMM_WORLD);
		MPI_Recv(&receivenumber , 1,  MPI_DOUBLE, partnerid, 10, MPI_COMM_WORLD, &status);

		number = number + receivenumber;
	}

	return number;
}
main(int argc, char *argv[]) {
double partial, sum, avg;
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &myid);
MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
partial = (double) myid;
printf("Node %d has %le\n", myid, partial);
sum = global_sum(partial);

if (myid == 0) {
	printf(" %d - Processor Job,\t TOTAL SUM :%f \n",nprocs,sum);
	avg = sum/nprocs;
	printf("GLOBAL AVERAGE = %f\n\n\n", avg);}
MPI_Finalize();
}
