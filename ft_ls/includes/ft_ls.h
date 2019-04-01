#ifndef FT_LS_H
# define FT_LS_H
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <string.h>
# include <time.h>
# include <grp.h>
# include <pwd.h>
typedef struct s_spec
{
    int     flags;
}              t_spec;

typedef struct s_dlist
{
    char *name;
    int blocks;
    struct stat buf;
    struct s_dlist* sub;
    struct s_dlist* next;
}               t_dlist;


# define FT_BIT(x) (1 << (x))
# define SPECIFIERS "lRart"
# define L              (0)
# define UPPER_R        (1)
# define A              (2)
# define LOWER_R        (3)
# define T              (4)
# define E              (5)
# define F              (6)
# define L_BIT          (FT_BIT(0))
# define UPPER_R_BIT    (FT_BIT(1))
# define A_BIT          (FT_BIT(2))
# define LOWER_R_BIT    (FT_BIT(3))
# define T_BIT          (FT_BIT(4))
# define ERROR          (FT_BIT(5))
# define F_BIT          (FT_BIT(6))
#endif