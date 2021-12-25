#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define SIZE 5

int main(int argc, char **argv)
{
    int res[SIZE*SIZE];
    res[0] = 1;
    
    MPI_Init(&argc, &argv);
    int rank, tasks;
    MPI_Comm comm;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &tasks);

    int size[2] = {SIZE, SIZE};
    int periodic[2] = {0};
    // создание транспьютерной матрицы
    MPI_Cart_create(MPI_COMM_WORLD, 2, size, periodic, 0, &comm);
    
    int coords[2]; // Координаты процесса в матрице

    MPI_Cart_coords(comm, rank, 2, coords);
     
    int tmp_buf[SIZE];
    tmp_buf[0] = rank + 1;

    MPI_Status status;


    // 1 step 
    if(rank % 5 != 0) { // не первый столбец
        MPI_Send(&tmp_buf, 1, MPI_INT, rank-1, 0, comm);

        if(rank % 5 < 4) { // последний столбец не должен ничего принимать
            MPI_Recv(&tmp_buf, 1, MPI_INT, rank + 1, 0, comm, &status);
        }
    } 
    else {
        if(rank == 0) {
            MPI_Recv(&res[1], 1, MPI_INT, rank + 1, 0, comm, &status);
        } else {
            MPI_Recv(&tmp_buf[1], 1, MPI_INT, rank + 1, 0, comm, &status);
        }
    }
    
    MPI_Barrier(comm);

    // 2 step 
    if(rank % 5 != 0 && rank % 5 < 4 ) { // не первый и последний столбцы
        MPI_Send(&tmp_buf, 1, MPI_INT, rank - 1, 0, comm);

        if(rank % 5 < 3 ) { // не последние два столбца
            MPI_Recv(&tmp_buf, 1, MPI_INT, rank + 1, 0, comm, &status);
        }
    } 
    else if(rank %5 < 4) {
        if(rank == 0) { // (0,0)
            MPI_Recv(&res[2], 1, MPI_INT, rank+1, 0, comm, &status);
        } else { // другие элементы первого столбца
            MPI_Recv(&tmp_buf[2], 1, MPI_INT, rank + 1, 0, comm, &status);
        }
    }
    
    MPI_Barrier(comm);

    // 3 step 
    if(rank % 5 != 0 && rank % 5 < 3 ) { // не первый и последний столбцы
        MPI_Send(&tmp_buf, 1, MPI_INT, rank - 1, 0, comm);

        if(rank % 5 < 2 ) { // не последние два столбца
            MPI_Recv(&tmp_buf, 1, MPI_INT, rank + 1, 0, comm, &status);
        }
    } 
    else if(rank %5 < 3) {
        if(rank == 0) { // (0,0)
            MPI_Recv(&res[3], 1, MPI_INT, rank+1, 0, comm, &status);
        } else { // другие элементы первого столбца
            MPI_Recv(&tmp_buf[3], 1, MPI_INT, rank + 1, 0, comm, &status);
        }
    }
    
    MPI_Barrier(comm);

    // 4 step 
    if(rank % 5 != 0 && rank % 5 < 2 ) { // не первый и последний столбцы
        MPI_Send(&tmp_buf, 1, MPI_INT, rank - 1, 0, comm);
    } 
    else if(rank %5 < 2) {
        if(rank == 0) { // (0,0)
            MPI_Recv(&res[4], 1, MPI_INT, rank+1, 0, comm, &status);
        } else { // другие элементы первого столбца
            MPI_Recv(&tmp_buf[4], 1, MPI_INT, rank + 1, 0, comm, &status);
        }
    }
    
    MPI_Barrier(comm);


    // 5 step 
    if(rank % 5 == 0 ) { // первый столбец
        if(rank != 0) {
            MPI_Send(&tmp_buf, 5, MPI_INT, rank - 5, 0, comm);
            if(rank < 20) {
                MPI_Recv(&tmp_buf, 5, MPI_INT, rank + 5, 0, comm, &status);
            }
        } else {
            MPI_Recv(&res[5], 5, MPI_INT, rank+5, 0, comm, &status);
        }        
    } 
    
    MPI_Barrier(comm);

    // 6 step 
    if(rank % 5 == 0 ) { // первый столбец
        if(rank != 0 && rank < 20) {
            MPI_Send(&tmp_buf, 5, MPI_INT, rank - 5, 0, comm);
            if(rank < 15) {
                MPI_Recv(&tmp_buf, 5, MPI_INT, rank + 5, 0, comm, &status);
                
            }
        } else if(rank==0){
            MPI_Recv(&res[10], 5, MPI_INT, rank+5, 0, comm, &status);
        }        
    } 
    
    MPI_Barrier(comm);

    // 7 step 
    if(rank % 5 == 0 ) { // первый столбец
        if(rank != 0 && rank < 15) {
            MPI_Send(&tmp_buf, 5, MPI_INT, rank - 5, 0, comm);
            if(rank < 10) {
                MPI_Recv(&tmp_buf, 5, MPI_INT, rank + 5, 0, comm, &status);
                
            }
        } else if(rank==0){
            MPI_Recv(&res[15], 5, MPI_INT, rank+5, 0, comm, &status);
        }        
    } 
    
    MPI_Barrier(comm);
   
   // 8 step 
    if(rank % 5 == 0 ) { // первый столбец
        if(rank != 0 && rank < 10) {
            MPI_Send(&tmp_buf, 5, MPI_INT, rank - 5, 0, comm);
            
        } else if(rank==0){
            MPI_Recv(&res[20], 5, MPI_INT, rank+5, 0, comm, &status);
        }        
    } 
    
    MPI_Barrier(comm);



    if(rank == 0) {
        printf("\n+------+------+------+------+------+------+\n");
        printf("|   \\  | (,0) | (,1) | (,2) | (,3) | (,4) |\n");
        printf("+------+------+------+------+------+------+\n");
        for(int i =0; i < SIZE; i++) {
            printf("| (%d,) |", i);
            for(int j =0; j < SIZE; j++) {
                if(res[SIZE*i + j] < 10) {
                    printf("  %d   |", res[SIZE*i + j]); 
                } else {
                    printf("  %d  |", res[SIZE*i + j]); 
                }
            }
            printf("\n+------+------+------+------+------+------+\n");
        }
    }


    MPI_Finalize();

    return 0;
}
