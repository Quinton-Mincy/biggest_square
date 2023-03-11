#include "bsq.h"

int gen_field(int n, int m, int d){
    char cmd[30];
    snprintf(cmd,sizeof(cmd),"perl sp_gen.pl %d %d %d",n,m,d);
	int status = system(cmd);
    if(status != 0){
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}