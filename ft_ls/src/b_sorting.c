#include "../includes/ft_ls.h"

int     s_byTime(t_dlist *tmp1, t_dlist *tmp2)
{

    int diff_m = tmp1->buf.st_mtime - tmp2->buf.st_mtime;
    int diff_n = tmp1->buf.st_mtimespec.tv_nsec - tmp2->buf.st_mtimespec.tv_nsec;
    if (diff_m < 0)
        return (0);
    else if (diff_m == 0)
    {
        if (diff_n < 0)
            return (0);
        else
            return (1);
    }
    return (1);
}

int     s_byTimeR(t_dlist *tmp1, t_dlist *tmp2)
{

    int diff_m = tmp1->buf.st_mtime - tmp2->buf.st_mtime;
    int diff_n = tmp1->buf.st_mtimespec.tv_nsec - tmp2->buf.st_mtimespec.tv_nsec;
    if (diff_m < 0)
        return (1);
    else if (diff_m == 0)
    {
        if (diff_n < 0)
            return (1);
        else
            return (0);
    }
    return (0);
}

int s_byName(t_dlist *tmp1, t_dlist *tmp2)
{
    int diff_m = strcmp(tmp1->name, tmp2->name);
    if (diff_m <= 0)
        return (1);
    else
        return (0);
}

int s_byNameR(t_dlist *tmp1, t_dlist *tmp2)
{
    int diff_m = strcmp(tmp1->name, tmp2->name);
    if (diff_m > 0)
        return (1);
    else
        return (0);
}


void swap_info(t_dlist *one, t_dlist *second)
{
	char *str_tmp;
	struct stat buf_tmp;

	str_tmp = one->name;
	buf_tmp = one->buf;
	one->name = second->name;
	one->buf = second->buf;
	second->name = str_tmp;
	second->buf = buf_tmp;
}

t_dlist *sort_list(t_dlist *lst, int (*cmp)(t_dlist *, t_dlist *))
{
	if (lst == NULL)
		return (NULL);
	if (lst->next == NULL)
		return (lst);
	t_dlist *tmp = lst;
	t_dlist *tmp2 = lst;

	while(tmp->next)
	{
		while(tmp2->next)
		{
			if (cmp(tmp, tmp2) == 1)
                swap_info(tmp, tmp2);
			tmp2 = tmp2->next;
		}
		tmp2 = lst;
		tmp = tmp->next;
	}
	while (tmp2->next)
	{
		if (cmp(tmp, tmp2) == 1)
            swap_info(tmp, tmp2);
		tmp2 = tmp2->next;
	}
	return (lst);	
}

