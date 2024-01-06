#include "mpi.h"
#include <math.h>
#include <stdio.h>

int main(int argc,char *argv[]){
    int rank,size;
    int x=3;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    printf("My rank is %d in total %d processes\n",rank,size);
    printf("POW is --> %f\n ",pow(x,rank));
    MPI_Finalize();
    return 0;
}