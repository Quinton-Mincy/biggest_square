#include "bsq.h"
#include "readline.h"
int main(int argc, char *argv[]){
    if(argc!=4){
        printf("Number of arguments (%d) not valid.\n",argc);
        return 1;
    }
    return my_bsq(argv);
}