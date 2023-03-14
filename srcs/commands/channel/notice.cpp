/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 21:24:55 by apommier          #+#    #+#             */
/*   Updated: 2023/03/14 02:15:04 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

void send_notice_msg(fdList &allFds, std::string msg, std::string dest, int userNbr)
{
	int pos;
	std::string fullMsg;

	fullMsg = ":" + allFds.userData[userNbr].nickname + "!" + allFds.userData[userNbr].userName + "@172.17.0.1 " + msg + "\r\n";
	if (dest[0] == '&' || dest[0] == '#')
	{	
		pos = find_channel(allFds, dest);
		if (pos == -1)
			return ;
		if (allFds.channelList[pos].mode.n && is_joined(allFds, dest, userNbr) == -1  )
			return ;
		if (allFds.channelList[pos].mode.m && !allFds.userData[userNbr].op 
				&& !is_chan_op(allFds, &allFds.channelList[pos], userNbr) 
				&& find_client_list(allFds.channelList[pos].verboseList, &allFds.userData[userNbr]) == -1)
			return ;
		for (size_t i = 0; i < allFds.channelList[pos].userList.size(); i++)
		{			
			if (&allFds.userData[userNbr] != allFds.channelList[pos].userList[i] && allFds.channelList[pos].userList[i]->mode.s)
				send(allFds.channelList[pos].userList[i]->fd, fullMsg.c_str(), fullMsg.size(), 0);
		}
		return ;
	}
	pos = find_user(allFds, dest);
	if (pos == -1)
		return ;
	if (allFds.userData[pos].mode.s)
		send(allFds.userData[pos].fd, fullMsg.c_str(), fullMsg.size(), 0);
}

void NOTICE(std::string buffer, fdList &allFds, int userNbr)
{
	std::vector<std::string> splitBuff;
	std::string msg;
	
	if (!allFds.userData[userNbr].registered) 
		return ;
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() < 2)
		return ;
	if (splitBuff.size() < 3)
		return ;
	std::vector<std::string> dest;
	split(splitBuff[1], ',', dest);
	for (size_t i = 0; i < dest.size(); i++)
		send_notice_msg(allFds, buffer, dest[i], userNbr);
}