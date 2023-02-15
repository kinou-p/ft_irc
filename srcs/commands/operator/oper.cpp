/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:04:47 by apommier          #+#    #+#             */
/*   Updated: 2023/02/15 19:43:22 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

void	OPER(std::string buffer, fdList &allFds, int userNbr)
{
	std::vector<std::string> splitBuff;
	std::string msg;
	
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() < 3)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "461 * OPER :Not enough parameters\n");
		return ;
	}
	//:irc.local 491 kinou2 
	if (splitBuff[1] != OP_NAME)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "491 * :Invalid oper credentials\n");
		return ;
	}
	if (splitBuff[2] != OP_PASSWORD)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "464 * :Password incorrect\n");
		return ;
	}
	// pos = find_user(allFds, splitBuff[1]);
	// if (pos != -1)
	// {
	// 	cmd_error(allFds, allFds.userData[userNbr].fd, "401 * SQUIT " + splitBuff[1] + " :No such nick/channel\n");
	// 	return ;
	// }
	allFds.userData[userNbr].op = 1;
	msg = "381 * " + allFds.userData[userNbr].nickname + " :You are now an IRC operator\n";
	send(allFds.userData[userNbr].fd, msg.c_str(), msg.size(), 0);
}