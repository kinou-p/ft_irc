/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_loop.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 21:58:13 by apommier          #+#    #+#             */
/*   Updated: 2023/03/13 16:42:42 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_irc.hpp"

void start_loop(fdList &allFds)
{
	int eventNbr;
	int i;
	int nbr;

	allFds.alive = 1;
	while (allFds.alive)
	{
		eventNbr = epoll_wait(allFds.epollFd, allFds.events, MAX_EVENTS, 0);
		for (i = 0; i < eventNbr ; i++)
		{
			if (allFds.events[i].data.fd == allFds.serverFd)
				new_connection(allFds);
			else
			{
				nbr = find(allFds.userFdList.begin(), allFds.userFdList.end(), allFds.events[i].data.fd) - allFds.userFdList.begin();
				clientRequest(allFds, nbr);
			}
		}
	}
	std::cout << "dead server\n";

}