# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lchambos <lchambos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/12 14:58:34 by lchambos          #+#    #+#              #
#    Updated: 2026/03/26 16:46:53 by lchambos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc -Wall -Wextra -Werror -g3
NAME = minishell

SRC =	1_lexer/lexer_token.c \
		1_lexer/lexer_utils.c \
		1_lexer/lexer_utils2.c \
		1_lexer/lexer.c \
		2_parsing/check_errors.c \
		2_parsing/define_parsing.c \
		2_parsing/expand.c \
		2_parsing/expand_var.c \
		2_parsing/parsing_utils.c \
		2_parsing/parsing.c \
		3_main_exec/build_cmds.c \
		3_main_exec/cmd_type.c \
		3_main_exec/init_minishell.c \
		3_main_exec/launch_cmds.c \
		3_main_exec/minishell.c \
		4_builtins/builtin_cd.c \
		4_builtins/builtin_echo.c \
		4_builtins/builtin_env.c \
		4_builtins/builtin_exit.c \
		4_builtins/builtin_export.c \
		4_builtins/builtin_pwd.c \
		4_builtins/builtin_unset.c \
		4_builtins/export_utils.c \
		4_builtins/utils.c \
		5_pipe/files_pipe.c \
		5_pipe/parsing_pipe.c \
		5_pipe/pipe_exec.c \
		5_pipe/utils_pipe.c \
		6_utils/free_struct.c \
		6_utils/free.c \
		6_utils/signal_handlers.c \
		GNL/get_next_line.c \
		GNL/get_next_line_utils.c

OBJ = $(SRC:.c=.o)

LIB_DIR = libft
LIB_LIB = $(LIB_DIR)/libft.a

all: $(LIB_LIB) $(NAME)

$(LIB_LIB):
	make -C $(LIB_DIR)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIB_LIB) -lreadline -o $(NAME)
	@echo "\033[1;94mMinishell ready !\033[0;39m"
	
clean:
	rm -f $(OBJ)
	make -C $(LIB_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(LIB_LIB)

re: fclean all

.PHONY: all clean fclean re
