# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/10 20:25:49 by mait-elk          #+#    #+#              #
#    Updated: 2024/05/08 20:04:49 by mait-elk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
CC = cc $(CFLAGS)
INC = include/
LIBFT = libft/libft.a
SRCS = 	parsing/command_check.c parsing/check_redirections.c parsing/expand_input.c parsing/args_parsing.c \
		utils/global_utils.c \
		utils/minishell_utils.c split/ft_split.c split/ft_split_utils.c \
		utils/str/str_utils.c \
		utils/protected/protected_funcs.c\
		utils/matrix_utils/matrix.c \
		utils/data_init.c utils/free.c \
		io/io_utils.c\
		env/env_list.c env/env_sort.c  env/env_list_read.c  env/env_utils.c \
		env/env_free.c \
		heredoc/heredoc.c \
		builtins/cd.c builtins/echo.c builtins/pwd.c builtins/export.c \
		builtins/builtins.c \
		error/do_error.c \
		linked_lists/t_arg_instr.c linked_lists/t_cmd_instr.c linked_lists/free_linked_list.c
		#multiples/
SRCS_O = $(SRCS:.c=.o)
NAME = minishell

all: $(NAME)
	@echo "\033[32mminishell Is Ready.\033[0m"
#	Do This Steps First : \
	git clone https://github.com/Homebrew/brew.git ~/homebrew \
	cd ~/homebrew/bin/ \
	./brew install readline \
	if you have errors about dylib do this step : \
		export DYLD_LIBRARY_PATH=${HOME}/homebrew/Cellar/readline/8.2.10/lib"

$(NAME): $(LIBFT) $(NAME).c $(SRCS_O) $(INC)$(NAME).h
	@echo "\033[32mCompiling Executable $(NAME) FROM [ $(SRCS_O) ]\033[0m"
	@$(CC) $(NAME).c $(SRCS_O) -I ${HOME}/homebrew/Cellar/readline/8.2.10/include $(LIBFT) -L ${HOME}/homebrew/Cellar/readline/8.2.10/lib -lreadline -o $(NAME)

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

push : fclean
	@git add .
	@read -p "Enter commit message: " msg_push; \
	git commit -m "$$msg_push";
	@git push origin ${USER}

.PHONY: clean pull
