#include "mpi.h"
#include <stdio.h>

int main(int argc,char *argv[]){
    int rank,size;
    int x=3;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    
    printf("My rank is --> %d\t",rank);
    if(rank%2==0){
        printf("Even thus \"Hello\"\n ");
    }
    else{
        printf("Odd thus \"World\"\n ");

    }
    MPI_Finalize();
    return 0;
}