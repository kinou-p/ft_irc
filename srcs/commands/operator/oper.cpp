/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:04:47 by apommier          #+#    #+#             */
/*   Updated: 2023/03/10 21:04:49 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

void	OPER(std::string buffer, fdList &allFds, int userNbr)
{
	std::vector<std::string> splitBuff;
	std::string msg;
	
	if (!allFds.userData[userNbr].registered) 
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "451 " + allFds.userData[userNbr].nickname + " OPER :You have not registered\n");
		return ;
	}
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() < 3)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "461 " + allFds.userData[userNbr].nickname + " OPER :Not enough parameters\n");
		return ;
	}
	//:irc.local 491 kinou2 
	if (splitBuff[1] != OP_NAME)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "491 " + allFds.userData[userNbr].nickname + " :Invalid oper credentials\n");
		return ;
	}
	if (splitBuff[2] != OP_PASSWORD)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "464 " + allFds.userData[userNbr].nickname + " :Password incorrect\n");
		return ;
	}
	// pos = find_user(allFds, splitBuff[1]);
	// if (pos != -1)
	// {
	// 	cmd_error(allFds, allFds.userData[userNbr].fd, "401 " + allFds.userData[userNbr].nickname + " SQUIT " + splitBuff[1] + " :No such nick/channel\n");
	// 	return ;
	// }
	allFds.userData[userNbr].op = 1;
	allFds.userData[userNbr].mode.s = 1;
	msg = "381 " + allFds.userData[userNbr].nickname + " " + allFds.userData[userNbr].nickname + " :You are now an IRC operator\n";
	send(allFds.userData[userNbr].fd, msg.c_str(), msg.size(), 0);
}