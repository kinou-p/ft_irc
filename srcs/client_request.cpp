/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_request.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 22:34:36 by apommier          #+#    #+#             */
/*   Updated: 2023/02/11 23:53:10 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_irc.hpp"

bool clientRequest(fdList &allFds, int userNbr)//, 
{
	//int userFd = allFds.events[user].data.fd;
	char buf[1024] = {0};
	std::string buffer;
	size_t len = 1024;
	
	//buf.reserve(1024);
	//se demerder pour join quand pas \n
	// std::cout << "fd in client request " << allFds.userData[userNbr].fd << std::endl;
	// std::cout << "fd of list in client request " << allFds.userList[userNbr] << std::endl;
	// std::cout << "user nbr " << userNbr << std::endl;
	
	//std::cout << "client request!" << std::endl;
	//if (recv(allFds.userData[userNbr].fd, buf, len, 0) == -1)
	if (recv(allFds.userData[userNbr].fd, buf, len, 0) == -1)
		ft_error("recv() error");
	buffer = buf;
	if (buffer.empty())
	{
		//delete client
		delete_user(allFds, userNbr);
		// close(allFds.userData[userNbr].fd);
		// allFds.userData.erase(allFds.userData.begin() + userNbr);
		// allFds.userList.erase(allFds.userList.begin() + userNbr);
		// allFds.nbrUser--;
		// std::cout << "buffer empty\n";
		return (1);
	}
	//std::cout << "BUFFER: ---" << buf << "---" << std::endl;
	
	//split with \n and while (tab de split) -> parsing

	std::vector<std::string> splitBuff;
	split_but_keep(buffer, '\n', splitBuff);
	for (size_t i = 0; i < splitBuff.size(); i++)
	{
		parse_commands(splitBuff[i], allFds, userNbr);	
	}

	return (1);
}