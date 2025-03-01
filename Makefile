NAME = pipex

SRC = ./mandatory/ft_error.c ./mandatory/ft_split.c ./mandatory/ft_strjoin.c \
		./mandatory/pipex.c ./mandatory/pipex_help.c 

OBJS = ${SRC:.c=.o} 
CC = cc 
CFLAGS = -Wall -Wextra -Werror 
RM = rm -rf 

%.o : %.c ./mandatory/pipex.h 
	@$(CC) $(CFLAGS) -c $<  -o $@

$(NAME): $(OBJS)
	@${CC} $(CFLAGS) -o $(NAME) ${OBJS}

all: $(NAME)

clean: 
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re : fclean all 