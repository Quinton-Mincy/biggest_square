#ifndef MY_BSQ
#define MY_BSQ
#include "readline.h"
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

typedef struct s_bsq{
    int i;//row coordinate
    int j;//column coordinate
    int size;//line side size
}bsq;
/*generate_field*/
int gen_field(char *argv[]);

/*parse_input.c*/
bool check_dimensions(char *n, char *m, char *d);
bool check_if_num(char *num);
bool get_dimensions(char *argv[],int *n, int *m);
bool valid_dimensions(char *argv[]);

/*utility.c*/
void free_memory(char **grid_str, bsq *square_info, int **matrix, int n);
void free_2d_arrays(int **matrix, char **grid, int n);
int min_sub_sqaure(int arr[]);

/*matrix.c*/
int** create_tabulation_matrix(int n, int fd);
bsq *init_bsq();
void populate_matrix(int** sol, int m, int fd);
int* populate_rows(char* row, int m);
char* populate_row_ch(int* row, int m);
char** reformat(int** matrix, int n, int m);
void update_matrix(int **matrix,bsq  *square_info,int i,int m);

/*display.c*/
void print_grid(char** str_grid, int n);
void print_matrix(int** matrix, int n, int m);
void x_marks(char** grid_str, bsq* square);

/*tabulate.c*/
bsq* maximal_square(int** matrix, int n, int m);
int my_bsq(char *argv[]);

#endif