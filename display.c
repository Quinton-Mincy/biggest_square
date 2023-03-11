#include "bsq.h"
void print_grid(char** str_grid, int n){
    int i = 0;
    printf("\n");
    while(i < n){
        int j = 0;
        while(str_grid[i][j]!= '\0'){
            printf("%c ",str_grid[i][j]);    
            j++;
        }
        printf("\n");
        i++;
    }
}
void print_matrix(int** matrix, int n, int m){
    int i = 0;
    while(i < n){
        int j = 0;
        while(j < m){
            printf("%d ",matrix[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}
void x_marks(char** grid_str, bsq* square){
    // printf("sqaure->i: %d, square->j: %d, square->size: %d\n",square->i,square->j,square->size);
    int i_start = square->i - ((square->size) -1);//row
    int i_end = square->i+1;

    int j_end = square->j+1;
    // printf("i_start: %d, i_end: %d, j_start: %d, j_end: %d ",i_start,i_end,j_start,j_end);
    while(i_start < i_end){
        int j_start = (square->j) - (square->size -1);//column
        while(j_start < j_end){
            grid_str[i_start][j_start] = 'x';
            j_start++;
        }
        i_start++;
    }
}