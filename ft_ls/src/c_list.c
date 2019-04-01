#include "../includes/ft_ls.h"

t_dlist     *newNode(char *name, struct stat buf)
{
    t_dlist *new = malloc(sizeof(t_dlist));
    new->next = NULL;
    new->sub = NULL;
    memcpy(&(new->buf), &buf, sizeof(buf));
    new->name = strdup(name);
    return (new);
}

void	ft_memdel(void **ap)
{
	if (!ap)
		return ;
	free(*ap);
	*ap = NULL;
}
void				ft_strdel(char **as)
{
	ft_memdel((void **)as);
}
void				ft_bufdel(struct stat **as)
{
	ft_memdel((void **)as);
}
void    delList(t_dlist *list)
{
    while(list)
    {
        ft_strdel(&list->name);
        ft_memdel((void **)list);
        free(list);
        list = list->next;
    }
}
void	lstdel(t_dlist **list)
{
	t_dlist	*temp;

	if ((*list))
	{
		temp = (*list)->next;
		(*list)->next = NULL;
		ft_strdel(&(*list)->name);
		ft_memdel((void**)&(*list));
		lstdel(&(temp));
	}
}
void    append(t_dlist **head, char *name, struct stat buf)
{
    t_dlist *new;
    t_dlist *last;
    last = *head;
    new = malloc(sizeof(t_dlist));
    new->next = NULL;
    new->name = strdup(name);
    memcpy(&(new->buf),&buf,sizeof(buf));
    if (*head == NULL)
    {
        *head = new;
        return;
    }
    while(last->next)
        last = last->next;
    last->next = new;
}