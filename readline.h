
#ifndef MY_READLINE
#define MY_READLINE

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define READLINE_READ_SIZE  1

typedef struct s_queue{
    bool eof_reached;
    int max_size;
    int size;
    int head;
    int tail;
    int leftover_size;
    char array[1024];
    char* leftover;
}queue;

queue* q;

bool is_empty(queue* q);
void init_queue();
int check_for_nl(char* buffer, int ret);
void enqueue(char* char_block, int end);
char* dequeue();
void init_my_readline();
char* my_readline(int fd);

#endif