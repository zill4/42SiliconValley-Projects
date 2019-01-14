# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcrisp <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/14 12:24:10 by jcrisp            #+#    #+#              #
#    Updated: 2019/01/14 12:38:45 by jcrisp           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

#	src / obj files
SRC	= main.c
OBJ	= $(addprefix $(OBJDIR), $(SRC:.c=.o))

#	compiler
CC	= gcc
CFLAGS	= -Wall -Wextra -Werror -g

#	ft library
FT	= ./libft/
FT_LIB	=	$(addprefix $(FT), libft.a)
FT_INC	=	-I ./libft
FT_LNK  = 	-L	./libft -l ft

#	MLX library
MLX		= ./miniLibX/
MLX_LIB = $(addprefix $(MLX), mlx.a)
MLX_INC	=	-I ./miniLibX
MLX_LNK =	-L ./miniLibX -l mlx -framework OpenGl -framework AppKit

#	directories
SRCDIR	= ./src/
INCDIR	= ./includes/
OBJDIR	= ./obj/

all: obj $(FT_LIB) $(MLX_LIB) $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	$(CC) $(CFLAGS) $(MLX_INC) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
	make -C $(FT)

$(MLX_LIB):
	make -C $(MLX)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_LNK) $(FT_LNK) -lm -o $(NAME)

clean:
		rm -rf $(OBJDIR)
		make -C $(FT) clean
		make -C $(MLX) clean
fclean:
		rm -rf $(NAME)
		make -C $(FT) fclean
re: fclean all
