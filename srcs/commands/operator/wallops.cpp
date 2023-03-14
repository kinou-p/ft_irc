/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wallops.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:09:38 by apommier          #+#    #+#             */
/*   Updated: 2023/03/14 06:23:21 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"


void	WALLOPS(std::string buffer, fdList &allFds, int userNbr)
{
	std::vector<std::string> splitBuff;
	std::string msg;
	
	if (!allFds.userData[userNbr].registered) 
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "451 " + allFds.userData[userNbr].nickname + " WALLOPS :You have not registered\r\n");
		return ;
	}
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() < 2)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "431 " + allFds.userData[userNbr].nickname + " WALLOPS :Not enought argument\r\n");
		return ;
	}
	msg = ":" + allFds.userData[userNbr].nickname + " WALLOPS :" + buffer.substr(splitBuff[1].size() + std::string::npos + 1) + "\r\n";
	for (int i = 0; i < allFds.userData.size(); i++)
	{
		if (allFds.userData[i].op && allFds.userData[i].mode.s)
			send(allFds.userData[i].fd, msg.c_str(), msg.size(), 0);
	}
}