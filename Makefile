# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rroland <rroland@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/27 20:45:20 by rroland           #+#    #+#              #
#    Updated: 2021/10/12 19:18:08 by rroland          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SOURCE = main.c dop_func.c init.c

OBJECTS = $(SOURCE:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@gcc $(SOURCE) -o $(NAME) -g -lpthread

%.o:%.c
	@gcc -c $(SOURCE)

clean:
	@rm -rf $(OBJECTS)
fclean: clean
	@rm -rf $(NAME)
re: fclean all
