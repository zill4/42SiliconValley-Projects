# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcrisp <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/14 12:24:10 by jcrisp            #+#    #+#              #
#    Updated: 2019/03/20 16:11:11 by jcrisp           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ftprintf.a
#	src / obj files
# Folders of the source files (*.c)
SRC_DIR = src/
LIB_DIR = libft/src/

SRC_FILES =  arg.c hex.c num.c oct.c signed.c spec.c strings.c unsigned.c ft_printf.c
LIBFT_FILES = ft_atoi.c ft_bzero.c ft_isdigit.c ft_memalloc.c ft_putchar.c \
			  ft_putnchar.c ft_putstr.c ft_putunbr.c  \
			   ft_strdup.c ft_strlen.c ft_strncpy.c ft_strrev.c ft_memset.c\
			  ft_strsub.c ft_lower_str.c  ft_putchar.c ft_putstr.c ft_strnew.c \

# Source files path
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
LIBFT = $(addprefix $(LIB_DIR), $(LIBFT_FILES))

# Objects
OBJ = $(SRC_FILES:.c=.o) $(LIBFT_FILES:.c=.o)

# Flags
INC = -Iincludes/
FLAGS = -Wall -Wextra -Werror

# all rule
all: $(NAME)

# Compiling command
$(NAME):
	@gcc -c $(FLAGS) $(SRC) $(LIBFT) $(INC)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

# clean rule
clean:
	@/bin/rm -f $(OBJ)

# fclean rule
fclean: clean
	@/bin/rm -f $(NAME)

# re rule
re: fclean all

# phony
.PHONY: all clean fclean re
