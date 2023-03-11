#include "bsq.h"
bool check_dimensions(char *n, char *m, char *d){
    return ((check_if_num(n) && check_if_num(m)) && check_if_num(d));
}
bool check_if_num(char *num){
    int i = 0;
    /*will also rule out negative quantities*/
    while(num[i]!= '\0'){
        if(num[i]> 47 && num[i] < 58){
            i++;
        }else{
            return false;
        }
    }
    return true;
}
bool get_dimensions(char *argv[],int *n, int *m, int *d){
    if(!valid_dimensions(argv)){
        perror("Invalid dimensions");
        return false;
    }
    *n = atoi(argv[1]);
    *m = atoi(argv[2]);
    *d = atoi(argv[3]);
     /*if n and m are unequal, equal to zero, or invlalid input (atoi returns zero to non-numerical characters)*/
    if(*n != *m || (*n) * (*m) == 0){
        perror("Invalid dimensions");
        return false;
    }
    return true;
}
bool valid_dimensions(char *argv[]){
    return check_dimensions(argv[1],argv[2],argv[3]);
}