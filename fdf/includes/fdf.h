#ifndef FDF_H
# define FDF_H
# include "../libft/libft.h"
# include "../miniLibX/mlx.h"
# include <fcntl.h>
# include <stdio.h>

typedef struct s_point
{
    int x; //The position on the horizontal axis.
    int y; //The position on the vertical axis.
    int z; //The value of the point axis.
}               t_point;

typedef struct s_map
{
    int **map;
    t_point *dimensions; //the overall dimensions of the map.
}               t_map;

typedef struct s_strmap
{
    char **line;
    int row;
    int col;
    struct s_strmap *next;
}               t_strmap;
#endif
