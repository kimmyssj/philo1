SRC_A = $(wildcard *.c)

OBJ_A = $(SRC_A:.c=.o)

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread

all : $(NAME)

$(NAME) : $(OBJ_A)
	$(CC) $(CFLAGS) $(OBJ_A) -o $(NAME)

OBJ_A :
	$(CC) $(CFLAGS) -c $(SRC_A) -o $(OBJ_A)

clean :
	rm -f *.o
	
fclean :
	rm -f *.o
	rm -f philo

re : 
	make fclean
	make all

.PHONY : all clean fclean re
