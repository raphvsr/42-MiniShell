# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rvasseur <raphael.vasseur@proton.me>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/30 12:00:00 by p0ubelle          #+#    #+#              #
#    Updated: 2026/08/27 14:41:14 by rvasseur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = minishell

CC          = cc
CFLAGS      = -Wall -Wextra -Werror
INCLUDES    = -I./src -I./libft

LIBFT_DIR   = ./libft
LIBFT       = $(LIBFT_DIR)/libft.a

SRCS        =	src/main.c \
				src/env/env_utils.c \
				src/builtins/cd.c src/builtins/echo.c src/builtins/exit.c src/builtins/env.c \
				src/builtins/export.c src/builtins/pwd.c src/builtins/unset.c \
				src/errors/free_env.c src/errors/err_utils.c \
				src/env/env_utils2.c \
				src/exec/executor.c \
				src/parsing/parsing_utils.c \
				src/parsing/lexer/split_line.c \
				src/parsing/lexer/lexer.c \
				src/env/env_utils3.c \
 				src/signals/signals.c

OBJS        = $(SRCS:.c=.o)

HEADER      = src/minishell.h

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

test_redirs: $(LIBFT)
	$(CC) -g3 $(CFLAGS) $(INCLUDES) test_redirs.c src/exec/*.c src/env/*.c src/builtins/*.c src/errors/*.c src/signals/*.c $(LIBFT) -lreadline -o test_redirs ./test_redirs

bonus: all

.PHONY: all clean fclean re bonus FORCE
