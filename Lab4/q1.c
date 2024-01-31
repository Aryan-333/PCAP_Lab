#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>

void ErrorHandler(int err_code){
    if(err_code != MPI_SUCCESS){
        char error_string[BUFSIZ];
        int length_err_string, err_class;
        MPI_Error_class(err_code, &err_class);
        MPI_Error_string(err_code, error_string, &length_err_string);
        printf("Error: Class - %d | String - %s\n", err_class, error_string);
    }
}

int main(int argc,char* argv[])
{
    int rank,size,fact=1,factsum,i,errorcode;

    MPI_Init(&argc,&argv);
    MPI_Errhandler_set(MPI_COMM_WORLD, MPI_ERRORS_RETURN);
   errorcode = MPI_Comm_size(MPI_COMM_WORLD, &size);
   ErrorHandler(errorcode);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   ErrorHandler(errorcode);


    for(i=1;i<=rank+1;i++){
        fact=fact*i;
    }

   errorcode= MPI_Scan(&fact,&factsum,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
        printf("Process %d: Local value = %d, Global sum = %d\n", rank+1, fact, factsum);

    if (rank==size-1) //Because it is scan it accumulate in last one
    {
        ErrorHandler(errorcode);
        printf("Sum of all the factorial=%d",factsum);
    }


    MPI_Finalize();
    exit(0);
}