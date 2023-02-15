/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:04:47 by apommier          #+#    #+#             */
/*   Updated: 2023/02/15 15:23:13 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

void	OPER(std::string buffer, fdList &allFds, int userNbr)
{
	int pos;
	std::vector<std::string> splitBuff;
	std::string msg;
	
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() < 3)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "461 * OPER :Not enough parameters\n");
		return ;
	}
	if (splitBuff[2] != allFds.password)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "464 * :Password incorrect\n");
		return ;
	}
	pos = find_user(allFds, splitBuff[1]); //return direct user fd
	if (pos != -1)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "401 * SQUIT " + splitBuff[1] + " :No such nick/channel\n");
		return ;
	}
	allFds.userData[pos].op = 1;
	msg = "381 * " + allFds.userData[pos].nickname + " :You are now an IRC operator\n";
	send(allFds.userData[pos].fd, msg.c_str(), msg.size(), 0);
}