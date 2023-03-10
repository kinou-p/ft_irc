/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:19:52 by apommier          #+#    #+#             */
/*   Updated: 2023/03/10 21:04:49 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

void	TOPIC(std::string buffer, fdList &allFds, int userNbr)
{
	channelData chan;
	int chanNbr;
	std::vector<std::string> splitBuff;
	
	std::cout << "topic im here1\n";//RPL_NOTOPIC //RPL_TOPIC
	if (!allFds.userData[userNbr].registered) 
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "451 " + allFds.userData[userNbr].nickname + " TOPIC :You have not registered\n");
		return ;
	}
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() < 2)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "461 " + allFds.userData[userNbr].nickname + " TOPIC :Not enough parameters\n");
		return ;
	}
	if (is_joined(allFds, splitBuff[1], userNbr) == -1)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "422 " + allFds.userData[userNbr].nickname + " " + splitBuff[1] + " :You're not on that channel\n");
		return ;
	}
	if ((chanNbr = find_channel(allFds, splitBuff[1])) != -1)
	{
		chan = allFds.channelList[chanNbr];
		if (!is_chan_op(allFds, &chan, userNbr) && !allFds.userData[userNbr].op)
		{
			cmd_error(allFds, allFds.userData[userNbr].fd, "482 " + allFds.userData[userNbr].nickname + " " + splitBuff[1] + " :You're not channel operator\n");
			return ;
		}
	}
	// else if (!allFds.userData[userNbr].op && !allFds.userData[userNbr].op)
	// {
	// 	cmd_error(allFds, allFds.userData[userNbr].fd, "482 " + allFds.userData[userNbr].nickname + " " + splitBuff[1] + " :You're not channel operator\n");
	// 	return ;
	// }
	std::cout << "topic im here2\n";//RPL_NOTOPIC //RPL_TOPIC
	if (splitBuff.size() < 3)
	{
		if (!allFds.channelList[chanNbr].topic.empty())
			cmd_reply(allFds, allFds.userData[userNbr].fd, "332 TOPIC " + splitBuff[1] + " :" + allFds.channelList[chanNbr].topic + "\n");
		else
			cmd_error(allFds, allFds.userData[userNbr].fd, "331 TOPIC " + splitBuff[1] + " :No topic is set\n");
		return;
		//std::cout << "PRINT TOPIC here\n";//RPL_NOTOPIC //RPL_TOPIC
	}
	else
	{
		allFds.channelList[chanNbr].topic = buffer.substr(6 + splitBuff[1].size() + 2, std::string::npos);
		//std::cout << "topic= " << allFds.channelList[chanNbr].topic << std::endl;
		cmd_reply(allFds, allFds.userData[userNbr].fd, "332 TOPIC " + splitBuff[1] + " :" + allFds.channelList[chanNbr].topic + "\n");
		//std::cout << "PRINT TOPIC here topic set\n";//RPL_NOTOPIC //RPL_TOPIC
	}
	return ;
}