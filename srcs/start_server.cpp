/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_server.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 21:44:20 by apommier          #+#    #+#             */
/*   Updated: 2023/03/13 16:43:06 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_irc.hpp"

// void initialize_function_ptr(fdList	allFds)
// {
// 	// int i = 0;
// 	// for (i = 0; i < allFds.parsingTab.cmdNbr, i++)	
// }

void initialize(char **av)
{
	int opt = 1;
	struct sockaddr_in addr;
	fdList allFds;

	allFds.nbrUser = 0;
	allFds.password = av[2];
	std::cout << "pass= " << av[2] << std::endl;
	allFds.serverFd = socket(AF_INET, SOCK_STREAM, 0);
	if (allFds.serverFd == -1)
		ft_error("socket() error");
	if (setsockopt(allFds.serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
		ft_error("setsockopt() error");

	addr.sin_port = htons(atoi(av[1]));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	
	if (addr.sin_port <= 0)
		ft_error("wrong format for <port>\nneed to be an positive integer");
	if (bind(allFds.serverFd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		ft_error("bind() error");
	if (listen(allFds.serverFd, 10) == -1)
		ft_error("listen() error");
		
	time_t timer;
	time(&timer);
	allFds.creation_date = ctime(&timer);
	allFds.epollFd = epoll_start();
	epoll_add(allFds.epollFd, allFds.serverFd);
	start_loop(allFds);
}