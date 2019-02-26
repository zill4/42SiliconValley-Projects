#ifndef FDF_H
# define FDF_H
# include "../libft/libft.h"
# include "../miniLibX/mlx.h"
# include <fcntl.h>
# include <stdio.h>

typedef struct s_point
{
    int x;          //The position on the horizontal axis.
    int y;          //The position on the vertical axis.
    int z;          //The value of the point axis.
    char *color;    //The color value passed in by the map.
                    // Color :: 0xFFFFFF
}               t_point;

typedef struct s_map
{
    t_point **map;
    int dim_x;
    int dim_y;
}               t_map;

typedef struct s_strmap
{
    char **line;
    int row;
    int col;
    struct s_strmap *next;
}               t_strmap;
#endif
