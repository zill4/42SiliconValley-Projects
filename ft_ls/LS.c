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

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
/*
	SYS/STAT.H available info
dev_t     st_dev     ID of device containing file
ino_t     st_ino     file serial number
mode_t    st_mode    mode of file (see below)
nlink_t   st_nlink   number of links to the file
uid_t     st_uid     user ID of file
gid_t     st_gid     group ID of file
dev_t     st_rdev    device ID (if file is character or block special)
off_t     st_size    file size in bytes (if file is a regular file)
time_t    st_atime   time of last access
time_t    st_mtime   time of last data modification
time_t    st_ctime   time of last status change
blksize_t st_blksize a filesystem-specific preferred I/O block size for
                     this object.  In some filesystem types, this may
                     vary from file to file
blkcnt_t  st_blocks  number of blocks allocated for this object
 */

typedef struct s_spec
{
    int     flags;   
}              t_spec;
# define FT_BIT(x) (1 << (x))
/*
    -a      Include directory entries whose names begin with a dot (.).
    -l      (The lowercase letter ``ell''.)  List in long format.  (See below.)  If the output is to a terminal, a total sum for all the
             file sizes is output on a line before the long listing.
    -R      Recursively list subdirectories encountered.
    -r      Reverse the order of the sort to get reverse lexicographical order or the oldest entries first (or largest files last, if com-
             bined with sort by size
    -t      Sort by time modified (most recently modified first) before sorting the operands by lexicographical order.
*/
# define SPECIFIERS "lRart"
# define L          (0)
# define UPPER_R    (1)
# define A          (2)
# define LOWER_R    (3)
# define T          (4)
# define L_BIT      (FT_BIT(0))
# define UPPER_R_BIT    (FT_BIT(1))
# define A_BIT          (FT_BIT(2))
# define LOWER_R_BIT    (FT_BIT(3))
# define T_BIT          (FT_BIT(4))


// -R finds all directories in my current directory then preforms ls on that directory.
char* concat(const char *s1, const char *s2)
{  
    char *temp = malloc(strlen(s1) + 2);
    strcpy(temp, s1);
    strcat(temp, "/");
    char *result = malloc(strlen(temp) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here


    strcpy(result, temp);
    strcat(result, s2);
    return result;
}

void  next_dir(char *name)
{
    // Open the next directory.
    DIR *dr = opendir(name);
    struct dirent *de;
    struct stat buf;
    if (dr != NULL){
        //printf("ERROR could not open %s\n", name);
    //else
    //{
        while ((de = readdir(dr)) != NULL)
        {
            //printf("Current Dir is %s\n", de->d_name);
            // Get directories.
            lstat(de->d_name, &buf);
            //printf("CHECKING MODE %s : %d\n", de->d_name, buf.st_mode);
            if (S_ISDIR(buf.st_mode) || buf.st_mode == 33188){
                if ((strchr(de->d_name, '.') == 0 && strlen(de->d_name) > 1 && !(strcmp(de->d_name, ".."))) || (strchr(de->d_name, '.') == NULL))
                {
                    next_dir(concat(name, de->d_name));
                }              
            } 
        }
        printf("*--------------- Current dir %s -----------------*\n", name);
        dr = opendir(name);
        while ((de = readdir(dr)) != NULL)
            printf("%s\n", de->d_name);
        closedir(dr);
        printf("---------------------------------------------------------\n");
    }
    //closedir(dr);
}
void p_rec(int *arr, int pos)
{
    int i = pos;
    if (pos != 8)
    {
        pos++;
        p_rec(arr, pos);
    }
    printf("Arr: %d\n", arr[i]);
}

void set_flags(char *str, t_spec *spec)
{
    int i = 0;
    if (!str){
        printf("ERROR Bad String!\n");
        return ;
    }
    if (str[0] != '-')
    {
        printf("ERROR Bad Flag format\n");
        return ;
    }
    while (str[i])
    {
        if (str[i] == 'l')
            spec->flags |= L_BIT;
        if (str[i] == 'a')
            spec->flags |= A_BIT;
        if (str[i] == 'r')
            spec->flags |= LOWER_R_BIT;
        if (str[i] == 'R')
            spec->flags |= UPPER_R_BIT;
        if (str[i] == 't')
            spec->flags |= T_BIT;
        i++;
    }
}
int main(int argc, char **argv) 
{ 
    // args rovers
    int args = 1;
    // Pointer for directory entry 
    struct dirent *de;
    // Stat buffer   
 	struct stat buf;
    // Specifier struct; contains list of flags.
    t_spec *spec;
    // opendir() returns a pointer of DIR type.  
    DIR *dr = opendir("."); 
    // Must malloc for spec first
    spec = malloc(sizeof(t_spec));
    // Initialize flags to zero.
    spec->flags = 0;
    // Traverse argument variables for flags, find string.
        //First check for number of arguments
        if (argc > 1)
        {
            while (args < argc)
            {
                printf("Current argument %s\n", argv[args]);
                // If this argument is a flag, set the flag
                if (argv[args][0] == '-')
                    set_flags(argv[args], spec);
                else
                {
                    lstat(argv[args], &buf);
 		            //printf("Data: %ld\n", buf.st_ctime);
                   // printf("Type is: %hu\n", buf.st_mode); 
                    if (S_ISDIR(buf.st_mode))
                    {
                        //printf("is directory\n");
                        next_dir(argv[args]);
                    }
                }
                args++;
            }
        }   
    // Need to get flags from string passed as argument
    if (dr == NULL)  // opendir returns NULL if couldn't open directory 
    { 
        printf("Could not open current directory" ); 
        return 0; 
    } 
    
    // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html 
    // for readdir() 
    // while ((de = readdir(dr)) != NULL)
	//    	printf("%s\n", de->d_name);
    /* RECURSIVE TEST */
    int arr[] = {0,1,2,3,4,5,6,7,8};
    //p_rec(arr, 0);
    closedir(dr);     
    return 0; 
} 
