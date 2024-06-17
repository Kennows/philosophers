NAME = philo

SRCS = philo.c \
	   error_utils.c \
	   ft_atol.c \
	   initialazation.c \
	   utils.c

OBJ = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Werror -Wextra -Wall

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: re fclean clean all
