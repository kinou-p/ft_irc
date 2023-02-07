/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_request.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 22:34:36 by apommier          #+#    #+#             */
/*   Updated: 2023/02/06 12:36:52 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_irc.hpp"

bool clientRequest(fdList allFds, int clientFd)
{
	char buf[1024] = {0};
	size_t len = 1024;
	
	std::cout << "client request!" << std::endl;
	if (recv(clientFd, buf, len, 0) == -1)
		ft_error("recv() error");
	std::cout << "BUFFER: ---" << buf << "---" << std::endl;
	parse_commands(buf, allFds);
	return (1);
}