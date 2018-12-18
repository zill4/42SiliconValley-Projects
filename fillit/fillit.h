#ifndef FILLIT_H
# define FILLIT_H
# include "./libft/libft.h"
# include <stdio.h>

typedef struct  s_point
{
                int x;
                int y;
}               t_point;

typedef struct  s_block
{
                //until linked listed static 676 is used for max map.
                t_point point[4];
                int x_dim;
                int y_dim;
                int ox;
                int oy;
}               t_block;
/*
    FILL_IT RULE SET
    0. Takes in one param as a file of "Testriminos" to assemble.
    1. Every "Tetrimino" will fit in a 4x4 square and are seperated by a \n
    2. If input is invalid display usage and exit.
    3. File needs 1 - 26 "Tetriminos"
    Tetrimino:
        - 4 x 4 followed by a newline.
        - '#' or '.'
        - must touch one other block of the four sides.
        VALID:
        .... .... #### .... .##. .... .#.. .... ....
        ..## .... .... .... ..## .##. ###. ##.. .##.
        ..#. ..## .... ##.. .... ##.. .... #... ..#.
        ..#. ..## .... ##.. .... .... .... #... ..#.
        INVALID:
        #### ...# ##... #. .... ..## #### ,,,, .HH.
        ...# ..#. ##... ## .... .... #### #### HH..
        .... .#.. .... #. .... .... #### ,,,, ....
        .... #... .... .... ##.. #### ,,,, ....
        SAMPLE FILE:
        $> cat -e valid_sample.fillit
        ...#$
        ...#$
        ...#$
        ...#$
        $
        ....$
        ....$
        ....$
        ####$
        $
        .###$
        ...#$
        ....$
        ....$
        $
        ....$
        ..##$
        .##.$
        ....$
        $>
        FINAL OUTPUT NEEDS TO FILL THE SQUARE TO MOST UPPER LEFT.
        Can use alphabet for testing.
*/

#endif
