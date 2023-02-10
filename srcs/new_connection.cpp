/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_connection.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 22:26:27 by apommier          #+#    #+#             */
/*   Updated: 2023/02/10 09:19:45 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_irc.hpp"

void new_connection(fdList &allFds)
{
	struct sockaddr_in addr;
	int addrLen = sizeof(addr);

	//std::cout << "in new adress  " << &allFds << std::endl;
	//std::cout << "new connection !" << std::endl;
	if (MAX_EVENTS == allFds.nbrUser)
	{
		std::cout << "new connection refused, already full" << std::endl;
		return ;
	}
	
	int newUserFd;
	allFds.userList.push_back(newUserFd);
	allFds.userList[allFds.nbrUser] = accept(allFds.serverFd, (struct sockaddr *)&addr, (socklen_t*)&addrLen);
	
	std::cout << "newConnection | user fd = " << allFds.userList[allFds.nbrUser] << std::endl;
	
	clientData newElement;
	allFds.userData.push_back(newElement);
	allFds.userData[allFds.nbrUser].fd = allFds.userList[allFds.nbrUser];
	
	std::cout << "newConnection | user in data fd = " << allFds.userData[allFds.nbrUser].fd << std::endl;
	
	epoll_add(allFds.epollFd, allFds.userList[allFds.nbrUser]);
	allFds.nbrUser++; 	
}

// void new_connection(fdList *allFds, struct epoll_event newClient)
// {
// 	struct sockaddr_in addr;
// 	int addrLen = sizeof(addr);

// 	std::cout << "new connection !" << std::endl;
// 	if (MAX_EVENTS == (*allFds).nbrUser)
// 		std::cout << "new connection refused, already full" << std::endl;
// 	(*allFds).userList[(*allFds).nbrUser] = accept((*allFds).serverFd, (struct sockaddr *)&addr, (socklen_t*)&addrLen);
	
// 	std::cout << "newConnection | user fd = " << (*allFds).userList[(*allFds).nbrUser] << std::endl;
	
// 	(*allFds).userData[(*allFds).nbrUser].fd = (*allFds).userList[(*allFds).nbrUser];
// 	std::cout << "newConnection | user in data fd = " << (*allFds).userData[(*allFds).nbrUser].fd << std::endl;
	
// 	epoll_add((*allFds).epollFd, (*allFds).userList[(*allFds).nbrUser]);
// 	(*allFds).nbrUser++; 	
// }