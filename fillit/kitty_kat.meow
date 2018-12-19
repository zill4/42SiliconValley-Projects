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

void    minDim(t_point *min, t_block *block)
{ 
    int i;

    i = 0;
    if (min->x > 0)
    {
        i = 0;
        while (i < 4)
            block->point[i++].x -= min->x;
    }
    if (min->y > 0)
    {
        i = 0;
        while (i < 4)
            block->point[i++].y -= min->y;
    }
}

void    setMinMax(t_point *min, t_point *max, t_block *block)
{
    min->x = block->point[0].x;
    min->y = block->point[0].y;
    max->x = block->point[0].x;
    max->y = block->point[0].y;
}

int   minMaxxer(t_point *min, t_point *max, t_block *block)
{
    int i;

    i = 0;
    while (i < 4)
    {
        if (block->point[i].x > max->x)
            max->x = block->point[i].x;
        if (block->point[i].x < min->x)
            min->x = block->point[i].x;
        if (block->point[i].y > max->y)
            max->y = block->point[i].y;
        if (block->point[i].y < min->y)
            min->y = block->point[i].y;
        i++;
        if (min->x < 0 || max->x > 3)
            return (0);
    }
    return (1);
}

int     checkDim(t_block *block)
{
    t_point min;
    t_point max;

    initPoint(&min);
    initPoint(&max);
    setMinMax(&min, &max, block);
    if (minMaxxer(&min, &max, block) == 0)
        return (0);
    minDim(&min, block);
    block->x_dim = (max.x - min.x) + 1;
    block->y_dim = (max.y - min.y) + 1;
    return(1);
}


void    printMapPls(char map[17][17], int mapSize)
{
    int k;
    int i;

    i = 0;
    k = 0;
    while (i < mapSize)
    {
        while (k < mapSize)
            ft_putchar(map[i][k++]);
        ft_putchar('\n');
        k = 0;
        i++;
    }
}

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
            x++;
        }
        map[y][x] = '\0';
        x = 0;
        y++;
    }
}
void    setLastPlace(t_block block, t_point *lastPlace, int x, int y)
{
    lastPlace->x = x + block.point[0].x + block.ox;
    lastPlace->y = y + block.point[0].y + block.oy;
}

void    placePoints(char map[17][17], t_block b, int x, int y, int l)
{
    int i;
    
    i = -1;
     while (++i < 4)
                   map[y + b.point[i].y + b.oy][x + b.point[i].x + b.ox] = 'A' + l;
}

void    undoPoint(char map[17][17], t_block b, int x, int y)
{
     int i;

    i = -1;
     while (++i < 4)
        map[y + b.point[i].y][x + b.point[i].x] = '.';
}
int     checkMap(char map[17][17], t_block b, int mapSize, int l, t_point *lastPlace)
{
    int x;
    int y;
    int i;

    x = -1;
    y = -1;
    while (++y < mapSize)
    {
        while (++x < mapSize)
        {
            i = 0;
            while ((map[y + b.point[i].y + b.oy][x + b.point[i].x + b.ox] == '.')&&
                    y + b.point[i].y + b.oy < mapSize && x + b.point[i].x + b.ox < mapSize && i++ < 4)
            if (i == 4)
            {
                setLastPlace(b, lastPlace, x, y);
                placePoints(map, b, x, y, l);
                printMapPls(map,mapSize);
                printf("---------\n");
                return (1);
            }
        }
        x = -1;
    }
    return (0);
}

int     checker(char map[17][17], t_block b, int mapSize, t_point *lastPlace, int l)
{
    int x;
    int y;
    int i;

    x = -1;
    y = -1;
    while (++y < mapSize)
    {
        while (++x < mapSize)
        {
            i = 0;
            while ((map[y + b.point[i].y][x + b.point[i].x] == 'A' + l)&&
                    y + b.point[i].y < mapSize && x + b.point[i].x < mapSize && i++ < 4)
            if (i == 4)
            {
                setLastPlace(b, lastPlace, x, y);
                undoPoint(map, b, x, y);
                return (1);
            }
        }
        x = -1;
    }
    return (0);
}

void     redo(t_block *block, int x, int y)
{  
    if (x == 0)
        block->ox = 0;
    if (y == 1)
        block->oy += 1;
    if (x == 1)
        block->ox += 1;
}  

void    undoOffset(t_block *block)
{
        block->ox = 0;
        block->oy = 0;
}

int     undo(t_block *block, char map[17][17], int x, int y, int mapMax)
{
            x = (x - block->point[0].x) + block->point[3].x;
            y = (y - block->point[0].y) + block->point[3].y;
            if (x < mapMax - 1 && map[y][x + 1] == '.')
                redo(block, 1, 0);
            else if (y < mapMax && map[y + 1][x] == '.')
                redo(block, 0, 1);   
            else
                return (0);
            
            return (1);
}

void redux(int *i, int *mapMax, t_block *blocks, int index)
{
    *mapMax += 1;
    undoOffset(&blocks[*i]);
    *i = 0;
}

int    tetriMap(char map[17][17], t_block *blocks, int index, int mapMax, t_point lp)
{
    int i;
    
    i = 0;
    while (i != index) 
    {
        if (checkMap(map, blocks[i], mapMax, i, &lp) > 0)
            i++;
        else
        {
            i--;
            checker(map, blocks[i], mapMax, &lp, i);
            while (!undo(&blocks[i], map, lp.x, lp.y, mapMax))
            {
                if (i < 0) 
                {
                    redux(&i, &mapMax, blocks, index);
                    break;
                }
                checker(map, blocks[i], mapMax, &lp, i);
                i--;
            }
        }

    }
    return(mapMax);
}

void    printMap(int index, t_block *blocks)
{

    int dimMap;
    char map[17][17];
	t_point lastpoint;
	lastpoint.x = 0;
	lastpoint.y = 0;
    t_point dimPrint;
    dimMap = 2;
    dimPrint.x = 0;
    dimPrint.y = 0;
    initMap(map, 17); 
    dimMap = tetriMap(map,blocks, index, 2, lastpoint); 
    printMapPls(map,dimMap);
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
                index++;
            }
        }
        spaces++;
    }
    return (index);
}

int main(int argc, char** argv)
{

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