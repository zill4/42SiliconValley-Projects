#include "fillit.h"
#include <fcntl.h>

/*
    Prototype: int parseTetri(t_block *b, int y, char* str)
    Description: partseTetri, pareses a string for '.' && '#'.
                If the '#' are found, they are recorded in t_block.x
                && t_block.y position. A 0 is returned if the line is empty.
                A -1 is returned if the format is bad. A 1 is returned if success.
*/
int parseTetri(t_block *blocks, int *i, int *y, char* str)
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
            blocks->point[*i].x = x;
            blocks->point[*i].y = *y;
            *i += 1;
        }
        x++;
    }
    return (1);
}
/*
    prototype int   checkDim(t_block block)
    Description: checkDim, checks the dimensionality of a block.
                If a block is 1x4, 2x2, or 2x3 and the reverse of those.
                If a block is valid or not, i.e. no 4x2, 3x5, etc.
                Will also set the dimensions of a block. 
                returns 1 if good, 0 if bad.
*/
int     checkDim(t_block *block)
{
    int i;
    int x_min;
    int x_max;
    int y_min;
    int y_max;

    i = 0;
    x_min = block->point[0].x;
    y_min = block->point[0].y;
    x_max = block->point[0].x;
    y_max = block->point[0].y;
    while(i < 4)
    {
        if (block->point[i].x > x_max)
            x_max = block->point[i].x;
        if (block->point[i].x < x_min)
            x_min = block->point[i].x;
        if (block->point[i].y > y_max)
            y_max = block->point[i].y;
        if (block->point[i].y < y_min)
            y_min = block->point[i].y;
        i++;
        if (x_min < 0 || x_max > 3)
            return (0);
    }
        block->x_dim = (x_max - x_min) + 1;
        block->y_dim = (y_max - y_min) + 1;
    return(1);
}
void    printAll(t_point finalDim, int mapDim)
{
    int i;
    int k;

    k = 0;
    i = 0;
    while (i < mapDim)
    {
        while (k < mapDim)
        {
            if(finalDim.x > k && finalDim.y > i)
                ft_putchar('#');
            else
                ft_putchar('.');
            k++;
        }
        ft_putchar('\n');
        k = 0;
        i++;
    }
}
/*
    prototype void  printMap(int index)
    Description: printMap, takes the index of the counted blocks and
                creates the maximum map size for those blocks.
    SOON
        will places pieces onto map if space is free.
*/
void    printMap(int index, t_block *blocks)
{
    int i;
    int dimMap;
    t_point dimPrint;
    dimMap = 17;
    dimPrint.x = 0;
    dimPrint.y = 0;
    i = 0;
    while (i <= index)
    {
        /* This set of if statements finds space taken of tetris blocks */
        if (blocks[i].x_dim <= blocks[i].y_dim)
        {
            if (dimPrint.x > dimPrint.y)
                dimPrint.y += blocks[i].x_dim;
            else
            {
                dimPrint.x += blocks[i].x_dim;
                if (blocks[i].y_dim > dimPrint.y)
                    dimPrint.y = blocks[i].y_dim;
            }   
        }
        else
        {
            if (dimPrint.y > dimPrint.x)
                dimPrint.x += blocks[i].y_dim;
            else
            {
                dimPrint.y += blocks[i].y_dim;
                if (blocks[i].x_dim > dimPrint.x)
                    dimPrint.x = blocks[i].x_dim;
            }
        }
        i++;
    }
    if (dimPrint.x > dimPrint.y)
        dimMap = dimPrint.x;
    else
        dimMap = dimPrint.y;
    printf("The Dimensions of the map are, (X: %d, Y: %d)\n", dimPrint.x, dimPrint.y);
    printAll(dimPrint, dimMap);
}



int main()
{
    /* Variables */ 
    int fileDesc; 
    char *temp; //Container for the parsing of files.
    int y;
    int index;
    int i = 0;
    int ret;
    ret = 42;
    y = 0;
    index = 0;
    //t_point test_p;
    //t_block block;
    t_block blocks[26];
    /* Open file for testing */
   fileDesc = open("test",O_RDONLY);
    /* Check file if file is valid. */
    if (fileDesc <= 0) 
    {
            printf("The file provided is invalid\n");
            return (0);
    } 
    /*
    get_next_line(fileDesc, &temp);
    ret = parseTetri(&blocks[index], &i, &y, temp);
    printf("Return: %d Point Number: %d, X: %d, Y: %d\n", ret, i, blocks[index].point[i - 1].x,blocks[index].point[i - 1].y);
    y++;
    ret = parseTetri(&blocks[index], &i, &y, temp);
    printf("Return: %d Point Number: %d, X: %d, Y: %d\n", ret, i, blocks[index].point[i -1 ].x,blocks[index].point[i - 1].y);
    y++;
    */
    /* Print the file iteratively */
    
    while (get_next_line(fileDesc,&temp))
    {
        /* Check for every 4 == a block must increase index */
        if (ft_strlen(temp) >= 4)
        {
            if (y % 4 == 0 && y != 0)
            {
                i = 0;
                y = 0;
                index++;
            }
           // printf("Line: %s\n", temp);
            ret = parseTetri(&blocks[index], &i, &y, temp);
            if (ret <= 0)
                break;
            //if (i > 0)
             //   printf("Point Number: %d, X: %d, Y: %d\n", i, blocks[index].point[i -1].x,blocks[index].point[i -1].y);
            y++;
        }
    }
    index++;
    /*
        This Will print out the blocks with their values.
    */

    for (int k = 0; k < index; k++)
    {
        for(int j =0; j < index; j++)
        {
            printf("Block: %d, Point: %d, Value(x: %d, y: %d)\n",k,j,blocks[k].point[j].x, blocks[k].point[j].y);
        }
        printf("INDEX: %d", k);
                if (!checkDim(&blocks[k]))
                {
                    printf("Error Bad formatting! Shame on you!\n");
                    return (0);
                }
                else
                    printf("Block Dimensions, X: %d, Y: %d\n", blocks[k].x_dim, blocks[k].y_dim);
    }
    printMap(index, blocks);
    return (0);
}