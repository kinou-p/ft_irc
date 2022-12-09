/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_server.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 21:44:20 by apommier          #+#    #+#             */
/*   Updated: 2022/12/09 23:57:24 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_irc.hpp"

void initialize(char **av)
{
	//int allFds.serverFd;
	//int epollFd;
	//int newSockFd = 0;
	int opt = 1;
	struct sockaddr_in addr;
	int addrLen = sizeof(addr);
	fdList	allFds;

	allFds.serverFd = socket(AF_INET, SOCK_STREAM, 0);
	if (allFds.serverFd == -1)
		ft_error("socket() error");
	if (setsockopt(allFds.serverFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
		ft_error("setsockopt() error");

	addr.sin_port = htons(atoi(av[1]));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	
	if (addr.sin_port <= 0)
		ft_error("wrong format for <port>\nneed to be an positive integer");
	if (bind(allFds.serverFd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		ft_error("bind() error");
	if (listen(allFds.serverFd, 100) == -1)
		ft_error("listen() error");
		
	// newSockFd = accept(allFds.serverFd, (struct sockaddr *)&addr, (socklen_t*)&addrLen);
	// if (newSockFd == -1)
	// 	ft_error("accept() error");
	
	// char buffer[1024];
	// int nbrRead;
	// while (strncmp("/quit", buffer, 5))
	// {
	// 	nbrRead = read()
	// }

	allFds.epollFd = epoll_start();
	epoll_add(allFds.epollFd, allFds.serverFd);
	start_loop(allFds);
	
	//send(newSockFd, "hello", 5, 0);
}