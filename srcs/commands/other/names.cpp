/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:14:15 by apommier          #+#    #+#             */
/*   Updated: 2023/03/13 16:37:30 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

//:irc.server.net 353 user = #channel :@user1 +user2 user3
//:irc.server.net 366 user #channel :End of /NAMES list.

void	names_reply(fdList &allFds, channelData &chan, int fd, int userNbr)
{
	std::string msg;
	print_client_list(chan.opList);
	print_client_list(chan.verboseList);
	msg = "353 " + allFds.userData[userNbr].nickname + " = " + chan.name + " :";
	for (size_t i = 0; i < chan.userList.size(); i++)
	{
		if (chan.userList[i]->mode.i && !is_in_same(allFds, userNbr, find_user(allFds, chan.userList[i]->nickname) && !allFds.userData[userNbr].op))
			;
		else if (find_client_list(chan.opList, chan.userList[i]) != -1 || allFds.userData[userNbr].op)
		{
			std::cout << "he is op!!!\n";
			msg += "@" + chan.userList[i]->nickname + " ";
		}
		else if (find_client_list(chan.verboseList, chan.userList[i]) != -1)
		{
			std::cout << "he is verbose???\n";
			msg += "+" + chan.userList[i]->nickname + " ";
		}
		else
			msg += chan.userList[i]->nickname + " ";
	}
	msg += "\r\n";
	std::cout << "name msg= " << msg;
	cmd_reply(allFds, fd, msg);
	msg = "366 " + allFds.userData[userNbr].nickname + " " + chan.name + " :End of /NAMES list\r\n";
	cmd_reply(allFds, fd, msg);
}

void	names_loop(fdList &allFds, std::vector<std::string> splitBuff, int userNbr)
{
	std::vector<std::string>	splitChan;
	int pos;
	
	split(splitBuff[1], ',', splitChan);
	for (size_t i = 0; i < splitChan.size(); i++)
	{
		pos = find_channel(allFds, splitChan[i]);
		if (pos != -1)
		{
			if ((!allFds.channelList[pos].mode.p && !allFds.channelList[pos].mode.s) 
					|| is_joined(allFds, allFds.channelList[pos].name, userNbr) || allFds.userData[userNbr].op)
				names_reply(allFds, allFds.channelList[pos], allFds.userData[userNbr].fd, userNbr);
			return;
		}
	}
	


}

void	NAMES(std::string buffer, fdList &allFds, int userNbr)
{
	std::vector<std::string> splitBuff;
	
	if (!allFds.userData[userNbr].registered) 
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "451 " + allFds.userData[userNbr].nickname + " NAMES :You have not registered\r\n");
		return ;
	}
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() == 1 || splitBuff[1] == "0")
	{
		for (size_t i = 0; i < allFds.channelList.size(); i++)
		{
			if ((!allFds.channelList[i].mode.p && !allFds.channelList[i].mode.s) 
				|| is_joined(allFds, allFds.channelList[i].name, userNbr) || allFds.userData[userNbr].op)
				names_reply(allFds, allFds.channelList[i], allFds.userData[userNbr].fd, userNbr);
		}
		return ;
	}
	else
		names_loop(allFds, splitBuff, userNbr);
	return ;
}
