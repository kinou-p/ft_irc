/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:14:15 by apommier          #+#    #+#             */
/*   Updated: 2023/02/22 20:04:19 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

//:irc.server.net 353 user = #channel :@user1 +user2 user3
//:irc.server.net 366 user #channel :End of /NAMES list.

void	names_reply(fdList &allFds, channelData &chan, int fd, std::string user)
{
	std::string msg;
	msg = "353 " + user + " = " + chan.name + " :";
	for (int i = 0; i < chan.nbrUser; i++)
	{
		if (chan.userList[i]->mode.o)//ischanop 
			msg += "=" + chan.userList[i]->nickname + " ";
		else if (chan.userList[i]->mode.o)//verbose
			msg += "@" + chan.userList[i]->nickname + " ";
		else
			msg += "+" + chan.userList[i]->nickname + " ";
	}
	msg += "\n";
	std::cout << "name msg= " << msg;
	cmd_reply(allFds, fd, msg);
}

void	NAMES(std::string buffer, fdList &allFds, int userNbr)
{
	(void)buffer; 
	(void)allFds;
	(void)userNbr;
	std::vector<std::string> splitBuff;
	int pos;
	
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() == 1 || splitBuff[1] == "0")
	{
		for (size_t i = 0; i < allFds.channelList.size(); i++)
		{
			if ((!allFds.channelList[i].mode.p && !allFds.channelList[i].mode.s) 
				|| is_joined(allFds, allFds.channelList[i].name, userNbr))
			{
				names_reply(allFds, allFds.channelList[i], allFds.userData[userNbr].fd, allFds.userData[userNbr].nickname);
				//print who
			}
		}
		return ;
	}
	if ((pos = find_channel(allFds, splitBuff[1])) != -1)
	{
		if ((!allFds.channelList[pos].mode.p && !allFds.channelList[pos].mode.s) 
				|| is_joined(allFds, allFds.channelList[pos].name, userNbr))
		{
			names_reply(allFds, allFds.channelList[pos], allFds.userData[userNbr].fd, allFds.userData[userNbr].nickname);
		}
		return; //??
	}
	return ;
}
