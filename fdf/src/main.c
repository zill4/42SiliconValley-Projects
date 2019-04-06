#include "../includes/fdf.h"

/*
int     ft_strarr_count(char **str)
PARAMS:
    char **str ::List of strings to check the dimensions of.
Desciption:
    Checks for the size of the array of strings.
Returns:
    Size of array as an integer.
*/
int     ft_strarr_count(char **str)
{
    int i;

    i = 0;
    while(str[i])
    {
        i++;
    }
    return (i);
}
/*
int     ft_strcontains(char *str, char c)
PARAMS:
    char* str :: The string to check.
    char c  :: The character we are looking for.
Description:
    If the character we are looking for is there.
Returns:
    1 if the character is present.
    0 if the character is not.
    -1 if the string is bad.
*/

int     ft_strcontains(char *str, char c)
{
    int i;

    i = 0;
    if (!str)
        return (-1);
    while(str[i])
    {
        if (str[i] == c)
            return (1);
        i++;
    }
    return (0);
}
/*
int     ft_strisnum(char *str)
PARAMS:
    char* str :: The string to check
Description:
    Check whether the entire string is numeric.
Returns:
    1 if the string is all numbers 
    0 if not
    -1 if a bad string
*/
int     ft_strisnum(char *str)
{
    int i;

    i = 0;
    if (!str)
        return (-1);
    while(str[i])
    {
        if (ft_isdigit(str[i]))
            i++;
        else
            return (0);
    }
    return (1);
}
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
    void loadMap(int fileDescriptor, t_strmap *top_of_map)
    Params: 
        int fd :: The file descriptor for opening the file needed to be read.
        t_strmap *head :: The top of the list of lines that neeed to be parsed for color and depth.
    Description:
        Read through the entire file, save all points into a strmap.


*/
t_point     loadMap(int fd, t_strmap *head)
{
    // Variables
    char *line;
    char **strings;
    int i;
    int x;
    t_point dimensions;

    i = 0;
    // Iterate through file collecting all numbers. 
    while (get_next_line(fd, &line))
    {
        ft_putstr(line);
        // Allocate
        strings = malloc(sizeof(char)*ft_strlen(line)/2);
        strings = ft_strsplit(line, ' ');
        x = ft_strarr_count(strings);
        //We can assume that the size of each string array is arond half the line len.
        // This should append a new map to the head.
        if (i > 0)
            append_strmap(head, new_strmap(i, ft_strlen(line), strings));
        else
            head = new_strmap(i, ft_strlen(line), strings);
        i++;
        ft_putchar('\n');
    }
    dimensions.x = x;
    dimensions.y = i;
    return (dimensions);
}
/*
    t_point parseColor(char* str, int col, int row)
    Params:
        char* str :: The string that needs to be parsed for color
        int col :: The column to be read as the y axis.
        int row :: The row to be read as the x asxis.
    Description:
        Parse color and dimension, return point with required fields.
*/
// t_point     parseColor(char *str, int col, int row)
// {
//     t_point new;
//     // Have to split string with 8,0xFFFFFF format.
//     int i;
//     char *num_str;
//     int z;

//     num_str = malloc(ft_strlen(str));
//     i = 0;
//     if (!str)
//         return(new);

//     while (str[i])
//     {
//         if (ft_isdigit(str[i]))
//             num_str[i] = str[i];
//         if (str[i] == ',')
//         {
//             num_str[i] = '\0';
//             z = ft_atoi(num_str);
//             new.color = str + i + 1;
//             break;
//         }
//         i++;
//     }   
// }
// /*
//     t_map parseMap(t_strmap *head)
//     params:
//         t_strmap *head :: The top of the list of blocks containing each string for
//                           the map to read.
//     Description:
//         Parse strmap linked list of strings containing column & row information for a given map.
//         Given a map with a color id -> 8,0xFFFFF save color within a point.
//         Given a map with non equal dimensions return a bad map.
// */
// t_map   parseMap(t_strmap *head)
// {
  
//     int i;

//     i = 0;
//     while(head->next)
//     {
//         while(i < head->row)
//         {
//             if (ft_strcontains(head->line[i], ','))
//             {
//                 //Parse for color
//                 parseColor(head->line[i],head->col, i);
//             }
//             else if (ft_strisnum(head->line[i]))
//             {
//                 //Create new_point and append to map.

//             }
//             i++;
//         }
//     }
//     return (map);
// }


int main(int argc, char **argv)
{
        // File Descriptor
    int fd;
    //t_map map;
        // Container for map depths.
    t_point test;
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
    test = loadMap(fd, head);
    printf("Dimensions X:%d Y:%d\n", test.x, test.y);
        // The file can now be closed.
    close(fd);
    //map = parseMap(head);

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
