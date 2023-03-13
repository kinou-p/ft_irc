/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squit.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:11:03 by apommier          #+#    #+#             */
/*   Updated: 2023/03/13 16:36:38 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

//ERR_NOPRIVILEGES                ERR_NOSUCHSERVER

void	SQUIT(std::string buffer, fdList &allFds, int userNbr)
{
	std::vector<std::string> splitBuff;
	split(buffer, ' ', splitBuff);

	if (!allFds.userData[userNbr].registered) 
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "451 " + allFds.userData[userNbr].nickname + " SQUIT :You have not registered\r\n");
		return ;
	}
	if (splitBuff.size() < 2)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "431 " + allFds.userData[userNbr].nickname + " SQUIT :Not enought argument\r\n");
		return ;
	}
	if (!allFds.userData[userNbr].op)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "481 " + allFds.userData[userNbr].nickname + " :Permission Denied- You're not an IRC operator\r\n");
		return ;
	}
	if (splitBuff[1] != "irc.local")
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "402 " + allFds.userData[userNbr].nickname + " " + splitBuff[2] + " :No such server\r\n");
		return ;
	}
	std::string fullMsg;
	for (int pos = 0; pos < allFds.nbrUser; pos++)
	{
		fullMsg = ":irc.local NOTICE " + allFds.userData[pos].userName + "." + allFds.userData[pos].nickname + " :*** You have been disconnected from the server\r\n";
		send(allFds.userData[pos].fd, fullMsg.c_str(), fullMsg.size(), 0);
		if (close(allFds.userData[pos].fd) != 0)
			ft_error("close() error");
	}
	std::cout << "squit | alive = 0\n";
	if (close(allFds.serverFd) != 0)
		ft_error("close() error");
	if (close(allFds.epollFd) != 0)
		ft_error("close() error");
	allFds.alive = 0;
	return ;
}