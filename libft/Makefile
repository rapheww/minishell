# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lchambos <lchambos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/04 15:46:15 by lchambos          #+#    #+#              #
#    Updated: 2026/02/25 23:58:24 by lchambos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC =	ft_isalpha.c	ft_memchr.c	ft_memset.c	ft_strlen.c	ft_tolower.c	ft_strrchr.c \
	ft_atoi.c	ft_isascii.c	ft_memcmp.c	ft_strchr.c	ft_strncmp.c	ft_toupper.c \
	ft_bzero.c	ft_isdigit.c    ft_memcpy.c	ft_strlcat.c	ft_strnstr.c	ft_isprint.c \
	ft_memmove.c	ft_strlcpy.c	ft_calloc.c	ft_strdup.c	ft_itoa.c	ft_isalnum.c \
	ft_strmapi.c	ft_strtrim.c	ft_substr.c	ft_split.c	ft_striteri.c	ft_strjoin.c \
	ft_putendl_fd.c	ft_putnbr_fd.c	ft_putstr_fd.c	ft_putchar_fd.c	ft_strcmp.c

OBJS =  ${SRC:.c=.o}

.c.o:
	cc -Wall -Wextra -Werror -I . -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
	ar rcs ${NAME} ${OBJS}

all: ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

bonus: ${OBJS}
	ar rcs ${NAME} ${OBJS}

.PHONY: all clean fclean re
