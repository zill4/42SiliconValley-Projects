
#include "fillit.h"
#include <fcntl.h>

void    initPoint(t_point *p)
{
    p->x = 0;
    p->y = 0;
}

int     checkFormat(t_block block)
{
    int d;
    int i;
    
    i = 0;
    d = 0;
    while (i < 3)
    {
        d = block.point[i + 1].y - block.point[i].y;
        if (d > 1 || d < -1)
            return (0);
        d = block.point[i + 1].x - block.point[i].x;
        if (d > 1 || d < -1)
            return (0);
        i++;
    }
    return (1);
}

int     addBlockLine(t_block *block, char *line, int *count, int y)
{
    int i;

    i = 0;
    printf("checking length of line: %zu\n", ft_strlen(line));
    printf("String: %s\n", line);
    while(line[i])
    {
        if (line[i] == '#')
        {
            block->point[*count].x = i;
            block->point[*count].y = y;
            *count += 1;
        }
        else if (line[i] != '.' && line[i] != '#')
            return (-1);
        i++;
    }
    if (i != 4)
        return (-1);
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
/* IM PRETTY SURE THIS IS NOT NECESSARY */
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
    return(1);
}


/*   
    prototype void    printMapPls(map, sizeofmap)
    Description:    Will print the map for the given size.
*/
void    printMapPls(char map[17][17], int mapSize)
{
    int k = 0;
    for(int i = 0; i < mapSize; i++)
    {
        for (k = 0; k < mapSize; k++)
        {
            ft_putchar(map[i][k]);
        }
        ft_putchar('\n');
       k = 0;
    }
	printf("---------\n");
}

/*
    prototype void  initMap(char **map, int dim)
        initMap takes a pointer to a map, initializes the map to a series of '.''s
*/
void  initMap(char map[17][17], int dim)
{
    printf("Map size: %d\n", dim);
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
    protoype  int   placePoint(char **map, t_block *blocks, t_point mapPoints, int index)
            Description:  Tries to recursively place a point based on the mapPoints location in the map.
                        Points are placed till the either the block is finished or a spot is not available.
                        If a spot is not free the function is called again with a change in first the x position, then the y position.
                        Should not happen but if a spot just cannot befound a critical error is thrown.
*/
int         checkMap(char map[17][17], t_block block, int mapSize, int l, t_point *lastPlace, int v)
{
    int k = 0;
    int ox = block.ox;
    int oy = block.oy;
    int x;
    x = 0;
    int y; 
    y = 0;
    int i = 0;
    char *lett = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    //I subbed one and added one places this could be fixed.
    mapSize -= 1;
    //checks if map is too small returns -1
    if (block.point[0].y > mapSize || \
    block.point[0].x > mapSize || \
    block.point[1].y > mapSize || \
    block.point[1].x > mapSize || \
	block.point[2].y > mapSize || \
    block.point[2].x > mapSize || \
    block.point[3].y > mapSize || \
    block.point[3].x > mapSize)
		return (-1);
    
    while (y < mapSize + 1)
    {
        while (x < mapSize + 1)
        {  
            /* MUCH LIKE THE UNDO THIS IS THE PLACEMENT */
            //bascially iterates through map addes x + offset + inherent value of block checks if map is free and places 
            //does this for all four points, if all four are free it places it at once else keeps going and returns 0 if nothing could be placed.
            if ((map[y + block.point[0].y + oy][x + block.point[0].x + ox] == '.')&& \
                (map[y + block.point[1].y + oy][x + block.point[1].x + ox] == '.')&& \
			    (map[y + block.point[2].y + oy][x + block.point[2].x + ox] == '.')&& \
                (map[y + block.point[3].y + oy][x + block.point[3].x + ox] == '.')&& 
                y + block.point[0].y + oy <= mapSize && y + block.point[1].y + oy <= mapSize \
                && y + block.point[2].y + oy <= mapSize && y + block.point[3].y + oy <= mapSize \
                && x + block.point[0].x + ox <= mapSize && x + block.point[1].x + ox <= mapSize \
                && x + block.point[2].x + ox <= mapSize && x + block.point[3].x + ox <= mapSize)
            {
                lastPlace->x = x + block.point[0].x + ox;
                lastPlace->y = y + block.point[0].y + oy;
                if (!v){
                map[y + block.point[3].y + oy][x + block.point[3].x + ox] = lett[l];
                map[y + block.point[2].y + oy][x + block.point[2].x + ox] = lett[l];
                map[y + block.point[1].y + oy][x + block.point[1].x + ox] = lett[l];
                map[y + block.point[0].y + oy][x + block.point[0].x + ox] = lett[l];
                }

                l++;

                k = 0;
                while ( i <= mapSize)
                {
                    while (k <= mapSize)
                    {
                        ft_putchar(map[i][k]);
                        k++;
                    }
                    ft_putchar('\n');
                    k = 0;
                    i++;
                }   
				printf("------------------------\n");
                return (1);
            }
           x++;
        }
        x = 0;
        y++;
    }
	
     if (block.point[3].y >= y || block.point[3].x >= y)
         return (-1);
    return (0);
}


int         checker(char map[17][17], t_block block, int mapSize, t_point *lastPlace, int i)
{

    int x;
    x = 0;
    int y; 
    y = 0;
    char *lett = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    mapSize -= 1;
    printf("we are currently checking fabulous block #: %d, of letter: %c\n", i, lett[i]);
    while (y < mapSize + 1)
    {
        while (x < mapSize + 1)
        {  
           //checks if all points are free to be placed and actaully does the undoing.     
            if ((map[y + block.point[0].y][x + block.point[0].x] == lett[i])&& \
                (map[y + block.point[1].y][x + block.point[1].x] == lett[i])&& \
			    (map[y + block.point[2].y][x + block.point[2].x] == lett[i])&& \
                (map[y + block.point[3].y][x + block.point[3].x] == lett[i])&& 
                y + block.point[0].y <= mapSize && y + block.point[1].y <= mapSize \
                && y + block.point[2].y <= mapSize && y + block.point[3].y <= mapSize \
                && x + block.point[0].x <= mapSize && x + block.point[1].x <= mapSize \
                && x + block.point[2].x <= mapSize && x + block.point[3].x <= mapSize)
            {
                lastPlace->x = x + block.point[0].x;
                lastPlace->y = y + block.point[0].y;
/* THIS IS THE UNDOING METHOD LOL */
                map[y + block.point[0].y][x + block.point[0].x] = '.';
                map[y + block.point[1].y][x + block.point[1].x] = '.';
			    map[y + block.point[2].y][x + block.point[2].x] = '.';
                map[y + block.point[3].y][x + block.point[3].x] = '.';
                return (1);
            }
           x++;
        }
        x = 0;
        y++;
    }
    return (0);
}
/*
    prototype void redo(t_block block, int x, int y)
    Description: increases the x or y value of a block given an undo transformation.
*/
void     redo(t_block *block, int x, int y)
{  
    if( x > y)
        block->ox += 1; //each block has a ox and oy value for offseting.
    else
    {
        block->ox = 0;
        block->oy += 1;
    }
}   

void    undoOffset(t_block blocks[26], int index)
{
    int i;

    i = 0;
    while (i < index)
    {
        blocks[i].ox = 0;
        blocks[i].oy = 0;
        i++;
    }
}

int     undo(t_block *block, char map[17][17], int x, int y, int mapMax)
{

            x = (x - block->point[0].x) + block->point[3].x; //This is the farthest right position 
            y = (y - block->point[0].y) + block->point[3].y;//basically checks if the block can be undone, 
            //because it will either move to the right or down, if the map is too small
            //or if theere is another block in the way it should not undo.
            printMapPls(map,mapMax); //this prints the map.
            if (x < mapMax - 1 && map[y][x + 1] == '.')
                redo(block, 1, 0); //redo is the new method of shifting a block right or down
            else if (y < mapMax - 1 && map[y + 1][x] == '.')
                redo(block, 0, 1);   
            else
                return (0);
        
            return (1);
}
/*
    prototype void  tetriMap(char **map, t_block *blocks, int mapMax)
    Description: for the dimensions of the map, each block is paced in the left upper
        most position. If a position is unavailable then it is tansformed in the x direction 
        checks spacing and repeats until it can be placed.
*/
void    tetriMap(char map[17][17], t_block *blocks, int index, int mapMax, int i, t_point lastPlace)
{    
	int ret = 0; 
    int v = 0;
    int x = lastPlace.x;
    int y = lastPlace.y;

    /* Iterate through the blocks until we reach the last block */
    while ( i != index) 
    {
        /* v basically allows us to check the last place of a map without placing */
        v = 0;
        if ((ret = (checkMap(map, blocks[i], mapMax, i, &lastPlace, v))) > 0)
            i++;
		else if (ret == -1)
            mapMax++; //checkMap will return -1 if the block its trying to place is to big for the map.
        else //This else triggers if we could not place the point easily in checkMap
        {
            i--;
            v = 1;
            checker(map, blocks[i], mapMax, &lastPlace, i);
            x = lastPlace.x; //undo removes points based on lastplace.
            y = lastPlace.y;
            while (!undo(&blocks[i], map, x, y, mapMax))
            {
                v = 1;
                i--;
                if (i < 0) 
                {
                    mapMax++;
                    undoOffset(blocks, index);
                    i = 0;
                    break;
                }
                if (checker(map, blocks[i], mapMax, &lastPlace, i)) {
                x = lastPlace.x;
                y = lastPlace.y;
                }
                
            }
            //printMapPls(map,mapMax); //this prints the map.
        }
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
    int i; //this iterates through the while loop of the index
    int dimMap; //saves maximum dimension of map.
    char map[17][17]; //This is the map we will be printint out. living on the stack.
	t_point lastpoint; //saves the last point we placed something.
	lastpoint.x = 0; //init last point, you have to init these a function would be useful.
	lastpoint.y = 0; //init last point
    t_point dimPrint; //another point saving the dimensions to print, but is a bit redudant based on how we solve the map now.
    dimMap = 2; //initial dim of map should always be 2.
    dimPrint.x = 0; //init dimprint
    dimPrint.y = 0; //init dimprint
    i = 0; //init i

    /* This marks the end of the uncessary thing above */

    i = 0;
    printf("Index: %d", index);

    initMap(map, 17); //init the map, with a bunch of '.'s 
        tetriMap(map,blocks, index, 2, i, lastpoint); //This is the thing we have been working for the past couple weeks.

}

int     readTetri(int fileDesc, t_block blocks[26])
{
    char    *line;
    int     index;
    int     count;
    int     spaces;
    int     y;

    y = 0;
    index = 0;
    count = 0;
    spaces = 0;
    while (get_next_line(fileDesc,&line))
    {
        if(line == NULL && spaces % 5 != 0)
            return (-1);
        if(addBlockLine(&blocks[index], line, &count, y) > 0)
        {
            y++;
            if (y % 4 == 0)
            {   
                if (count > 4)
                    return (0);
                count = 0;
                y = 0;
               // if (checkFormat(blocks[index]) <= 0)
                 //   return (0);
                index++;
            }
        }
        spaces++;
    }
    return (index);
}

int main(int argc, char** argv)
{
    /* Variables */ 
    int fileDesc; 
    int y;
    int index;
    t_block blocks[26];

    fileDesc = 0;
    y = 0;
    index = 0;

    if (argc != 2)
    {
        ft_putstr("Usage: fillit input file\n");
        return (1);
    }
    if((index = readTetri(open(argv[1], O_RDONLY), blocks)) == 0 )
    {
        ft_putstr("error\n");
        return (1);
    }

    for (int k = 0; k < index; k++)
    {
        if (!checkDim(&blocks[k]))
        {
            printf("Error Bad formatting! Shame on you!\n");
            return (0);
        }
    }
    close(fileDesc);
    printMap(index, blocks);
    return (0);
}