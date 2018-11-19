/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcrisp <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 14:14:08 by jcrisp            #+#    #+#             */
/*   Updated: 2018/11/18 18:01:28 by jcrisp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int		openFile(const int fd)
{
	char *buffy;

	printf("value from read: %d", read(fd,&buffy,0));
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
	if (!openFile(fd))
	{	
		return (-1);
	}
	size_t bufsize;
	char *buf;
	bufsize = 10;
	
	read(fd, &buf, bufsize);
	//write(fd, &buf, bufsize);
	
	//printf("LINE: %s",buf);
	return(1);
}

int main()
{
	char* buf;
	get_next_line(1,&buf);
	//printf("Hello World");	
	return (0);
}