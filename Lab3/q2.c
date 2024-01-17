#include "mpi.h"
#include <stdio.h>

int main(int argc,char *argv[])
{
    int rank,size,N,M,A[100],B[100],R[100],c,i;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if(rank==0){
        printf("Enter value of M\n");
        scanf("%d",&M);
        N=size;
        printf("Enter %d values:\n",N);
        for(i=0;i<N*M;i++){
            scanf("%d",&A[i]);
        }
    }
        MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);

        MPI_Scatter(A,M,MPI_INT,B,M,MPI_INT,0,MPI_COMM_WORLD);
        for(int i=0;i<M;i++){
        fprintf(stdout,"I have received %d in process %d\n",B[i],rank);
        }
        fflush(stdout);
        
        int sendResult = 0;
	    for (int i = 0; i < M; i++)
		    sendResult += B[i];

	    sendResult /= M;
        MPI_Gather(&sendResult,1,MPI_INT,R,1,MPI_INT,0,MPI_COMM_WORLD);
        if(rank==0){
        for(int i=0;i<size;i++){
        fprintf(stdout,"I root have received %d in process \n",R[i]);
        }
            int Final = 0;
	    for (int i = 0; i < size; i++)
		    Final += R[i];

	    Final /= size;

        printf("Total Average is %d\n",Final);
        }
        MPI_Finalize();
        return 0;
    }