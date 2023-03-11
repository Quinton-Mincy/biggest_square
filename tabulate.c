#include "bsq.h"
bsq *init_bsq(){
    bsq *square_info = malloc(sizeof(bsq));
    square_info->i = 0;
    square_info->j = 0;
    square_info->size = 0;
    return square_info;
}
void update_matrix(int **matrix,bsq  *square_info,int i,int m){
    int j = 1;
    while(j < m){
        if(matrix[i][j] == 1){
            /*in order, the neighbor above, oblique to, and to the left of the bottom right corner of the supposed square*/
            int neighbor_arr[] = {matrix[i-1][j], matrix[i-1][j-1], matrix[i][j-1]};
            /*
            minimum value will default to one. any value larger than one signifies that a larger square exists beyond the current one
            the minimum value will actually denote the largest square that can exist at that given coordinate, given that the current
            coordinate is taken as the bottom right-hand corner of a supposed square
            */
            int minimum = min_sub_sqaure(neighbor_arr);
            matrix[i][j] = minimum;
            /*update coorinates and size of current largest sub-sqaure*/
            if(minimum > square_info->size){
                square_info->i = i;
                square_info->j = j;
                square_info->size = minimum;
            }
        }
        j++;
    }
}
bsq* maximal_square(int** matrix, int n, int m){
    /*
    i and j start at one because the uppermost coordinate on the left corner, and any
    nodes at the top-most row and left-most column for that matter, cannot be the bottom
    right hand corner of a square, so they are ignored
    */
    int i = 1;
    bsq* square_info = init_bsq();
    while(i < n){
        update_matrix(matrix,square_info,i,m);
        i++;
    }
    return square_info;
}
int my_bsq(char *argv[]){
    /*get and confirm specified dimensions are valid*/
    int n;
    int m;
    if(!get_dimensions(argv,&n,&m)){
        return EXIT_FAILURE;
    }
    /*generate text file with perl script*/
    gen_field(argv);
    /*create and populate matrix, substituting obstacles (*) and open spaces with zeros and ones, respectively*/
    int fd = open("./square.txt",O_RDWR,0644);
    int** matrix = create_tabulation_matrix(n,fd);
    /*use dynamic programming tabulation to transform the matrix and find largest square */
    bsq* square_info = maximal_square(matrix,n,m);
    /*print dimensions and coordinate of square (bottom right corner)*/
    printf("{size: %dx%d,i: %d,j: %d}\n",square_info->size,square_info->size,square_info->i,square_info->j);
    //print_matrix(matrix,n,m);
    /*translate matrix of ones and zeros to 2D character array representing original field*/
    char** grid_str = reformat(matrix,n,m);
    /*use the square struct to determine location and size of square, and change corresponding characters to x's. Then print*/
    x_marks(grid_str,square_info);
    print_grid(grid_str,n);
    
    free_memory(grid_str,square_info,matrix,n);
    close(fd);
    return 0;
}