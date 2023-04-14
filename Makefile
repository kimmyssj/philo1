# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeojeon <jeojeon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/14 18:15:42 by jeojeon           #+#    #+#              #
#    Updated: 2023/04/15 00:21:45 by seungjki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Werror -Wall -Wextra
SRCS = $(wildcard *.c)

OBJS = $(SRCS:.c=.o)
RM = rm -f

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJS)

fclean :
	make clean
	$(RM) $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re
