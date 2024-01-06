#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char stringtogglecase(char s)
{

        if(s>=65 && s<=90)
         s+=32;
        else if(s>=97 && s<=122)
         s-=32;

        return s;

}

int main(int argc,char *argv[]){
    int rank,size;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    char ch[20];
    strcpy(ch,argv[1]);

    
    printf("My rank is %d, my toggle character is %c\n",rank,stringtogglecase(ch[rank]));
    MPI_Finalize();
    return 0;
}