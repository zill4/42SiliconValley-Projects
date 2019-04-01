#include "../includes/ft_ls.h"

t_dlist     *newNode(char *name, struct stat buf)
{
    t_dlist *new = malloc(sizeof(t_dlist));
    new->next = NULL;
    new->sub = NULL;
    ft_memcpy(&(new->buf), &buf, sizeof(buf));
    new->name = ft_strdup(name);
    return (new);
}

t_dlist     *newList()
{
    t_dlist *new = malloc(sizeof(t_dlist));
    new->next = NULL;
    new->sub = NULL;
    new->blocks = 0;
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
        if (list->sub)
            delList(list->sub);
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
    new->blocks = 0;
    new->name = ft_strdup(name);
    new->sub = NULL;
    ft_memcpy(&(new->buf),&buf,sizeof(buf));
    if (*head == NULL)
    {
        *head = new;
        return;
    }
    while(last->next)
        last = last->next;
    last->next = new;
}

void    appendD(t_dlist **head, char *name, struct stat buf)
{
    t_dlist *new;
    t_dlist *last;

    last = *head;
    new = malloc(sizeof(t_dlist));
    new->next = NULL;
    new->blocks = 0;
    new->name = ft_strdup(name);
    new->sub = newList();
    ft_memcpy(&(new->buf),&buf,sizeof(buf));
    if (*head == NULL)
    {
        *head = new;
        return;
    }
    while(last->next)
        last = last->next;
    last->next = new;
}