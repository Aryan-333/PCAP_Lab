#include "mpi.h"
#include <stdio.h>

int main(int argc,char *argv[])
{
    int rank,size,N,A[10],B[10],c,i;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if(rank==0){
        N=size;
        printf("Enter %d values:\n",N);
        for(i=0;i<N;i++){
            scanf("%d",&A[i]);
        }
    }
        MPI_Scatter(A,1,MPI_INT,&c,1,MPI_INT,0,MPI_COMM_WORLD);
        fprintf(stdout,"I have received %d in process %d\n",c,rank);
        fflush(stdout);
        int fact=1;
           for(i=1;i<=c;i++){    
                fact=fact*i;    
            }    
        c=fact;
        MPI_Gather(&c,1,MPI_INT,B,1,MPI_INT,0,MPI_COMM_WORLD);

        if(rank==0){
            fprintf(stdout,"The result gathered in the root\n");
            fflush(stdout);
            int sum=0;
            for(i=0;i<N;i++){
                sum = sum + B[i];
            }
            printf("The sum of factorial is %d",sum);
            fflush(stdout);
        }
        MPI_Finalize();
        return 0;
    }
