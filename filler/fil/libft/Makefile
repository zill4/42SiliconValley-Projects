# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcrisp <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/11 20:23:35 by jcrisp            #+#    #+#              #
#    Updated: 2018/10/21 16:02:35 by jcrisp           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
CC = gcc
NAME = libft.a
CFLAGS = -Wall -Werror -Wextra
FILES = ./ft_atoi.c ./ft_memalloc.c ./ft_putchar.c ./ft_strcat.c ./ft_striter.c ./ft_strncmp.c ./ft_strsub.c \
./ft_bzero.c ./ft_memccpy.c ./ft_putchar_fd.c ./ft_strchr.c ./ft_striteri.c ./ft_strncpy.c ./ft_tolower.c \
./ft_isalnum.c ./ft_memchr.c ./ft_putendl.c ./ft_strclr.c ./ft_strjoin.c ./ft_strnequ.c ./ft_toupper.c \
./ft_isalpha.c ./ft_memcmp.c ./ft_putendl_fd.c ./ft_strcmp.c ./ft_strlcat.c ./ft_strnew.c \
./ft_isascii.c ./ft_memcpy.c ./ft_putnbr.c ./ft_strcpy.c ./ft_strlen.c ./ft_strnstr.c \
./ft_isdigit.c ./ft_memdel.c ./ft_putnbr_fd.c ./ft_strdel.c ./ft_strmap.c ./ft_strrchr.c \
./ft_isprint.c ./ft_memmove.c ./ft_putstr.c ./ft_strdup.c ./ft_strmapi.c ./ft_strsplit.c \
./ft_itoa.c ./ft_memset.c ./ft_putstr_fd.c ./ft_strequ.c ./ft_strncat.c ./ft_strstr.c ./ft_strtrim.c \
./ft_lstnew.c ./ft_lstdelone.c ./ft_lstdel.c ./ft_lstadd.c ./ft_lstiter.c ./ft_lstmap.c ./get_next_line.c
OBJ = $(FILES:%.c=%.o)

$(NAME): 
		$(CC) $(CFLAGS) -c $(FILES) -I libft.h
		ar rc $(NAME) $(OBJ)
		ranlib $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
