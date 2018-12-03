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
    int k;
    int x_min;
    int x_max;
    int y_min;
    int y_max;

    i = 0;
    k = 0;
    x_min = block->point[0].x;
    y_min = block->point[0].y;
    x_max = block->point[0].x;
    y_max = block->point[0].y;
    while (i < 4)
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
    printf("XMax Dimemsion: %d XMIN Dimension: %d, YMax Dimension: %d, YMin Dimension: %d\n", x_max, x_min, y_max, y_min);
    /* normalize the points such that at least 1 is min 0, for simpler placing */
    if (x_min > 0)
    {
        i = 0;
        while (i < 4)
            block->point[i++].x -= x_min;
    }
    if (y_min > 0)
    {
        i = 0;
        while (i < 4)
            block->point[i++].y -= y_min;
    }
        block->x_dim = (x_max - x_min) + 1;
        block->y_dim = (y_max - y_min) + 1;
    printf("XMax Dimemsion: %d XMIN Dimension: %d, YMax Dimension: %d, YMin Dimension: %d\n", x_max, x_min, y_max, y_min);
    return(1);
}

/*
    prototype void printAll(t_point finalDim, int mapDim)
    Description: printAll takes the maximum dimension of the map.,
                and the worst case scenario 
*/
void    printAll(char map[17][17], int mapDim)
{
    t_point dim;
    int x;
    int y;
    x = 0;
    y = 0;
    dim.x = 0;
    dim.y = 0;
    while ( y < mapDim)
    {
        while (x < mapDim)
        {
            if (map[y][x] == '#' && (y >= dim.y))
                dim.y = y;
            if (map[y][x] == '#' && (x >= dim.x))
                dim.x = x;
            
            x++;
        }
        x = 0;
        y++;
    }
    x = 0;
    y = 0;
    if ( dim.x >= dim.y )
        dim.y = dim.x;
    else
        dim.x = dim.y;
    while (y < dim.y + 1)
    {
        while (x < dim.x + 1)
        {
            ft_putchar(map[y][x]);
            x++;
        }
        ft_putchar('\n');
        x = 0;
        y++;
    }
}
/*
    protoype  int   placePoint(char **map, t_block *blocks, t_point mapPoints, int index)
            Description:  Tries to recursively place a point based on the mapPoints location in the map.
                        Points are placed till the either the block is finished or a spot is not available.
                        If a spot is not free the function is called again with a change in first the x position, then the y position.
                        Should not happen but if a spot just cannot befound a critical error is thrown.
*/


int         checkMap(char map[17][17], t_block block, int mapSize)
{

    int k = 0;
    int x;
    x = 0;
    int y; 
    y = 0;
    int i = 0;
   


    while (y < mapSize)
    {
        while (x < mapSize)
        {
           // printf("Trying to plax at Y: %d + BY: %d  X: %d + BX: %d \n", y, block.point[0].y, x, block.point[0].x);
           // printf("The value is: %c\n", map[y + block.point[0].y][x + block.point[0].x]);
           // printf("Trying to plax at Y: %d + BY: %d  X: %d + BX: %d \n", y, block.point[1].y, x, block.point[1].x);
           // printf("The value is: %c\n", map[y + block.point[1].y][x + block.point[1].x]);
            //printf("Trying to plax at Y: %d + BY: %d  X: %d + BX: %d \n", y, block.point[2].y, x, block.point[2].x);
           // printf("The value is: %c\n", map[y + block.point[2].y][x + block.point[2].x]);
           // printf("Trying to plax at Y: %d + BY: %d  X: %d + BX: %d \n", y, block.point[3].y, x, block.point[3].x);
           // printf("The value is: %c\n", map[y + block.point[3].y][x + block.point[3].x]);
            if ((map[y + block.point[0].y][x + block.point[0].x] == '.') && (map[y + block.point[1].y][x + block.point[1].x] == '.') && (map[y + block.point[2].y][x + block.point[2].x] == '.') && (map[y + block.point[3].y][x + block.point[3].x] == '.'))
            {
                printf("Placing #\n");
                map[y + block.point[3].y][x + block.point[3].x] = '#';
                map[y + block.point[2].y][x + block.point[2].x] = '#';
                map[y + block.point[1].y][x + block.point[1].x] = '#';
                map[y + block.point[0].y][x + block.point[0].x] = '#';
                k = 0;
                while ( i < mapSize)
                {
                    while (k < mapSize)
                    {
                        ft_putchar(map[i][k]);
                        k++;
                    }
                    ft_putchar('\n');
                    k = 0;
                    i++;
                }   
                return (1);
            }
           x++;
        }
        x = 0;
        y++;
    }

     i = 0;
     k = 0;
    while ( i < mapSize)
    {
        while (k < mapSize)
        {
            ft_putchar(map[i][k]);
            k++;
        }
        ft_putchar('\n');
        k = 0;
        i++;
    }
    return (1);
}


int         placeMap(char map[17][17], t_block block, int mapSize, t_point *offset)
{
    int i;
    int k = 0;
    int x = offset->x;
    int y = offset->y;
    int px;
    int py;
    px = 0;
    py = 0;
    i = 0;
    printf("%d Map\n",mapSize);
    while (i < 4)
    {
        px = block.point[i].x;
        py = block.point[i].y;
        printf("PLACE Block X: %d Y: %d\n", px, py);
        printf("PLACE Map offset X: %d Y: %d\n",x, y);
        printf("PLACE Map Value: %c\n",map[py + y][px + x]);
        if (map[y + py][x + px] == '.')
        {
            map[y + py][x + px] = '#';
            i++;
        }
        else
        {
            printf("PLACE ERROR\n");
            return (0);
        }
    }
    i = 0;
    while ( i < mapSize)
    {
        while (k < mapSize)
        {
            ft_putchar(map[i][k]);
            k++;
        }
        ft_putchar('\n');
        k = 0;
        i++;
    }
    return (1);
}
/*
    prototype void  tetriMap(char **map, t_block *blocks, int mapMax)
    Description: for the dimensions of the map, each block is paced in the left upper
        most position. If a position is unavailable then it is tansformed in the x direction 
        checks spacing and repeats until it can be placed.
*/

void    tetriMap(char map[17][17], t_block *blocks, int index, int mapMax)
{
    
    int i;
    int j;
    t_point dim;
    t_point offset;

    offset.x = 0;
    offset.y = 0;
    dim.x = 0;
    dim.y = 0;
    j = 0; //point iterator
    i = 0; //block iterator

    while (i < index)
    {
        if (checkMap(map, blocks[i], mapMax))
        {

            printf("Map is good with an offset of X: %d, Y: %d\n", offset.x, offset.y);
            //placeMap(map, blocks[i], mapMax, &offset);
        }
        i++;
    }
    
}

/*
    prototype void  initMap(char **map, int dim)
        initMap takes a pointer to a map, initializes the map to a series of '.''s
*/

void  initMap(char map[17][17], int dim)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while(y < dim)
    {
        while(x < dim)
        {
            map[y][x] = '.';
            ft_putchar(map[y][x]);
            x++;
        }
        ft_putchar('\n');
        map[y][x] = '\0';
        x = 0;
        y++;
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
    char map[17][17];

    t_point dimPrint;
    dimMap = 17;
    dimPrint.x = 0;
    dimPrint.y = 0;
    i = 0;
    while (i < index  - 1)
    {
        /* This set of if statements finds space taken of tetris blocks */
       // if (blocks[i].x_dim <= blocks[i].y_dim)
        if (dimPrint.x <= dimPrint.y)
        {
            dimPrint.x += blocks[i].x_dim;
            if (blocks[i].y_dim > dimPrint.y || dimPrint.y== 0)
                dimPrint.y = blocks[i].y_dim;
            printf("The Dimensions of the map are, (X: %d, Y: %d)\n", dimPrint.x, dimPrint.y);
        }
        else
        {
            dimPrint.y += blocks[i].y_dim;
            if (blocks[i].x_dim > dimPrint.x || dimPrint.x == 0)
                dimPrint.x = blocks[i].x_dim;
            printf("The Dimensions of the map are, (X: %d, Y: %d)\n", dimPrint.x, dimPrint.y);
        }
        i++;
    }
    if (dimPrint.x > dimPrint.y)
        dimMap = dimPrint.x;
    else
        dimMap = dimPrint.y;
    /* After the max dimensions have been found, we can place init and place on map */
    
    /* Initialize a map for places tetri */
    initMap(map, dimMap);
    tetriMap(map,blocks, index, dimMap);
    //(map, blocks, index, dimMap)
    /* places tetri on map */
    printf("The Dimensions of the map are, (X: %d, Y: %d)\n", dimPrint.x, dimPrint.y);
    printAll(map, dimMap);
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
    
    t_block blocks[26];
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
        /* Check for every 4 == a block must increase index */
        if (ft_strlen(temp) >= 4)
        {
            if (y % 4 == 0 && y != 0)
            {
                i = 0;
                y = 0;
                index++;
            }
            ret = parseTetri(&blocks[index], &i, &y, temp);
            if (ret <= 0)
                break;
            y++;
        }
    }
    index++;
    /*
        This Will print out the blocks with their values.
    */

    for (int k = 0; k < index; k++)
    {
        for(int j =0; j < 4; j++)
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