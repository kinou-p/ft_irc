/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:14:17 by apommier          #+#    #+#             */
/*   Updated: 2023/03/13 16:38:26 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

//void	who_reply(fdList &allFds, int userNbr, int fd)
void	who_reply(fdList &allFds, clientData &user, int fd)
{
	std::string msg;
	
	msg = "352 "
	+ user.userName + " " 
	+ user.hostName + " irc.local " 
	+ user.nickname + " :0 " 
	+ user.realName + "\r\n";
	std::cout << "whoreply= " << msg << std::endl;
	cmd_reply(allFds, fd, msg);
}

void	WHO(std::string buffer, fdList &allFds, int userNbr)
{
	std::vector<std::string> splitBuff;
	int pos;
	(void) userNbr;

	if (!allFds.userData[userNbr].registered) 
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "451 " + allFds.userData[userNbr].nickname + " WHO :You have not registered\r\n");
		return ;
	}
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() == 1 || splitBuff[1] == "0")
	{
		for (int i = 0; i < allFds.nbrUser; i++)
		{
			if (!allFds.userData[i].mode.i || is_in_same(allFds, userNbr, i) || allFds.userData[userNbr].op)
				who_reply(allFds, allFds.userData[i], allFds.userData[userNbr].fd);
		}
		return ;
	}
	if ((pos = find_channel(allFds, splitBuff[1])) == -1)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "401 " + allFds.userData[userNbr].nickname + " " + splitBuff[1] + " :No such channel\r\n");
		return ;
	}
	for (size_t i = 0; i < allFds.channelList[pos].userList.size(); i++)
		who_reply(allFds, *allFds.channelList[pos].userList[i], allFds.userData[userNbr].fd);
	cmd_reply(allFds, allFds.userData[userNbr].fd, allFds.userData[userNbr].nickname + " :End of WHO list\n");
	return ;
}