
/**
 *
 * Name : Saurabh Chaure
 * Assignment 1
 *
 */

#include "mpi.h"
#include <stdio.h>
#include "math.h"
#define NBIN 10000000

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
double partial, sum, avg, step;
double cpu1, cpu2;
double pi;

MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &myid);
MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

cpu1=MPI_Wtime();
step = 1.0 / NBIN;

int i;
double x;
for(i=myid ; i < NBIN ; i+= nprocs ){
	x = ( i + 0.5 ) * step;
	partial += 4.0/( 1.0 + x * x);
}

partial *= step;
pi = global_sum( partial );

cpu2=MPI_Wtime();
if(myid == 0 ){
	printf(" PI VALUE with %d processors : %f\n", nprocs, pi );
	printf(" RUNTIME OF THE PROGRAM : %f \n\n", cpu2-cpu1 );
}

MPI_Finalize();
}
