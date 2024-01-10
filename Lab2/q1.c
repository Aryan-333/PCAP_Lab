#include "mpi.h"
#include <stdio.h>
#include <string.h>

void stringtogglecase(char *s)
{
    int i;
 
    for(i=0;s[i];i++)  
    {
        if(s[i]>=65 && s[i]<=90)
         s[i]+=32;
        else if(s[i]>=97 && s[i]<=122)
         s[i]-=32;
 	}

}

int main(int argc,char *argv[])
{
    int rank,size,x;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Status status;

    char ch[20];
    strcpy(ch,argv[1]);

    int n = strlen(argv[1]);


    if(rank==0){
        MPI_Ssend(ch,n,MPI_INT,1,1,MPI_COMM_WORLD);
        printf("I have sent %s from process 0\n",ch);
        MPI_Recv(ch,50,MPI_INT,1,2,MPI_COMM_WORLD,&status);
        printf("I have received %s in process 0\n",ch);
        fflush(stdout);
    }
    else{
        MPI_Recv(ch,50,MPI_INT,0,1,MPI_COMM_WORLD,&status);
        printf("I have received %s in process 1\n",ch);

        stringtogglecase(ch);
        printf("I have result %s in process 1\n",ch);

        MPI_Ssend(ch,n,MPI_INT,0,2,MPI_COMM_WORLD);
        printf("I have sent %s from process 1\n",ch);

        fflush(stdout);
    }
    MPI_Finalize();
    return 0;
}