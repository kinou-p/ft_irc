/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_loop.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 21:58:13 by apommier          #+#    #+#             */
/*   Updated: 2023/02/06 12:33:21 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_irc.hpp"

void start_loop(fdList allFds)
{
	bool alive = true;
	char buffer[1024] = { 0 };
	struct epoll_event events[MAX_EVENTS];
	int readChar;
	int eventNbr;

	std::cout << "serverFd: " << allFds.serverFd << std::endl;
	while (alive)
	{
		// std::cout << "hehe\n";
		// readChar = read(allFds.serverFd, buffer, 1024);
		//recv(int allFds.serverFd, void *buf, size_t len, int flags);
		//buffer[readChar] = '\0';
		
		// send(clientFd, "message received", 18, 0);

		eventNbr = epoll_wait(allFds.epollFd, events, MAX_EVENTS, 5000);
		std::cout << "eventNbr: " << eventNbr << std::endl;	
		for (int i = 0; i < eventNbr ; i++)
		{
			std::cout << "event[i]'s fd: " << events[i].data.fd << std::endl;
			if (events[i].data.fd == allFds.serverFd)
				new_connection(allFds, events[i]);
			else if (!clientRequest(allFds, events[i].data.fd))
			{
				alive = false;
				//else
				//	std::cout << "F*CK i dont know" << std::endl;
				//if (strncmp("QUIT", buffer, 4))
				//	alive = 0;
			}
		}
		if (!strncmp("/quit", buffer, 5))
			std::cout << "quit message received\n";

	}
	std::cout << "dead server\n";

}