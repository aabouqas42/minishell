# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/10 20:25:49 by mait-elk          #+#    #+#              #
#    Updated: 2024/03/10 21:06:24 by mait-elk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Werror -Wextra
CC = cc $(CFLAGS)
INC = include/
SRCS = 
SRCS_O = $(SRCS:.c=.o)
NAME = minishell

all: $(NAME) 

$(NAME): $(SRCS_O) $(INC)$(NAME).h
	$(CC) $(NAME).c $(OBJ) -o $(NAME) -I $(INC)

%.o: %.c $(INC)$(NAME).h
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean 
	rm -f $(NAME)

re: fclean all

.PHONY: clean