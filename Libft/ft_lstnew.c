/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcrisp <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 20:32:36 by jcrisp            #+#    #+#             */
/*   Updated: 2018/10/10 23:11:34 by jcrisp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_memcpy.c"
#include <stdio.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *new_node;
	if (!(new_node = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (!content || !content_size)
	{
		new_node->data = NULL;
		new_node->content_size = 0;
	}
	else
	{
		if(!(new_node->data = malloc(content_size)))
			return (NULL);
		new_node->content_size = content_size;
		ft_memcpy(new_node->data, content, content_size);
	}
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstdelone(t_list **alst, void(*del)(void *, size_t))
{
	del(*alst,*alst->content_size);
	free(*alst);
	*alst = NULL;
}

void	ft_lstdel(t_list **alst, void(*del)(void *,size_t))
{
	while(*alst->next)
	{
		ft_lstdelone(&alst->next, del);
		*alst = *alst->next;
	}
}

void	ft_lstadd(t_list **alst, t_list *new)
{
	new->next = *alst;
	*aslt = new;
}

void	ft_lstiter(t_list *lst, void(*f)(t_list *elem))
{
	if (!lst)
		return ;
	t_list *temp;
	temp = lst;
	while(temp->next)
	{
		f(temp);
		temp = temp->next;
	}

}

t_list *ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	if(!lst)
		return (NULL);
}
int main()
{
	t_list *john;
	char* num = "Hello";
	int size = strlen(num);
	john = ft_lstnew((void*)num, size);
	printf("Data: %s \n", (char*)john->data);
	return (0);
}
