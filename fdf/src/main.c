#include "../includes/fdf.h"


/*
    void append_strmap(t_strmap *head, t_strmap *new)
    PARAMS:
        t_strmap *head :: The beginning of the list.
        t_strmap *new :: The new block to be appended to the list. 
    Description:
        append_strmap appends a new block to the end of the current list
        pointing to the head.
*/
void append_strmap(t_strmap *head, t_strmap *new)
{
    t_strmap *rover;
    rover = head;
    while(rover->next)
        rover = rover->next;
    rover->next = new;
}
/*
    t_strmap *new_strmap(int row, char** strings)
    PARAMS:
        int row :: The index of which row this given block is on.
        int col :: Essentially the length of the given array of strings.
        char **strings :: The array of strings to be saved within this block.
    Description:
        new_strmap creates a new strmap block, and returns the address of it.
*/
t_strmap *new_strmap(int row, int col, char** strings)
{
    t_strmap *new;
    int i;

    if (!strings)
        return (NULL);
    i = 0;
    if ((new = malloc(sizeof(t_strmap))))
    {
        new->row = row;
        new->col = col;
        new->line = strings;
        new->next = NULL;
    }
    return (new);
}

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

/*
    t_point loadMap(int fileDescriptor, t_strmap *top_of_map)
    Params: 
        int fd :: The file descriptor for opening the file needed to be read.
        t_strmap *head :: The top of the list of lines that neeed to be parsed for color and depth.
    Description:
        Read through the entire file, save all points into a strmap.


*/
void loadMap(int fd, t_strmap *head)
{
    // Variables
    char *line;
    char **strings;
    int i;

    i = 0;
    // Iterate through file collecting all numbers. 
    while (get_next_line(fd, &line))
    {
        ft_putstr(line);
        // Allocate
        strings = malloc(sizeof(char)*ft_strlen(line)/2);
        strings = ft_strsplit(line, ' ');
        //We can assume that the size of each string array is arond half the line len.
        // This should append a new map to the head.
        if (i > 0)
            append_strmap(head, new_strmap(i, ft_strlen(line), strings));
        else
            head = new_strmap(i, ft_strlen(line), strings);
        i++;
        ft_putchar('\n');
    }
}



int main(int argc, char **argv)
{
        // File Descriptor
    int fd;
        // Container for map depths.
    t_strmap *head;
    head = NULL;
    printf("Welcome to FdF!\n");
        // First going to read in a map file 
    if (argc != 2)
    {
        ft_putstr("Usage: FdF input file\n");
        return (1);
    }
        // Open file for initial dimension check.
    fd = open(argv[1], O_RDONLY);
        // Loading Map :: loadMap(File Descriptor, String Map container)
    loadMap(fd, head);
        // The file can now be closed.
    close(fd);
    //parseMap(head);

//----------------------------------------------------------------------------------- 
    // /* testing inputs */
    // void *mlx_ptr;
	// void *win_ptr;
    // int grid = 12;
    // t_point one;
    // one.x = 10;
    // one.y = 10;
    // one.z = 42;
	// mlx_ptr = mlx_init();
	// win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "FdF");
    // draw_grid(mlx_ptr, win_ptr, grid);
	// mlx_loop(mlx_ptr);
    return (0);
}
