#include "mpi.h"
#include <stdio.h>
#include <math.h>
int main(int argc,char *argv[])
{
    int rank,size,x[10],y;
    int buffer[100];
    int sz = 100;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Status status;
    if(rank==0){
        MPI_Buffer_attach(buffer,sz);
        for(int i=1;i<size;i++){
        printf("Enter %d value in master process:",i);
        scanf("%d",&x[i]);
        }

        for(int i=1;i<size;i++){
        MPI_Bsend(&x[i],1,MPI_INT,i,1,MPI_COMM_WORLD);
        fprintf(stdout,"I have sent %d from process %d\n",x[i],rank);
        }
        MPI_Buffer_detach(&buffer,&sz);
    }
    else{
       MPI_Buffer_attach(buffer,sz);
        if(rank%2==0){
            MPI_Recv(&y,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
            fprintf(stdout,"I have received square %d in process %d\n",y*y,rank);
        }
        if(rank%2!=0){
            MPI_Recv(&y,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
            fprintf(stdout,"I have received cube %d in process %d\n",y*y*y,rank);

        }
        MPI_Buffer_detach(&buffer,&sz);
    }
    MPI_Finalize();
    return 0;
}