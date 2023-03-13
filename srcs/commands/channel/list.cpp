/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 00:50:51 by apommier          #+#    #+#             */
/*   Updated: 2023/03/13 16:31:44 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

void	list_reply(fdList &allFds, channelData &chan, int fd, int userNbr)
{
	//:irc.server.com 321 MonPseudo :Channel :Users Name          //start
	//:irc.server.com 322 MonPseudo #channel 10 :Channel Topic    //list
	//:irc.server.com 323 MonPseudo :End of LIST                  //end
	std::string msg;
	msg = "322 " + allFds.userData[userNbr].nickname + " :" + chan.name + " " + int_to_str(chan.userList.size()) + " :" + chan.topic + "\r\n";//"ChannelName UserNbr :Topic\r\n";
	cmd_reply(allFds, fd, msg);
}

void	list_loop(fdList &allFds, std::vector<std::string> splitBuff, int userNbr)
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
				list_reply(allFds, allFds.channelList[pos], allFds.userData[userNbr].fd, userNbr);
		}
	}
}

void	LIST(std::string buffer, fdList &allFds, int userNbr)
{
	std::vector<std::string> splitBuff;
	std::string msg;
	
	if (!allFds.userData[userNbr].registered) 
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "451 " + allFds.userData[userNbr].nickname + " LIST :You have not registered\r\n");
		return ;
	}
	split(buffer, ' ', splitBuff);
	msg = "321 " + allFds.userData[userNbr].nickname + " :ChannelName UserNbr :Topic\r\n";
	cmd_reply(allFds, allFds.userData[userNbr].fd, msg);
	if (splitBuff.size() == 1 || splitBuff[1] == "0")
	{
		for (size_t i = 0; i < allFds.channelList.size(); i++)
		{
			if ((!allFds.channelList[i].mode.p && !allFds.channelList[i].mode.s) 
					|| is_joined(allFds, allFds.channelList[i].name, userNbr) || allFds.userData[userNbr].op)
				list_reply(allFds, allFds.channelList[i], allFds.userData[userNbr].fd, userNbr);
		}
		return ;
	}
	else
		list_loop(allFds, splitBuff, userNbr);
	msg = "323 " + allFds.userData[userNbr].nickname + " :End of LIST\r\n";
	cmd_reply(allFds, allFds.userData[userNbr].fd, msg);
}