NAME = philo

CC = cc

CFLAGS = -Werror -Wall -Wextra -pthread -g -fsanitize=thread

SRC = ./srcs/main.c \
	./srcs/input_check.c \
	./srcs/helper_func.c \
	./srcs/actions.c \
	./srcs/police.c \
	./srcs/utils.c \
	./srcs/mutexes.c

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re:	fclean all

PHONY: clean fclean all
