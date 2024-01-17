#include "mpi.h"
#include <stdio.h>
#include<string.h>


int main(int argc,char *argv[])
{
    int rank,size,N,M,A[100],B[100],R,c,i,length;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    char string[size * 3], str[100];
	if (rank == 0){
		printf("Enter the string of length %d : ", size * 3);
		scanf("%s", string);
		length = strlen(string);
		length /= size;
	}
        MPI_Bcast(&length, 1, MPI_INT, 0, MPI_COMM_WORLD);

        MPI_Scatter(string,length,MPI_CHAR,str,length,MPI_CHAR,0,MPI_COMM_WORLD);

        int sendResult = 0;
	     for (int i = 0; i < length; i++){
		if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u' || str[i] == 'A' || str[i] == 'E' || str[i] == 'I' || str[i] == 'O' || str[i] == 'U'){
			sendResult++;

        }
	       }
	sendResult = length - sendResult;
    printf("Process %d has %d non vowels\n",rank,sendResult);
    
        MPI_Gather(&sendResult,1,MPI_INT,B,1,MPI_INT,0,MPI_COMM_WORLD);
        int total=0;
        for(int i=0;i<size;i++){
            total = total+B[i];
        }
        if(rank==0){
        printf("The total non-vowels are : %d\n",total);
        }
        MPI_Finalize();
        return 0;
}