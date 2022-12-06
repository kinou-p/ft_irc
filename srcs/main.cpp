/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:27:33 by apommier          #+#    #+#             */
/*   Updated: 2022/12/06 19:08:00 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_irc.hpp"


#define PORT 8080

void ft_error(std::string str)
{
	std::cout << str << std::endl;
	if (errno)
		std::cout << strerror(errno);
	exit(1);
}

void initialize(char **av)
{
	int epollFd;
	int sockFd;
	int newSockFd = 0;
	int opt = 1;
	struct sockaddr_in addr;
	int addrLen = sizeof(addr);

	sockFd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockFd == -1)
		ft_error("socket() error");
	if (setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
		ft_error("setsockopt() error");

	std::cout << atoi(av[1]) << std::endl;

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

	send(newSockFd, "hello", 5, 0);
}

int main(int ac, char **av)
{


	if (!(ac == 3 || ac == 2))
		ft_error("wrong number of arguments\nFORMAT: ./ircserv <port> <password>");
	initialize(av);
	return (0);
}