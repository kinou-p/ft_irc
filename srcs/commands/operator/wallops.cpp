/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wallops.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:09:38 by apommier          #+#    #+#             */
/*   Updated: 2023/02/17 21:13:21 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"


void	WALLOPS(std::string buffer, fdList &allFds, int userNbr)
{
	std::vector<std::string> splitBuff;
	std::string msg;
	
	//std::cout << "privmsg bufer= --" << buffer << std::endl;
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() < 2)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "431 * WALLOPS :Not enought argument\n");
		return ;
	}
	msg = ":" + allFds.userData[userNbr].nickname + " WALLOPS :" + buffer.substr(splitBuff[1].size() + std::string::npos + 1) + "\n";
	//msg = "PRIVMSG " + allFds.userData[userNbr].nickname + " " + buffer.substr(splitBuff[1].size() + std::string::npos + 1);
	for (int i = 0; i < allFds.nbrUser; i++)
	{
		if (allFds.userData[i].op && allFds.userData[i].mode.s)
			send(allFds.userData[i].fd, msg.c_str(), msg.size(), 0);
			//PRIVMSG(msg, allFds, userNbr);
	}
}