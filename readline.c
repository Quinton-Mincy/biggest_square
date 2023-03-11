#include "readline.h"
static queue *q = NULL;
bool is_empty(queue* q){
    return !(q->size);
}
void clear_buffer(char *buffer,int clearance){
    int i  = 0;
    while(i<clearance){
        buffer[i] = '\0';
        i++;
    }
}
void init_queue(){
    q = malloc(sizeof(queue));
    // bzero(q->array,128);
    q->eof_reached = false;
    q->size = 0;
    q->head = 0;
    q->tail = 0;
    q->leftover_size = 0;
    q->max_size = 1024;
    clear_buffer(q->array,1024);
    q->leftover = NULL;
}
int check_for_nl(char* buffer, int ret){
    int i = 0;
    while(i < ret){
        if(buffer[i] == '\n'){
            return i;
        }
        i++;
    }
    return -1;
}

void enqueue(char* char_block, int end){
    int i = 0;
    while(i < end){
        q->array[q->tail] = char_block[i];
        q->tail = (q->tail +1) % q->max_size;
        q->size++;
        i++;
    }
}
char* dequeue(){
    char* str = malloc(sizeof(char)*q->size+1);
    int i = 0;
    int end = q->size;
    while(i < end){//when n_loc is zero, then str is allocated as a string of size 1, with value of '\0'
        char curr_char = q->array[q->head];
        str[i] = curr_char;
        q->array[q->head] = '\0';
        q->head = (q->head +1) % q->max_size;
        q->size--;
        i++;
    }
    str[i] = '\0';
    return str;
}

void init_my_readline(){
    init_queue();
}

char* my_readline(int fd){
    // if(q->leftover!=NULL)
    //     printf("%s\n",q->leftover);
    if(fd == -1){
        return NULL;
    }
    if(q->eof_reached &&q->leftover == NULL){
        return NULL;
    }
    char* end_str = NULL;

    if(q->leftover != NULL){
        int nl_loc = check_for_nl(q->leftover,q->leftover_size);
        if(nl_loc==q->leftover_size-1){//if new line last character
            if(nl_loc==-1 ){//final newline in file
                return NULL;
            }
            enqueue(q->leftover,nl_loc);
            end_str = dequeue();
            clear_buffer(q->leftover,q->leftover_size);
            free(q->leftover);
            q->leftover_size = 0;
            q->leftover = NULL;
            return end_str;
        }else if(nl_loc>-1){//nl somewhere in the middle...or first character
            enqueue(q->leftover,nl_loc);
            end_str = dequeue();
            if((q->leftover_size-1)-nl_loc != 0){
                // printf("%d\n",q->leftover_size);
                char* new_leftovers = strdup(&q->leftover[nl_loc+1]);
                free(q->leftover);
                q->leftover = strdup(new_leftovers);
                q->leftover_size = (q->leftover_size-1)-nl_loc;
            }
            return end_str;
        }
        enqueue(q->leftover,q->leftover_size);//no nl in leftover
        free(q->leftover);
        q->leftover_size = 0;
        q->leftover = NULL;

    }
    int ret = 0;
    char buffer[READLINE_READ_SIZE+1];//make sure always null terminated
    clear_buffer(buffer,READLINE_READ_SIZE+1);
    int i = 0;
    
    while( (ret = read(fd,&buffer,READLINE_READ_SIZE)) !=0){
        if(i == 0 && buffer[0] == '\n'){
            return NULL;
        }
        if(ret == -1){
            printf("Cannot read file\n");
            return NULL;
        }
        if(ret != READLINE_READ_SIZE){
            q->eof_reached = true;
        }
        //////////////can make this into an array of struct funcitons
        int nl_loc = check_for_nl(&buffer[0], ret);
        if(nl_loc == -1){
            enqueue(&buffer[0], ret);
        }else{//if we find a new line, we need to return right after, saving the leftovers for the next function call
            enqueue(&buffer[0],nl_loc);
            if(nl_loc != READLINE_READ_SIZE-1){//if nl_loc is the last index of the buffer, then their are no leftovers (if newline is first character in buffer,leftovers are what follows?)
                char* leftover = strdup(&buffer[nl_loc+1]);
                q->leftover = leftover;//skip first occurence of newline, function call, if new line is first character, there is an empty line
                q->leftover_size = strlen(leftover)/sizeof(leftover[0]);
            }
            break;
        }
        //////////////can make this into an array of struct funcitons
        clear_buffer(buffer,READLINE_READ_SIZE+1);
        i++;
    }
    if( (ret == 0 && i == 0)){
        return NULL;
    }
    end_str = dequeue();
    return end_str;
}