#include "fillit.h"
#include <fcntl.h>

/*
    Prototype: int parseTetri(t_block *b, int y, char* str)
    Description: partseTetri, pareses a string for '.' && '#'.
                If the '#' are found, they are recorded in t_block.x
                && t_block.y position. A 0 is returned if the line is empty.
                A -1 is returned if the format is bad. A 1 is returned if success.
*/
int parseTetri(t_block *blocks, int i, int y, char* str)
{
    int x;

    x = 0;
    if (str == NULL)
        return (-1);
    if (!(ft_strlen(str) % 4 == 0))
        return (0);
    while (str[x])
    {
        /* Check if '#' point is reached,
            Record x position 0 - 3
            Record y position from outside func.
            i iterates to next block if multiple '#' points are found.
        */
        if (str[x] == '#')
        {
            blocks->point[i].x = x;
            blocks->point[i].y = y;
            i++;
        }
        x++;
    }
    return (1);
}

int main()
{
    /* Variables */ 
    int fileDesc; 
    char *temp; //Container for the parsing of files.
    //t_point test_p;
    //t_block block;
    t_block blocks[4];
    /* Open file for testing */
   fileDesc = open("test",O_RDONLY);
    /* Check file if file is valid. */
    if (fileDesc <= 0) 
    {
            printf("The file provided is invalid\n");
            return (0);
    } 
    /* Print the file iteratively */
    while (get_next_line(fileDesc,&temp))
    {
        printf("Line: %s\n", temp);    
    }
    return (0);
}