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

void push(t_dlist** head_ref, char *name, struct stat buf) 
{ 
    /* 1. allocate node */
    t_dlist* new_node = malloc(sizeof(t_dlist));
   
    /* 2. put in the data  */
    new_node->blocks = -1;
    new_node->name = ft_strdup(name);
    new_node->sub = NULL;
    ft_memcpy(&(new_node->buf),&buf,sizeof(buf));   
    /* 3. Make next of new node as head */
    new_node->next = (*head_ref); 
   
    /* 4. move the head to point to the new node */
    (*head_ref) = new_node; 
} 
    void isFile(t_dlist *head, struct stat buf, char *name)
    {
        if (head->name == NULL)
        {
            ft_memcpy(&(head->buf), &buf, sizeof(buf));
            append(&head->sub, name, buf);
        }
        else
            append(&head->sub, name, buf);
    }
    char *takeDir(char *name)
    {
        char *result;
        int i;
        int len;

        if (!name)
            return (NULL);
        i = 0;
        len = ft_strlen(name);
        result = malloc(len);
        while(len--)
        {
            if (name[len] == '/')
                break;
        }
        while(i != len)
        {
            result[i] = name[i];
            i++;
        }
        result[i] = '\0';
        return (result);
    }

    char *takeName(char *name)
    {
        char *result;
        int i;
        int len;

        if (!name)
            return (NULL);
        i = 0;
        len = ft_strlen(name);
        result = malloc(len);
        while(len--)
        {
            if (name[len] == '/')
                break;
        }
        ++len;
        while(name[len])
        {
            result[i] = name[len++];
            i++;
        }
        result[i] = '\0';
        return (result);
    }
    int isInDir(char *name)
    {
        DIR *dr;
        struct dirent *de;
        char *namer;
        char *temp;

        temp = name;
        if (checkPos(name, '/') < 0)
            temp = concat(".", name);
        else
            name = takeName(name);
        
        namer = takeDir(temp);
        if ((dr = opendir(namer)))
        {
            while ((de = readdir(dr)) != NULL)
            {
                if (ft_strcmp(de->d_name, name) == 0)
                    return (1);
            }
        }
        
        return (0);
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
        head->sub = newList();
        head->next = NULL;
        head->name = NULL;
        spec = malloc(sizeof(t_spec));
        spec->flags = 0;
        spec->dirs = 0;
        tmp = head;
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
                        head->name = ft_strdup(argv[args]);
                        ft_memcpy(&(head->buf), &buf, sizeof(buf));
                    }
                    else
                        appendD(&head, argv[args], buf);
                    next_dir(argv[args], head, spec);
                    spec->dirs += 1;
                }
                else
                {
                    if (S_ISREG(buf.st_mode) && isInDir(argv[args]))
                    {
                        if (!(spec->flags & F_BIT))
                        {
                            if (head->name == NULL)
                            {
                                printf("We are adding %s\n", argv[args]);
                                head->name = ft_strdup(".");
                                ft_memcpy(&(head->sub->buf), &buf, sizeof(buf));
                                head->sub->name = argv[args];
                            }
                            else
                            {
                                push(&head,".", buf);
                                append(&head->sub,argv[args],buf);
                                //head->next->name = ft_strdup(".");
                                //ft_memcpy(&(head->next->sub->buf), &buf, sizeof(buf));
                                //head->next->sub->name = argv[args];
                            }
                                //push(&head, argv[args], buf);
                        }
                        else
                            append(&head->sub, argv[args], buf);
                        spec->dirs += 1;
                        spec->flags |= F_BIT;
                    }
                    else
                    {
                        printf("%s no file or directory\n", argv[args]);
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
        if (argc == 1 || head->name == NULL)
        {
            lstat(".", &buf);
            head->name = ft_strdup(".");
            head->next = NULL;
            ft_memcpy(&(head->buf), &buf, sizeof(buf));
            next_dir(head->name, head, spec);
        }
        if ((spec->flags & F_BIT))
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
            tmp = head->next;
            delList(head->sub);
            ft_strdel(&head->name);
            ft_memdel((void **)&head);
            free(head);
            head = tmp;
            if (!head)
            {
                free(spec);
                delList(tmp);
                return (0);
            }
        }
        if (ft_strcmp(head->name, ".") == 0)
        {
            loadSubs(head, spec);
            print_dir(head, spec);
            tmp = head;
            head = head->next;
        }
        ft_sortPrint(head, spec);
        free(spec);
        delList(tmp->sub);
        delList(tmp);
        return 0; 
    } 
