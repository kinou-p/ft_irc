/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:34:57 by apommier          #+#    #+#             */
/*   Updated: 2023/03/13 16:36:13 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

void	KILL(std::string buffer, fdList &allFds, int userNbr)
{
	int pos;
	std::vector<std::string> splitBuff;

	if (!allFds.userData[userNbr].registered) 
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "451 " + allFds.userData[userNbr].nickname + " KILL :You have not registered\r\n");
		return ;
	}
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() < 3)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "431 " + allFds.userData[userNbr].nickname + " KILL :Not enought argument\r\n");
		return ;
	}
	if (!allFds.userData[userNbr].op)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "481 " + allFds.userData[userNbr].nickname + " :Permission Denied- You're not an IRC operator\r\n");
		return ;
	}
	pos = find_user(allFds, splitBuff[1]); 
	if (pos == -1)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "401 " + allFds.userData[userNbr].nickname + " KILL " + splitBuff[1] + " :No such nick\r\n");
		return ;
	}
	std::string msg;
	std::string fullMsg;
	msg = "connection killed by " + allFds.userData[userNbr].nickname + " " + buffer.substr(buffer.find_first_of(':'), std::string::npos);
	fullMsg = ":" + allFds.userData[userNbr].nickname + "!" + allFds.userData[userNbr].userName + "@172.17.0.1 " + msg + "\r\n";
	send(allFds.userData[pos].fd, fullMsg.c_str(), fullMsg.size(), 0);
	delete_user(allFds, pos);
	return ;
}