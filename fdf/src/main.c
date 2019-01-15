#include "../includes/fdf.h"

void    draw_grid(void* mlx_ptr, void *win_ptr, int grid)
{
    grid++;
    for (int k = 1; k < 12; k++)
    {
        for (int i = 0; i < 300; i++)
        {
            mlx_pixel_put(mlx_ptr, win_ptr, i + 100 , 400 - (26 * k), 255);
            mlx_pixel_put(mlx_ptr, win_ptr, 400 - (26 * k) ,i + 100 , 255);
        }
    }
}
t_point getDimensions(int fd)
{
    t_point dim;
    char *line;
    int x;
    int i;
    int y;
    i = 0;
    y = 0;
    x = 0;
    while (get_next_line(fd, &line))
    {
        /* processes map into numeric map */
        ft_putstr(line);
        while(line[i])
        {
            //Check if digit is surrounded by ' 's such that it constitutes a value.
            if (ft_isdigit(line[i]) && line[i -1] == ' ' && line[i + 1] == ' ')
                x++;
            i++;
        }
        dim.x = x;
        ft_putchar('\n');
        y++;
    }
    dim.x += 2;
    dim.y = y;
      printf("\nDimensions X: %d Y: %d \n", dim.x, dim.y);
    return (dim);
}

int main(int argc, char **argv)
{
    /* VARIABLES */
    // File Descriptor
    int fd;
    // temporary string container
    printf("Welcome to FdF!\n");

    /* We are first going to read in a map file */
    if (argc != 2)
    {
        ft_putstr("Usage: FdF input file\n");
        return (1);
    }
    // Open file for initial dimension check.
    fd = open(argv[1], O_RDONLY);
    // Get dimensions
    t_point dim = getDimensions(fd);
    // print dimensions
      printf("\nDimensions X: %d Y: %d \n", dim.x, dim.y);
    /* testing inputs */
    void *mlx_ptr;
	void *win_ptr;
    int grid = 12;
    t_point one;
    one.x = 10;
    one.y = 10;
    one.z = 42;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "FdF");
    draw_grid(mlx_ptr, win_ptr, grid);
	mlx_loop(mlx_ptr);
    return (0);
}
