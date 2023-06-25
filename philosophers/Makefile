CC=cc
FLAGS=-Wall -Werror -Wextra
SRCS=  philo.c utils.c utils1.c init.c
OBJS=$(SRCS:%.c=%.o)
NAME=philo

all: $(NAME)


$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS)  -o $(NAME)

%.o: %.c philo.h
	$(CC) $(FLAGS) $(INCLUDES)  -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all