/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:14:17 by apommier          #+#    #+#             */
/*   Updated: 2023/02/23 17:49:05 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

//void	who_reply(fdList &allFds, int userNbr, int fd)
void	who_reply(fdList &allFds, clientData &user, int fd)
{
	// std::string msg;
	// //:<server> 352 <channel> <username> <hostname> <server> <nick> H :0 <realname>
	// //if (chan.size())
	// msg = "352 " /*+ chan + " " */
	// + allFds.userData[userNbr].userName + " " 
	// + allFds.userData[userNbr].hostName + " irc.local " 
	// +  allFds.userData[userNbr].nickname + " :0 " 
	// + allFds.userData[userNbr].realName + "\n";

	// cmd_reply(allFds, fd, msg);


	std::string msg;
	//:<server> 352 <channel> <username> <hostname> <server> <nick> H :0 <realname>
	//if (chan.size())
	msg = "352 " /*+ chan + " " */
	+ user.userName + " " 
	+ user.hostName + " irc.local " 
	+ user.nickname + " :0 " 
	+ user.realName + "\n";
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
		cmd_error(allFds, allFds.userData[userNbr].fd, "451 * WHO :You have not registered\n");
		return ;
	}
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() == 1 || splitBuff[1] == "0")
	{
		for (int i = 0; i < allFds.nbrUser; i++)
		{
			if (!allFds.userData[i].mode.i || is_in_same(allFds, userNbr, i))
			{
				who_reply(allFds, allFds.userData[i], allFds.userData[userNbr].fd);
				//print who
			}
		}
		return ;
	}
	if ((pos = find_channel(allFds, splitBuff[1])) == -1)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "401 * " + splitBuff[1] + " :No such nick/channel\n");
		return ;
	}
	for (int i = 0; i < allFds.channelList[pos].nbrUser; i++)
	{
		who_reply(allFds, *allFds.channelList[pos].userList[i], allFds.userData[userNbr].fd);
	}
	//"<nick> :End of WHOIS list"
	cmd_reply(allFds, allFds.userData[userNbr].fd, allFds.userData[userNbr].nickname + " :End of WHOIS list\n");
		//std::cout << 
	return ;
}