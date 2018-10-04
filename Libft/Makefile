# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcrisp <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/11 20:23:35 by jcrisp            #+#    #+#              #
#    Updated: 2018/09/17 16:22:21 by jcrisp           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
CC = gcc
NAME = libft.a
CFLAGS = -Wall -Werror -Wextra
FILES = ./ft_isdigit.c ./ft_memset.c ./ft_strchr.c ./ft_strdup.c ./ft_strcmp.c ./ft_strcpy.c ./ft_strlen.c ./ft_strncpy.c ./ft_tolower.c ./ft_toupper.c
OBJ = ./ft_isdigit.o ./ft_memset.o ./ft_strchr.o ./ft_strdup.o ./ft_strcmp.o ./ft_strcpy.o ./ft_strlen.o ./ft_strncpy.o ./ft_tolower.o ./ft_toupper.o
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
