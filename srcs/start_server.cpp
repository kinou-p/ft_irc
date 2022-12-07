/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_server.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 21:44:20 by apommier          #+#    #+#             */
/*   Updated: 2022/12/07 01:25:31 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_irc.hpp"

void initialize(char **av)
{
	int sockFd;
	int epollFd;
	int newSockFd = 0;
	int opt = 1;
	struct sockaddr_in addr;
	int addrLen = sizeof(addr);

	sockFd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockFd == -1)
		ft_error("socket() error");
	if (setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
		ft_error("setsockopt() error");

	addr.sin_port = htons(atoi(av[1]));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	
	if (addr.sin_port <= 0)
		ft_error("wrong format for <port>\nneed to be an positive integer");
	if (bind(sockFd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		ft_error("bind() error");
	if (listen(sockFd, 100) == -1)
		ft_error("listen() error");
	newSockFd = accept(sockFd, (struct sockaddr *)&addr, (socklen_t*)&addrLen);
	if (newSockFd == -1)
		ft_error("accept() error");
	
	char buffer[1024];
	int nbrRead;
	while (strncmp("/quit", buffer, 5))
	{
		nbrRead = read()
	}

	
	epollFd = epoll_start();
	epoll_add(epollFd, newSockFd);
	start_loop(epollFd, sockFd, newSockFd);

	
	//send(newSockFd, "hello", 5, 0);
}