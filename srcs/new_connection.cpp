/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_connection.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 22:26:27 by apommier          #+#    #+#             */
/*   Updated: 2023/02/11 14:47:52 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_irc.hpp"

void new_connection(fdList &allFds)
{
	struct sockaddr_in addr;
	int addrLen = sizeof(addr);
	int newFd;

	std::cout << "==========newconnection========\n";
	//std::cout << "in new adress  " << &allFds << std::endl;
	//std::cout << "new connection !" << std::endl;

	if (MAX_EVENTS == allFds.nbrUser)
	{
		std::cout << "new connection refused, already full" << std::endl;
		return ;
	}

	//int newUserFd;
	//allFds.userList.push_back(newUserFd);
	newFd = accept(allFds.serverFd, (struct sockaddr *)&addr, (socklen_t*)&addrLen);
	//allFds.userList[allFds.nbrUser] = newFd;
	allFds.userList.push_back(newFd);
	//std::cout << "newConnection | old user fd = " << newFd << std::endl;
	if (fcntl(newFd, F_SETFL, O_NONBLOCK) == -1)
		ft_error("fctnl() error");


	//std::cout << "fcntl return = " << newFd;
	//close(newFd);
	//std::cout << "newConnection | user fd = " << allFds.userList[allFds.nbrUser] << std::endl;
	
	clientData newElement;
	newElement.fd = newFd;
	allFds.userData.push_back(newElement);
	//allFds.userData[allFds.nbrUser].fd = allFds.userList[allFds.nbrUser];
	//std::cout << "newConnection | user in data fd = " << allFds.userData[allFds.nbrUser].fd << std::endl;
	
	epoll_add(allFds.epollFd, allFds.userList[allFds.nbrUser]);
	allFds.nbrUser++; 	
}