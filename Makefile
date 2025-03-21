NAME = pipex
NAME_BONUS = pipex_bonus

SRC = ./mandatory/ft_error.c ./mandatory/ft_split.c ./mandatory/ft_strjoin.c \
		./mandatory/pipex.c ./mandatory/pipex_help.c ./mandatory/pipex_help2.c \

SRC_BONUS = bonus/ft_error_bonus.c bonus/get_next_line_help_bonus.c bonus/get_next_line_bonus.c \
			bonus/pipex_help_bonus.c bonus/pipex_bonus.c bonus/ft_split_bonus.c bonus/ft_strjoin_bonus.c \
			bonus/ft_itoa_bonus.c bonus/here_doc_bonus.c bonus/pipex_help2_bonus.c

OBJS = ${SRC:.c=.o} 
OBJS_BONUS = ${SRC_BONUS:.c=.o}
CC = cc 
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf 


$(NAME): $(OBJS)
	@${CC} $(CFLAGS) -o $(NAME) ${OBJS}

$(NAME_BONUS): $(OBJS_BONUS)
	@${CC} $(CFLAGS) -o $(NAME_BONUS) ${OBJS_BONUS}

./mandatory/%.o: ./mandatory/%.c ./mandatory/pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus/%.o: bonus/%.c bonus/pipex_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@


all: $(NAME)

bonus: $(NAME_BONUS)

clean: 
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all 