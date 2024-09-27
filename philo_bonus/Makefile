# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/27 13:05:27 by pajimene          #+#    #+#              #
#    Updated: 2024/09/23 11:25:15 by pajimene         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= 	philo_bonus

CC 		= 	cc

CFLAGS 	= 	-Wall -Wextra -Werror -g3

SRC 	= 	main.c \
			parsing.c \
			utils.c \
			simulation.c \
			display_eat.c \
			get_data.c

OBJ		= 	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 