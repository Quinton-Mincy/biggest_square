CC = C:\ProgramData\chocolatey\bin\gcc.exe
CFLAGS += -Wall -Werror -Wextra
CFLAGS_DEBUG = $(CFLAGS)
MAIN = my_bsq
SRCS = my_bsq.c readline.c generate_field.c parse_input.c utility.c display.c matrix.c tabulate.c
OBJS = $(SRCS:.c=.o) 

all: $(MAIN)

$(MAIN): $(OBJS)
		$(CC) $(CFLAGS) -o $@ $(LINKERFLAG) $^

clean:
		del $(OBJS)

fclean: clean
		del $(MAIN).exe $(DEBUG).exe

re: fclean all