/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LS.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcrisp <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 20:11:45 by jcrisp            #+#    #+#             */
/*   Updated: 2019/03/25 21:11:59 by jcrisp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		//ft_bufdel((list)->buf);
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
    //free(&name);
    //free(&buf);
}

void    printIT(t_dlist *head)
{
    while(head->next)
    {
        printf("%s\n", head->name);
        head = head->next;
    }
     printf("%s\n", head->name);
}

int   checkPos(char* str, char c)
{
    char *tmp;
    int pos;
    tmp = strchr(str,c);
    pos = (int)(tmp - str);
    return (pos);
}

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


char* concat(const char *s1, const char *s2)
{
    char *temp = malloc(strlen(s1) + 2);
    strcpy(temp, s1);
    strcat(temp, "/");
    char *result = malloc(strlen(temp) + strlen(s2) + 1);
    strcpy(result, temp);
    strcat(result, s2);
    free(temp);
    //free(result);
    return result;
}
void	mode_print(int  mode)
{
	char c;
	size_t		i;
	static char temp[10];
	static char buff[] = "rwxrwxrwx";

	i = 0;
	while (i < 9)
	{
		temp[i] = (mode & (1 << (8 - i))) ? buff[i] : '-';
		i++;
	}
	temp[i] = '\0';
	if((mode & S_IFDIR) == S_IFDIR)
		c = 'd';
	else if ((mode & S_IFLNK) == S_IFLNK)
		c = 'l';
	else if ((mode & S_IFBLK) == S_IFBLK)
		c = 'b';
	else if ((mode & S_IFCHR) == S_IFCHR)
		c = 'c';
	else if ((mode & S_IFIFO) == S_IFIFO)
		c = 'p';
	else if ((mode & S_IFSOCK) == S_IFSOCK)
		c = 's';
	else
		c = '-';
	printf("%c%s", c, temp);
}
void  print_file(char *name, t_spec *spec)
{
    struct stat buf;
    lstat(name, &buf);
    if (spec->flags & L_BIT)
    {
        mode_print(buf.st_mode);
        printf(" %hu ",buf.st_nlink);
        printf("%-5s ",getpwuid(buf.st_uid)->pw_name);
        printf("%s ",getgrgid(buf.st_gid)->gr_name);
        printf("%6lld ",buf.st_size);
        printf("%.12s ",4+(ctime (&buf.st_mtime)));
    }
    printf("%s\n",name);
}
void  print_dir(t_dlist *head, t_spec *spec)
{
    t_dlist *tmp;
            if (head->sub == NULL || head->blocks == -1)
                return ;
            if (strcmp(head->name, "."))
                printf("%s\n", head->name);
            if (spec->flags & L_BIT && !(spec->flags & F_BIT))
                printf("Total %d\n",head->blocks);
            if (head->sub != NULL)
            {
                while(head->sub->next)
                {
                    if (spec->flags & L_BIT)
                    {
                        mode_print(head->sub->buf.st_mode);
                        printf(" %hu ",head->sub->buf.st_nlink);
                        printf("%-5s ",getpwuid(head->sub->buf.st_uid)->pw_name);
                        printf("%s ",getgrgid(head->sub->buf.st_gid)->gr_name);
                        printf("%6lld ",head->sub->buf.st_size);
                        printf("%.12s ",4+(ctime (&head->sub->buf.st_mtime)));
                    }
                    printf("%s\n",head->sub->name);
                    tmp = head->sub->next;
                    ft_strdel(&head->sub->name);
                    ft_memdel((void **)&head->sub);
                    free(head->sub);
                    head->sub = tmp;
                }
                if (spec->flags & L_BIT)
                {
                    mode_print(head->sub->buf.st_mode);
                    printf(" %hu ",head->sub->buf.st_nlink);
                    printf("%-5s ",getpwuid(head->sub->buf.st_uid)->pw_name);
                    printf("%s ",getgrgid(head->sub->buf.st_gid)->gr_name);
                    printf("%6lld ",head->sub->buf.st_size);
                    printf("%.12s ",4+(ctime (&head->sub->buf.st_mtime)));
                }
                printf("%s\n ",head->sub->name);
                //free(head->sub->name);
                //free(head->sub);
                delList(head->sub);
            }
        //lstdel(&head->sub);
        printf("\n"); 
}

void loadSubs(t_dlist *head, t_spec *spec)
{
    DIR *dr = opendir(head->name);
    struct stat buf;
    struct dirent *de;
    int count = -1;
    // char *name = strdup(head->name);
    char *name = head->name;
    char *temp;
    head->sub = malloc(sizeof(t_dlist));
    head->sub->next = NULL;
    head->blocks = 0;
    if (dr != NULL)
    {
        // read in all sub-directories
        while ((de = readdir(dr)) != NULL)
        {   
            temp = concat(name, de->d_name);
            lstat(temp, &buf);  
            if (spec->flags & A_BIT)
            {
                    if (count == -1) 
                    {			
                        head->sub->name = strdup(de->d_name);
                        memcpy(&(head->sub->buf),&buf,sizeof(buf));
                        count += 1;
                    }
                    else
                        append(&head->sub, de->d_name, buf);
                    count += buf.st_blocks;
            }
            else
            {
                if ((strcmp(de->d_name, "..") && strcmp(de->d_name, ".") && checkPos(de->d_name, '.') != 0) || (strchr(de->d_name, '.') == NULL))
                {
                    if (count == -1) 
                    {			
                        head->sub->name = strdup(de->d_name);
                        memcpy(&(head->sub->buf),&buf,sizeof(buf));
                        count += 1;
                    }
                    else
                        append(&head->sub, de->d_name, buf);
                    count += buf.st_blocks;
                }
            }
            free(temp);
        }
        head->blocks = count;
        if (head->sub->name == NULL)
        {
            closedir(dr);
            return ;
        }
        if (spec->flags & T_BIT)
        {
            if (spec->flags & LOWER_R_BIT)
                sort_list(head->sub, s_byTimeR);
            else
                sort_list(head->sub, s_byTime);
        }
        else
        {
            if (spec->flags & LOWER_R_BIT)
                sort_list(head->sub, s_byNameR);
            else
                sort_list(head->sub, s_byName);
        }
        closedir(dr);
    }
}

void    printListR(t_dlist *head, t_spec *spec)
{
    if (!head)
        return ;
    if (head->next)
        printListR(head->next, spec);
    loadSubs(head, spec);
    print_dir(head, spec);
}

void    printList(t_dlist *head, t_spec *spec)
{
    if (!head)
        return ;
    while (head->next)
    {
        loadSubs(head, spec);
        print_dir(head, spec);
        head = head->next;
    }
    loadSubs(head, spec);
    print_dir(head, spec);
}

void  next_dir(char *name, t_dlist *head, t_spec *spec)
{
    DIR *dr = opendir(name);
    struct dirent *de;
    struct stat buf;
    char* temp;
    if (dr != NULL)
    {
        while ((de = readdir(dr)) != NULL)
        {
            temp = concat(name, de->d_name);
           lstat(temp, &buf);
           free(temp);
            if (spec->flags & UPPER_R_BIT)
            {
                if (S_ISDIR(buf.st_mode) )
                {
                    if (spec->flags & A_BIT)
                    {
                        if ((strchr(de->d_name, '.') == 0 && strlen(de->d_name) > 1 && !(strcmp(de->d_name, ".."))) || (strchr(de->d_name, '.') == NULL) || (strchr(de->d_name, '.') != NULL && strcmp(de->d_name, "..") && strcmp(de->d_name, ".")))
                        {            
                            temp = concat(name, de->d_name);
                            append(&head,temp, buf);
                            next_dir(temp, head, spec);
                            free(temp);
                        }
                    }
                    else
                    {

                        if ((strcmp(de->d_name, "..") && strcmp(de->d_name, ".") && checkPos(de->d_name, '.') != 0) || (strchr(de->d_name, '.') == NULL))
                        {            
                            temp = concat(name, de->d_name);
                            append(&head,temp, buf);
                            next_dir(temp, head, spec);
                            free(temp);
                        }
                    }                                 
                }
            }
        }
        closedir(dr);
    }
}

void set_flags(char *str, t_spec *spec)
{
    int i = 0;
    if (!str){
        printf("ERROR Bad String!\n");
        spec->flags |= ERROR;
        return ;
    }
    if (str[0] != '-')
    {
        printf("ERROR Bad Flag format\n");
        spec->flags |= ERROR;
        return ;
    }
    i++;
    while (str[i])
    {
        if (str[i] == 'l')
            spec->flags |= L_BIT;
        else if (str[i] == 'a')
            spec->flags |= A_BIT;
        else if (str[i] == 'r')
            spec->flags |= LOWER_R_BIT;
        else if (str[i] == 'R')
            spec->flags |= UPPER_R_BIT;
        else if (str[i] == 't')
            spec->flags |= T_BIT;
        else
            spec->flags |= ERROR;
        
        i++;
    }
}

int main(int argc, char **argv) 
{ 
    t_dlist *head;
    t_dlist *tmp;
    int args;
 	struct stat buf;
    t_spec *spec;

    args = 1;
    head = malloc(sizeof(t_dlist));
    head->next = NULL;
    head->name = NULL;
    spec = malloc(sizeof(t_spec));
    spec->flags = 0;

    while (args < argc)
    {
        if (argv[args][0] == '-')
            set_flags(argv[args], spec);
        else
        {
            lstat(argv[args], &buf);
            if (S_ISDIR(buf.st_mode))
            {
                if (head->name == NULL)
                {
                    head->name = strdup(argv[args]);
                    memcpy(&(head->buf), &buf, sizeof(buf));
                }
                else
                    append(&head, argv[args], buf);
                next_dir(argv[args], head, spec);
            }
            else
            {
                if (S_ISREG(buf.st_mode))
                {
                    spec->flags |= F_BIT;
                    if (head->name == NULL)
                    {
                        //head->name = strdup(".");
                        memcpy(&(head->buf), &buf, sizeof(buf));
                        append(&head->sub, argv[args], buf);
                    }
                    else
                        append(&head->sub, argv[args], buf);
                }
                else
                {
                    printf("%s no file or directory", argv[args]);
                    return (-1);
                }
            }
            
        }
        if (spec->flags & ERROR)
        {
            printf("ft_ls: illegal option -- %s\nusage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n", argv[args]);
            return (-1);
        }
        args++;
    }
    if (argc <= 2)
    {
        lstat(".", &buf);
        head->name = strdup(".");
        head->next = NULL;
        memcpy(&(head->buf), &buf, sizeof(buf));
        next_dir(head->name, head, spec);
    }
    if (!(spec->flags & F_BIT))
        loadSubs(head, spec);
    else
    {
        if (spec->flags & T_BIT)
        {
            if (spec->flags & T_BIT && spec->flags & LOWER_R_BIT)
                sort_list(head->sub, s_byTimeR); 
            else
                sort_list(head->sub, s_byTime);
        }
        else
        {
            if (spec->flags & LOWER_R_BIT)
                sort_list(head->sub, s_byNameR);
            else
                sort_list(head->sub, s_byName);
        }
        print_dir(head, spec);
        free(spec);
        ft_strdel(&head->name);
        ft_memdel((void **)&head);
        delList(head);
        return (0);
    }
    print_dir(head, spec);
    tmp = head;
    head = head->next;
    if (spec->flags & T_BIT)
    {
        if (spec->flags & T_BIT && spec->flags & LOWER_R_BIT)
        {
            sort_list(head, s_byTimeR);
            printList(head, spec);

        }
        else
        {
            sort_list(head, s_byTime);
            printListR(head, spec);
        }
    }
    else
    {
        if (spec->flags & LOWER_R_BIT)
        {
            sort_list(head, s_byName);
            printListR(head, spec);

        }
        else
        {
            sort_list(head, s_byNameR);
            printListR(head, spec);
        }
    }
    free(spec);
    free(tmp);
    delList(tmp);
    return 0; 
} 
