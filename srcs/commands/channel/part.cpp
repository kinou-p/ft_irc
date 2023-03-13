/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:10:07 by apommier          #+#    #+#             */
/*   Updated: 2023/03/13 16:32:06 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

void leave_chan(fdList &allFds, std::string chan, int userNbr, std::string msg)
{
	int chanPos;
	std::string reply;
	
	if ((chanPos = find_channel(allFds, chan)) == -1)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "401 " + allFds.userData[userNbr].nickname + " PART " + chan + " :No such channel\r\n");
		return ;
	}
	if (is_joined(allFds, chan, userNbr) == -1)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "422 " + allFds.userData[userNbr].nickname + " " + chan + " :You're not on that channel\r\n");
		return ;
	}
	int pos = find_client_list(allFds.channelList[chanPos].userList, &allFds.userData[userNbr]);
	allFds.channelList[chanPos].userList.erase(allFds.channelList[chanPos].userList.begin() + pos);
	del_chan_in_user(&allFds.userData[userNbr], &allFds.channelList[chanPos]);
	reply = ":" + allFds.userData[userNbr].nickname + "!" + allFds.userData[userNbr].userName + "@" + allFds.userData[userNbr].ip;
	if (!msg.empty())
		reply += " PART " + allFds.channelList[chanPos].name + " " + msg + "\r\n";
	else
		reply += " PART :" + allFds.channelList[chanPos].name + "\r\n";
	send(allFds.userData[userNbr].fd, reply.c_str(), reply.size(), 0);
	for (size_t i = 0; i < allFds.channelList[chanPos].userList.size(); i++)
	{
		if (allFds.channelList[chanPos].userList[i]->mode.s)
			send(allFds.channelList[chanPos].userList[i]->fd, reply.c_str(), reply.size(), 0);
	}
}

void	PART(std::string buffer, fdList &allFds, int userNbr)
{
	std::vector<std::string> splitBuff;
	std::vector<std::string> splitChan;
	std::string msg;
	
	if (!allFds.userData[userNbr].registered) 
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "451 " + allFds.userData[userNbr].nickname + " PART :You have not registered\r\n");
		return ;
	}
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() < 2)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "431 " + allFds.userData[userNbr].nickname + " PART :Not enought argument\r\n");
		return ;
	}
	split(splitBuff[1], ',', splitChan);
	if (splitBuff.size() > 2)
		msg = buffer.substr(splitBuff[0].size() + splitBuff[1].size() + 2, std::string::npos);
	for (size_t i = 0; i < splitChan.size(); i++)
		leave_chan(allFds, splitChan[i], userNbr, msg);
	return ;
}
