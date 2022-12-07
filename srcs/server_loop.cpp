/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_loop.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 21:58:13 by apommier          #+#    #+#             */
/*   Updated: 2022/12/07 01:16:41 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_irc.hpp"

#define MAX_EVENTS 5
#define READ_SIZE 10

void start_loop(int epollFd, int oldSock, int newSock)
{
	char buffer[1024] = { 0 };
	int readChar;

	std::cout << "loop start\n";
	while (strncmp("/quit", buffer, 5))
	{
		// std::cout << "hehe\n";
		readChar = read(newSock, buffer, 1024);
		buffer[readChar] = '\0';
		std::cout << "buffer: " << buffer << std::endl;
		// send(newSock, "message received", 18, 0);

		//event_count = epoll_wait(epoll_fd, events, MAX_EVENTS, 30000);	
		//for (i = 0; i < event_count; i++)
		//{
			
		//}
	}
	if (!strncmp("/quit", buffer, 5))
	{
		std::cout << "quit message received\n";
	}
}