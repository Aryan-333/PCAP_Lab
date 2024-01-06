#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char *argv[]){
    int rank,size;
    int a= atoi(argv[1]);
    int b = atoi(argv[2]);
    printf("The two numbers are %d and %d\n",a,b);

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    
    if(rank==0){
        printf("Addition is %d\n", a+b);
    }
        if(rank==1){
        printf("Subtraction is %d\n", a-b);
    }    if(rank==2){
        printf("Multiplication is %d\n", a*b);
    }    if(rank==3){
        printf("Division is %d\n", a/b);
    }
    MPI_Finalize();
    return 0;
}