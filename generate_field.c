#include "bsq.h"

int gen_field(char *argv[]){
    char cmd[30];
    snprintf(cmd,sizeof(cmd),"perl sp_gen.pl %s %s %s",argv[1],argv[2],argv[3]);
	int status = system(cmd);
    if(status != 0){
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}