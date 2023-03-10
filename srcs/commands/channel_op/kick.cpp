/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:19:32 by apommier          #+#    #+#             */
/*   Updated: 2023/03/10 21:21:43 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

//Paramètres: <canal> <utilisateur> [<commentaire>]

void	KICK(std::string buffer, fdList &allFds, int userNbr)
{
	std::vector<std::string>	splitBuff;
	std::string					msg;
	std::string					kickMsg;
	int							chanPos;
	int							userPos;
	channelData					chan;

	if (!allFds.userData[userNbr].registered) 
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "451 " + allFds.userData[userNbr].nickname + " KICK :You have not registered\n");
		return ;
	}
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() < 3)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "431 " + allFds.userData[userNbr].nickname + " KICK :Not enought argument\n");
		return ;
	}

	if ((chanPos = find_channel(allFds, splitBuff[1])) == -1)
	{	
		cmd_error(allFds, allFds.userData[userNbr].fd, "401 " + allFds.userData[userNbr].nickname + " KICK " + splitBuff[1] + " :No such channel\n");
		return ;
	}
	if (!allFds.userData[userNbr].op && is_joined(allFds, splitBuff[1], userNbr) == -1)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "422 " + allFds.userData[userNbr].nickname + " " + splitBuff[1] + " :You're not on that channel\n");
		return ;
	}

	if ((find_user(allFds, splitBuff[2])) == -1)
	{	
		cmd_error(allFds, allFds.userData[userNbr].fd, "401 " + allFds.userData[userNbr].nickname + " KICK " + splitBuff[1] + " :No such nick\n");
		return ;
	}
	
	if (chanPos != -1)
	{
		chan = allFds.channelList[chanPos];
		if (!is_chan_op(allFds, &chan, userNbr) && !allFds.userData[userNbr].op)
		{
			cmd_error(allFds, allFds.userData[userNbr].fd, "482 " + allFds.userData[userNbr].nickname + " " + splitBuff[1] + " :You're not channel operator\n");
			return ;
		}
	}
	msg = ":" + allFds.userData[userNbr].nickname + " KICK " + chan.name + " " + splitBuff[2];
	if (splitBuff.size() > 3)
		msg += ": " + buffer.substr(splitBuff[0].size() + splitBuff[1].size() + splitBuff[2].size() + 1, std::string::npos);
	if ((userPos = find_user(allFds, splitBuff[2])) == -1)
	{
		return ;
	}
	kickMsg = allFds.userData[userPos].nickname + " have been kicked by " + allFds.userData[userNbr].nickname + "\n";
	PART("PART " + splitBuff[1] + " has been kicked by " + allFds.userData[userNbr].nickname, allFds, userPos);
	//del_user_in_chan(&allFds.userData[userPos], &allFds.channelList[chanPos]);
	//del_chan_in_user(&allFds.userData[userPos], &allFds.channelList[chanPos]);
	std::cout << "kick msg---" << msg << "---" << std::endl;
	send(allFds.userData[userPos].fd, msg.c_str(), msg.size(), 0);
	//send_msg(allFds, msg, splitBuff[1], userNbr);
	for (size_t i = 0; i < allFds.channelList[chanPos].userList.size(); i++)
	{
		if (allFds.channelList[chanPos].userList[i]->mode.s)
			send(allFds.channelList[chanPos].userList[i]->fd, kickMsg.c_str(), kickMsg.size(), 0);
	}
	//cmd_reply(allFds, allFds.userData[userPos].fd, msg);
	
	// else if (!allFds.userData[userNbr].op)
	// {
	// 	cmd_error(allFds, allFds.userData[userNbr].fd, "482 " + allFds.userData[userNbr].nickname + " " + splitBuff[1] + " :You're not channel operator\n");
	// 	return ;
	// }
	return ;
}