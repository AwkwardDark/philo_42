# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/27 13:05:27 by pajimene          #+#    #+#              #
#    Updated: 2024/06/27 17:02:26 by pajimene         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= 	philo

CC 		= 	cc

CFLAGS 	= 	-Wall -Wextra -Werror -g3

SRC 	= 	 philo.c \
			parsing.c

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