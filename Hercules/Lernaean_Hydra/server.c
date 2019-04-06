/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcrisp <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 13:41:11 by jcrisp            #+#    #+#             */
/*   Updated: 2019/03/08 13:41:14 by jcrisp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


    // Instead of SOCK_STREAM use SOCK_RAW
    // Instead of 8 use IPPROTO_ICMP
    /* For Reference
        IP(dummy)   IPPROTO_IP      0
        ICMP        IPPROTO_ICMP    1
        IGMP        IPPROTO_IGMP    2
        Gateway     IPPROTO_GGP     3
        TCP         IPPROTO_TCP     6
        PUP         IPPROTO_PUP    12
        UDP         IPPROTO_UDP    17
        XND IDP     IPPROTO_IDP    22
        Net Disk    IPPROTO_ND     77
        Raw IP      IPPROTO_RAW   255
    */
/*Required Headers*/
 
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
 
    char str[100];
    int listen_fd, comm_fd;
 
    struct sockaddr_in servaddr;
 
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
 
    bzero( &servaddr, sizeof(servaddr));
 
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(21000);
 
    bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
 
    listen(listen_fd, 10);
 
    comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);
 
    while(1)
    {
 
        bzero( str, 100);
 
        read(comm_fd,str,100);
        if (strcmp(str, "ping\n") == 0){
            printf("pong pong\n");
            write(comm_fd, "pong pong\n", strlen("pong pong\n")+1);
        }
        else{
            printf("Usage: Send ping from client.\n");
            write(comm_fd, "Usage: Send ping from client.\n", strlen("Usage: Send ping from client.\n")+1);
        }
    }
}
