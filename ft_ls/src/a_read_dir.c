

#include "../includes/ft_ls.h"

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