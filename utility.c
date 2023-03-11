#include "bsq.h"
void free_memory(char **grid_str, bsq *square_info, int **matrix, int n){
    free(square_info);
    free_2d_arrays(matrix,grid_str,n);
}
void free_2d_arrays(int **matrix, char **grid, int n){
    int i  = 0;
    /*free rows*/
    while(i<n){
        free(matrix[i]);
        free(grid[i]);
        i+=1;
    }
    /*free columns*/
    free(grid);
    free(matrix);
}
int min(int arr[]){
    int min = 10000;
    int index = 0;
    while(index < 3){
        if(arr[index] < min){
            min = arr[index];
        }
        index++;
    }
    return min+1;
}