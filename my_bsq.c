#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/stat.h>

#include "readline.h"

typedef struct s_bsq{
    int i;//row coordinate
    int j;//column coordinate
    int size;//line side size
}bsq;

int** create_sol_matrix(int n){
    int** sol = malloc(sizeof(int*)*n);
    return sol;
}

char* reverse_string(char* str){
    int endex = strlen(str) -1;
    int index = 0;
    while(index < endex){
        char temp = str[index];
        str[index] = str[endex];
        str[endex] = temp;
        index++;
        endex--;
    }
    return str;
}

char* itoa(int num){
    char str[1024] = {'\0'};
    int i = 0;
    if(num != 0){
        while(num != 0){
            str[i] = (num%10) + '0';
            num/=10;
            i++;
        }
    }else{
        str[0] = 48;
    }
    char* final = strdup(str);
    if(strlen(final)>1){
        return reverse_string(final);
    }
    return final;
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


void populate_matrix(int** sol, int m, int fd){
    init_my_readline();
    char* line;
    int index = 0;
    while( (line = my_readline(fd)) != NULL){
        sol[index] = populate_rows(line, m);
        index++;
    }
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

bsq* maximal_square(int** matrix, int n, int m){
    int i = 1;
    bsq* square = malloc(sizeof(bsq));
    while(i < n){
        int j = 1;
        while(j < m){
            if(matrix[i][j] == 1){
                int arr[] = {matrix[i-1][j], matrix[i-1][j-1], matrix[i][j-1]};
                int minimum = min(arr);
                matrix[i][j] = minimum;
                if(minimum > square->size){
                    square->i = i;
                    square->j = j;
                    square->size = minimum;
                }
            }
            j++;
        }
        i++;
    }
    return square;
}

void print_grid(char** str_grid, int n){
    int i = 0;
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

int my_bsq(char *argv[]){
    char cmd[30];
    snprintf(cmd,sizeof(cmd),"perl sp_gen.pl %s %s %s",argv[1],argv[2],argv[3]);
	int status = system(cmd);
    if(status != 0){
        return 1;
    }

    int fd = open("./square.txt",O_RDWR,0644);
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    // int density = atoi(argv[3]);

    int** matrix = create_sol_matrix(n);
    populate_matrix(matrix,m,fd);
    bsq* square = maximal_square(matrix,n,m);
    printf("{size: %d,i: %d,j: %d}\n",square->size,square->i,square->j);

    print_matrix(matrix,n,m);
    char** grid_str = reformat(matrix,n,m);
    x_marks(grid_str,square);

    printf("\n");
    // print_grid(grid_str,n);

    free(grid_str);
    free(square);
    free(matrix);

    close(fd);
    return 0;
}

int main(int argc, char *argv[]){
    if(argc!=4){
        printf("Number of arguments (%d) not valid.\n",argc);
        return 1;
    }
    my_bsq(argv);
    return 0;
}