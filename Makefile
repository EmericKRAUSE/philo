NAME		=	philo
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror

SRC			=	./src/main.c\
				./src/get_value.c\
				./src/init.c\
				./src/monitor.c\
				./src/parsing.c\
				./src/routine.c\
				./src/utils.c

OBJ			=	$(SRC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean:		clean
	rm -rf $(NAME)

re:		fclean all

.PHONY: all clean fclean re