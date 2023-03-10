#ifndef MY_BSQ
#define MY_BSQ
#include "readline.h"
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

int gen_field(char *argv[]);

/*parse_input.c*/
bool check_dimensions(char *n, char *m, char *d);
bool check_if_num(char *num);
bool get_dimensions(char *argv[],int *n, int *m);
bool valid_dimensions(char *argv[]);
#endif