
#include "../includes/ft_ls.h"

void loadSubs(t_dlist *head, t_spec *spec)
{
    DIR *dr = opendir(head->name);
    struct stat buf;
    struct dirent *de;
    int count = -1;
    char *name = head->name;
    char *temp;
    head->sub = malloc(sizeof(t_dlist));
    head->sub->next = NULL;
    head->blocks = 0;
    if (dr != NULL)
    {
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