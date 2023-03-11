CC = gcc
CFLAGS += -Wall -Werror -Wextra
CFLAGS_DEBUG = $(CFLAGS)
MAIN = my_bsq
SRCS = my_bsq.c readline.c generate_field.c parse_input.c utility.c display.c matrix.c tabulate.c
OBJS = $(SRCS:.c=.o) 

all: $(MAIN)

$(MAIN): $(OBJS)
		$(CC) $(CFLAGS) -o $@ $(LINKERFLAG) $^

clean:
		$(RM) -f $(OBJS)

fclean: clean
		$(RM) -f $(MAIN) $(DEBUG)

re: fclean all