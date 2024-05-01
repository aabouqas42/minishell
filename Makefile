# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/10 20:25:49 by mait-elk          #+#    #+#              #
#    Updated: 2024/05/01 16:53:30 by aabouqas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror  #-g -fsanitize=address
CC = cc $(CFLAGS)
INC = include/
LIBFT = libft/libft.a
SRCS = 	parsing/command_check.c parsing/check_redirections.c parsing/expand_input.c parsing/args_parsing.c \
		utils/global_utils.c \
		utils/minishell_utils.c split/ft_split.c split/ft_split_utils.c \
		utils/str/str_utils.c \
		utils/protected/protected_funcs.c\
		utils/matrix_utils/matrix.c \
		utils/data_init.c \
		io/io_utils.c\
		env/env_list.c env/env_sort.c  env/env_list_read.c  env/env_utils.c \
		env/env_free.c \
		builtins/cd.c builtins/echo.c builtins/pwd.c builtins/export.c \
		temp_utils.c \
		#multiples/
SRCS_O = $(SRCS:.c=.o)
NAME = minishell

all: $(NAME)
	@echo "\033[32mminishell Is Ready.\033[0m"

$(NAME): $(LIBFT) $(NAME).c $(SRCS_O) $(INC)$(NAME).h
	@echo "\033[32mCompiling Executable $(NAME) FROM [ $(SRCS_O) ]\033[0m"
	@$(CC) $(NAME).c $(SRCS_O) $(LIBFT) -lreadline -o $(NAME)

%.o: %.c $(INC)$(NAME).h
	@echo "\033[32mCompiling $<\033[0m"
	@$(CC) -c $< -o $@

$(LIBFT): 
	@echo "\033[32mCompiling LIFT\033[0m"
	@make -C libft/

clean:
	@echo "\033[32mCleaning Object Files...\033[0m"
	@make -C libft/ clean
	@rm -f $(SRCS_O)

fclean: clean 
	@echo "\033[32mCleaning Executable File & Library...\033[0m"
	@make -C libft/ fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean
