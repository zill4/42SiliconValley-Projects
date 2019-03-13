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

NAME = ft_printf

#	src / obj files
SRC	= ./ft_printf.c ./pf_putstr.c ./pf_putnbr.c ./pf_putchar.c ./pf_atoib.c ./pf_atoib_cap.c ./ft_space.c
OBJ	= $(addprefix $(OBJDIR), $(SRC:.c=.o))

#	compiler
CC	= gcc
CFLAGS	= -Wall -Wextra -Werror -g

#	ft library
FT	= ./libft/
FT_LIB	=	$(addprefix $(FT), libft.a)
FT_INC	=	-I ./libft
FT_LNK  = 	-L	./libft -l ft

#	directories
SRCDIR	= ./src/
INCDIR	= ./includes/
OBJDIR	= ./obj/

all: obj $(FT_LIB)  $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	$(CC) $(CFLAGS) $(MLX_INC) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
	make -C $(FT)

$(NAME): $(OBJ)
	$(CC) $(OBJ)  $(FT_LNK) -lm -o $(NAME)

clean:
		rm -rf $(OBJDIR)
		make -C $(FT) clean
fclean:
		rm -rf $(NAME)
		make -C $(FT) fclean
re: fclean all
