# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: p0ubelle <p0ubelle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/30 12:00:00 by p0ubelle          #+#    #+#              #
#    Updated: 2026/05/30 12:00:00 by p0ubelle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = minishell

CC          = cc
CFLAGS      = -Wall -Wextra -Werror
INCLUDES    = -I./src -I./libft

LIBFT_DIR   = ./libft
LIBFT       = $(LIBFT_DIR)/libft.a

SRCS        = src/main.c \
              src/env/env_utils.c \
              src/builtins/cd.c \
              src/builtins/echo.c \
              src/builtins/env.c \
              src/builtins/exit.c \
              src/builtins/export.c \
              src/builtins/pwd.c \
              src/builtins/unset.c

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

bonus: all

.PHONY: all clean fclean re bonus
