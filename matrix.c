#include "bsq.h"
#include "readline.h"

int** create_tabulation_matrix(int n, int fd){
    int** matrix = malloc(sizeof(int*)*n);
    populate_matrix(matrix,n,fd);
    return matrix;
}
void populate_matrix(int** sol, int m, int fd){
    init_my_readline();
    char* line;
    int index = 0;
    while( (line = my_readline(fd)) != NULL){
        sol[index] = populate_rows(line, m);
        index++;
    }
}
int* populate_rows(char* row, int m){
    int index = 0;
    int* int_row = malloc(sizeof(int)*m);
    while(row[index]!='\0'){
        if(row[index] == 'o'){
            int_row[index] = 0;
        }else{
            int_row[index] = 1;
        }
        index++;
    }
    return int_row;
}
char* populate_row_ch(int* row, int m){
    int index = 0;
    char* char_row = malloc(sizeof(char)*m+1);
    while(index < m){
        if(row[index] == 0){
            char_row[index] = 'o';
        }else{
            char_row[index] = '.';
        }
        index++;
    }
    char_row[index] = '\0';
    return char_row;
}
char** reformat(int** matrix, int n, int m){
    // print_matrix(matrix,n,m);
    char** grid_str = malloc(sizeof(char*)*n);
    int i = 0;
    while(i < n){
        grid_str[i] = populate_row_ch(matrix[i],m);
        i++;
    }
    return grid_str;
}