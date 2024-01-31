#include <mpi.h>
#include <stdio.h>
int calcOcc(int arr[], int ele)
{
    int count = 0;
    for (int i = 0; i < 3; i++)
    {
        printf("arr %d ele %d\n", arr[i], ele);
        if (arr[i] == ele)
            count++;
    }

    printf("count  is %d\n", count);

    return count;
}

void ErrorHandler(int err_code){
    if(err_code != MPI_SUCCESS){
        char error_string[BUFSIZ];
        int length_err_string, err_class;
        MPI_Error_class(err_code, &err_class);
        MPI_Error_string(err_code, error_string, &length_err_string);
        printf("Error: Class - %d | String - %s\n", err_class, error_string);
    }
}
void main(int argc, char **argv)
{
    int rank, size, ele, total, err_code;
    int arr[3][3];
    int subarr[3];

    MPI_Init(&argc, &argv);
   err_code = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   err_code = MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("enter 9 numbers : ");
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                scanf("%d", &arr[i][j]);
            }
        }
        printf("enter element to be searched : ");
        scanf("%d", &ele);
    }

    MPI_Bcast(&ele, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(arr, 3, MPI_INT, subarr, 3, MPI_INT, 0, MPI_COMM_WORLD);

    int occ = calcOcc(subarr, ele);

   err_code = MPI_Reduce(&occ, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0){
    ErrorHandler(err_code);
        printf("Total occurances of %d = %d\n", ele, total);
    }


    MPI_Finalize();
}