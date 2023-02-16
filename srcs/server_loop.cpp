/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_loop.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 21:58:13 by apommier          #+#    #+#             */
/*   Updated: 2023/02/16 23:01:04 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_irc.hpp"

void start_loop(fdList &allFds)
{
	//bool alive = true;
	//int readChar;
	int eventNbr;
	int i;
	//int userId;
	int nbr;
	
	
	allFds.alive = 1;
	//std::cout << "serverFd: " << allFds.serverFd << std::endl;
	while (allFds.alive)
	{
		//std::cout << "---------start loop-----------\n";
		//std::cout << "\n\n\nwhile alive event loop" << std::endl;
		//std::cout << "in loop nbr user = " << allFds.nbrUser << std::endl;
		
		eventNbr = epoll_wait(allFds.epollFd, allFds.events, MAX_EVENTS, 0);

		//eventNbr = epoll_wait(allFds.epollFd, allFds.events, MAX_EVENTS, 5000);

		//std::cout << "eventNbr = " << eventNbr << std::endl;
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
				nbr = find(allFds.userFdList.begin(), allFds.userFdList.end(), allFds.events[i].data.fd) - allFds.userFdList.begin();
				//if (!clientRequest(allFds, i))
				// if (!clientRequest(allFds, nbr))
				// 	alive = false;
				clientRequest(allFds, nbr);
			}
		}
		//std::cout << "---------end loop-----------\n";
	}
	std::cout << "dead server\n";

}