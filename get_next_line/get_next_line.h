
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "./libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# define BUFF_SIZE 5

int     get_next_line(const int fd, char **line);
int		ft_stralloc(char **str, char** line, int fd, int val);
#endif
