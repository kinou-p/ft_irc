/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:34:57 by apommier          #+#    #+#             */
/*   Updated: 2023/02/23 17:47:50 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

void	KILL(std::string buffer, fdList &allFds, int userNbr)
{
	int pos;
	std::vector<std::string> splitBuff;

	if (!allFds.userData[userNbr].registered) 
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "451 * KILL :You have not registered\n");
		return ;
	}
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() < 3)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "431 * KILL :Not enought argument\n");
		return ;
	}
	if (!allFds.userData[userNbr].op)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "481 * :Permission Denied- You're not an IRC operator\n");
		return ;
	}
	pos = find_user(allFds, splitBuff[1]); 
	if (pos == -1)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "401 * KILL " + splitBuff[1] + " :No such nick/channel\n");
		return ;
	}
	std::string msg;
	std::string fullMsg;
	msg = "connection killed by " + allFds.userData[userNbr].nickname + " " + buffer.substr(buffer.find_first_of(':'), std::string::npos);
	fullMsg = ":" + allFds.userData[userNbr].nickname + "!" + allFds.userData[userNbr].userName + "@172.17.0.1 " + msg;
	send(allFds.userData[pos].fd, fullMsg.c_str(), fullMsg.size(), 0);
	//send_notice_msg(allFds, allFds.userData[userNbr].fd, userNbr)
	delete_user(allFds, pos);
	return ;
}