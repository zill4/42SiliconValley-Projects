/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcrisp <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 14:14:08 by jcrisp            #+#    #+#             */
/*   Updated: 2018/11/18 15:14:39 by jcrisp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

size_t	mem_allocator(
int		get_next_line(const int fd, char **line)
{
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
