# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rroland <rroland@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/27 20:45:20 by rroland           #+#    #+#              #
#    Updated: 2021/10/21 17:06:06 by rroland          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SOURCE = main.c dop_func.c init.c philo_die.c philo_eat.c

FLAGS = -Wall -Wextra -Werror

OBJECTS = $(SOURCE:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@gcc $(SOURCE) -o $(NAME) -g -lpthread

%.o:%.c
	@gcc -c $(FLAGS) $(SOURCE)

clean:
	@rm -rf $(OBJECTS)
fclean: clean
	@rm -rf $(NAME)
re: fclean all
