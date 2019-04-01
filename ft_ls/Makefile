NAME = ft_ls

#	src / obj files
SRC	=  main.c a_read_dir.c b_sorting.c  c_list.c  ./d_printing.c  pos_flags.c \
		subfiles.c 
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

all: obj $(FT_LIB) $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	$(CC) $(CFLAGS) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
	make -C $(FT)


$(NAME): $(OBJ)
	$(CC) $(OBJ) $(FT_LNK) -lm -o $(NAME)

clean:
		rm -rf $(OBJDIR)
		make -C $(FT) clean
fclean:
		rm -rf $(NAME)
		make -C $(FT) fclean
re: fclean all
