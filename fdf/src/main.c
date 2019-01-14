#include "../includes/fdf.h"
int main(int argc, char **argv)
{
    /* VARIABLES */
    // File Descriptor
    int fd;
    // temporary string container
    char *line;
    printf("Welcome to FdF!\n");

    /* We are first going to read in a map file */
    if (argc != 2)
    {
        ft_putstr("Usage: FdF input file\n");
        return (1);
    }
    fd = open(argv[1], O_RDONLY);
    while (get_next_line(fd, &line))
    {
        ft_putstr(line);
        ft_putchar('\n');
    }
	void *mlx_ptr;
	void *win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "mlx 42");
	mlx_loop(mlx_ptr);
    return (0);
}
