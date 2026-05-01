# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttakemur <ttakemur@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/23 21:14:32 by ttakemur          #+#    #+#              #
#    Updated: 2026/05/02 01:31:14 by ttakemur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libftprintf.a
CC := cc
LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a
CFLAGS := -Wall -Wextra -Werror -I $(LIBFT_DIR) -I includes

SRC_DIR := src
SRCS := $(SRC_DIR)/ft_printf.c \
		$(SRC_DIR)/ft_putchar.c \
		$(SRC_DIR)/ft_puthex.c \
		$(SRC_DIR)/ft_putnbr.c \
		$(SRC_DIR)/ft_putptr.c \
		$(SRC_DIR)/ft_putstr.c \
		$(SRC_DIR)/ft_putunsigned.c

OBJS := $(SRCS:.c=.o)

HEADERS := includes/ft_printf.h

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	cp $(LIBFT) $(NAME)
	ar rcs $(NAME) $(OBJS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re