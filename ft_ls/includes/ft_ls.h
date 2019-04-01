#ifndef FT_LS_H
# define FT_LS_H
# include "../libft/libft.h"
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

t_dlist *sort_list(t_dlist *lst, int (*cmp)(t_dlist *, t_dlist *));
void swap_info(t_dlist *one, t_dlist *second);
int s_byNameR(t_dlist *tmp1, t_dlist *tmp2);
int s_byName(t_dlist *tmp1, t_dlist *tmp2);
int     s_byTimeR(t_dlist *tmp1, t_dlist *tmp2);
int     s_byTime(t_dlist *tmp1, t_dlist *tmp2);
t_dlist     *newNode(char *name, struct stat buf);
void	ft_memdel(void **ap);
void				ft_strdel(char **as);
void				ft_bufdel(struct stat **as);
void    delList(t_dlist *list);
void	lstdel(t_dlist **list);
void    append(t_dlist **head, char *name, struct stat buf);
void	mode_print(int  mode);
char* concat(const char *s1, const char *s2);
int   checkPos(char* str, char c);
void  print_file(char *name, t_spec *spec);
void  print_dir(t_dlist *head, t_spec *spec);
void loadSubs(t_dlist *head, t_spec *spec);
void    printList(t_dlist *head, t_spec *spec);
void    printListR(t_dlist *head, t_spec *spec);
void  next_dir(char *name, t_dlist *head, t_spec *spec);
void set_flags(char *str, t_spec *spec);
void    ft_sorter(t_dlist *head, t_spec *spec);
t_dlist     *newList();
void    appendD(t_dlist **head, char *name, struct stat buf);
void    ft_sortPrint(t_dlist *head, t_spec *spec);

#endif