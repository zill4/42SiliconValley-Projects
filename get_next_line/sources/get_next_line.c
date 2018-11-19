#include "../include/get_next_line.h"

int		openFile(const int fd)
{
	char *buffy;

	printf("value from read: %zd", read(fd,&buffy,0));
	if (!read(fd,buffy,10))
	{
		printf("Invalid file descriptor\n");
		return (-1);
	}
	else
	{
		printf("Good file descriptor\n");
		return (fd);
	}
}

int		get_next_line(const int fd, char **line)
{
    char* buf;
    size_t bufsize;
    //t_list *buffy;
	bufsize = 10;
    int value;
    if (line == NULL || fd < 0 || read(fd,&buf,0) < 0)
        return (-1);
    while (*buf != '\n')
    {
        value = read(fd,&line,bufsize);
        printf("The line read is: %s", *line);
		if (value < 0)
			return (-1);
    }

	
	read(fd, &buf, bufsize);
	//write(fd, &buf, bufsize);
	
	//printf("LINE: %s",buf);
	return(1);
}
