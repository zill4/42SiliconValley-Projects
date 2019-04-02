    #include "../includes/ft_ls.h"
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
void printDetails(t_dlist *head)
{
    mode_print(head->sub->buf.st_mode);
    printf(" %hu ",head->sub->buf.st_nlink);
    printf("%-5s ",getpwuid(head->sub->buf.st_uid)->pw_name);
    printf("%s ",getgrgid(head->sub->buf.st_gid)->gr_name);
    printf("%6lld ",head->sub->buf.st_size);
    printf("%.12s ",4+(ctime (&head->sub->buf.st_mtime)));
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
    printf("\n"); 
}

void memclear(t_dlist *head, t_dlist *tmp)
{
    tmp = head->sub->next;
    ft_strdel(&head->sub->name);
    ft_memdel((void **)&head->sub);
    free(head->sub);
    head->sub = tmp;
}

void  print_dir(t_dlist *head, t_spec *spec)
{
    t_dlist *tmp;

    tmp = NULL;
        if ((head->sub == NULL || head->blocks == -1) & (!(spec->flags & F_BIT)))
            return ;
        if (head->sub == NULL && spec->flags & F_BIT)
        {
            print_file(head->name, spec);
            return ;
        }
        if ((strcmp(head->name, ".") && (head->next)) || (spec->dirs > 1))
             printf("%s:\n", head->name);
        if (spec->flags & L_BIT && !(spec->flags & F_BIT))
            printf("Total %d\n",head->blocks);
        if(head->sub->name == NULL)
            head->sub = head->sub->next;        
        while(head->sub->next)
        {
            if (spec->flags & L_BIT)
                printDetails(head);
            printf("%s\n",head->sub->name);
            tmp = head->sub->next;
            //ft_strdel(&head->sub->name);
            ft_memdel((void **)&head->sub);
            free(head->sub);
            head->sub = tmp;
            //memclear(head, tmp);
        }
        if (spec->flags & L_BIT)
            printDetails(head);
        printf("%s\n ",head->sub->name);
        if (!(spec->flags & F_BIT))
            ft_strdel(&head->sub->name);
        ft_memdel((void **)&head->sub);
        delList(head->sub);
        free(head->sub);
        printf("\n"); 
}