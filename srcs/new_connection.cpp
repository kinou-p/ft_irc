/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_connection.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 22:26:27 by apommier          #+#    #+#             */
/*   Updated: 2023/03/13 16:42:13 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_irc.hpp"

void new_connection(fdList &allFds)
{
	struct sockaddr_in addr;
	int addrLen = sizeof(addr);
	int newFd;

	std::cout << "==========NEW CLIENT========\n";
	newFd = accept(allFds.serverFd, (struct sockaddr *)&addr, (socklen_t*)&addrLen);
	if (newFd == -1)
	{
		std::cout << "accept error: client connexion canceled\n";
		return ;
	}
	allFds.userFdList.push_back(newFd);
	if (fcntl(newFd, F_SETFL, O_NONBLOCK) == -1)
		ft_error("fctnl() error");
	clientData newElement;
	newElement.fd = newFd;
	newElement.addr = addr;
	newElement.ip = inet_ntoa(addr.sin_addr);
	allFds.userData.push_back(newElement);
	epoll_add(allFds.epollFd, allFds.userFdList[allFds.nbrUser]);
	allFds.nbrUser++; 	
}