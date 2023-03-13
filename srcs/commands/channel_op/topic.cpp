/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:19:52 by apommier          #+#    #+#             */
/*   Updated: 2023/03/13 16:35:41 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

void	TOPIC(std::string buffer, fdList &allFds, int userNbr)
{
	channelData chan;
	int chanNbr;
	std::vector<std::string> splitBuff;
	
	if (!allFds.userData[userNbr].registered) 
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "451 " + allFds.userData[userNbr].nickname + " TOPIC :You have not registered\r\n");
		return ;
	}
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() < 2)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "461 " + allFds.userData[userNbr].nickname + " TOPIC :Not enough parameters\r\n");
		return ;
	}
	if (is_joined(allFds, splitBuff[1], userNbr) == -1)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "422 " + allFds.userData[userNbr].nickname + " " + splitBuff[1] + " :You're not on that channel\r\n");
		return ;
	}
	if ((chanNbr = find_channel(allFds, splitBuff[1])) != -1)
	{
		chan = allFds.channelList[chanNbr];
		if (!is_chan_op(allFds, &chan, userNbr) && !allFds.userData[userNbr].op)
		{
			cmd_error(allFds, allFds.userData[userNbr].fd, "482 " + allFds.userData[userNbr].nickname + " " + splitBuff[1] + " :You're not channel operator\r\n");
			return ;
		}
	}
	if (splitBuff.size() < 3)
	{
		if (!allFds.channelList[chanNbr].topic.empty())
			cmd_reply(allFds, allFds.userData[userNbr].fd, "332 TOPIC " + splitBuff[1] + " :" + allFds.channelList[chanNbr].topic + "\r\n");
		else
			cmd_error(allFds, allFds.userData[userNbr].fd, "331 TOPIC " + splitBuff[1] + " :No topic is set\r\n");
		return;
	}
	else
	{
		allFds.channelList[chanNbr].topic = buffer.substr(6 + splitBuff[1].size() + 2, std::string::npos);
		for (size_t i = 0; i < allFds.channelList[chanNbr].userList.size(); i++)
			cmd_reply(allFds, allFds.channelList[chanNbr].userList[i]->fd, "332 TOPIC " + splitBuff[1] + " :" + allFds.channelList[chanNbr].topic + "\r\n");
	}
	return ;
}