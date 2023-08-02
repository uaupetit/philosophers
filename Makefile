NAME = philo

CFLAGS = -Wall -Wextra -Werror -g 

SRC = philo.c initialize.c thread.c dead_file.c philo_utils.c \

CC = cc
	
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re