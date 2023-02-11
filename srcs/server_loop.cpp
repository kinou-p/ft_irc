/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_loop.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 21:58:13 by apommier          #+#    #+#             */
/*   Updated: 2023/02/11 14:06:49 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_irc.hpp"

void start_loop(fdList &allFds)
{
	bool alive = true;
	//int readChar;
	int eventNbr;
	int i;
	//int userId;
	int nbr;
	
	std::cout << "serverFd: " << allFds.serverFd << std::endl;
	while (alive)
	{
		//std::cout << "\n\n\nwhile alive event loop" << std::endl;
		//std::cout << "in loop nbr user = " << allFds.nbrUser << std::endl;
		eventNbr = epoll_wait(allFds.epollFd, allFds.events, MAX_EVENTS, 5000);
		//std::cout << "eventNbr: " << eventNbr << std::endl;	
		//std::cout << "in loop adress  " << &allFds << std::endl;
		for (i = 0; i < eventNbr ; i++)
		{
			
			//std::cout << "event[i]'s fd: " << allFds.events[i].data.fd << std::endl;
			//std::cout << "i= " << i << std::endl;
			if (allFds.events[i].data.fd == allFds.serverFd)
			{
				new_connection(allFds);
				//std::cout << "after new fd loop " << allFds.userData[i].fd << std::endl;
			}
			else
			{
				nbr = find(allFds.userList.begin(), allFds.userList.end(), allFds.events[i].data.fd) - allFds.userList.begin();
				//if (!clientRequest(allFds, i))
				if (!clientRequest(allFds, nbr))
					alive = false;

			}
		}
	}
	std::cout << "dead server\n";

}