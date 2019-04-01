#include "../includes/ft_ls.h"

int   checkPos(char* str, char c)
{
    char *tmp;
    int pos;
    tmp = strchr(str,c);
    pos = (int)(tmp - str);
    return (pos);
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
