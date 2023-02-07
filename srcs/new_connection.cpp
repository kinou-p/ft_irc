/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_connection.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 22:26:27 by apommier          #+#    #+#             */
/*   Updated: 2022/12/18 12:13:28 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_irc.hpp"

void new_connection(fdList allFds, struct epoll_event newClient)
{
	struct sockaddr_in addr;
	int addrLen = sizeof(addr);

	std::cout << "new connection !" << std::endl;
	if (MAX_EVENTS == allFds.nbrUser)
		std::cout << "new connection refused, already full" << std::endl;
	allFds.userList[allFds.nbrUser] = accept(allFds.serverFd, (struct sockaddr *)&addr, (socklen_t*)&addrLen);
	epoll_add(allFds.epollFd, allFds.userList[allFds.nbrUser]);
	allFds.nbrUser++; 	
}