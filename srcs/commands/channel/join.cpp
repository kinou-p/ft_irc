/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:40:33 by apommier          #+#    #+#             */
/*   Updated: 2023/03/14 02:13:25 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

int chan_check(fdList &allFds, int userNbr, int chanNbr, std::vector<std::string> splitBuff)
{
	std::string errorStr;
	if (find_client_list(allFds.channelList[chanNbr].banList, &allFds.userData[userNbr]) != -1)
	{
		errorStr = "474 " + allFds.userData[userNbr].nickname + " JOIN " + allFds.channelList[chanNbr].name + " :Cannot join channel (+b)\r\n";
		cmd_error(allFds, allFds.userData[userNbr].fd, errorStr); //ERR_INVITEONLYCHAN
		return (0);
	}
	else if (allFds.channelList[chanNbr].mode.i && find_client_list(allFds.channelList[chanNbr].invitedList, &allFds.userData[userNbr]) == -1)
	{
		errorStr = "461 " + allFds.userData[userNbr].nickname + " JOIN " + allFds.channelList[chanNbr].name + " :Cannot join channel (+i)\r\n";
		cmd_error(allFds, allFds.userData[userNbr].fd, errorStr); //ERR_INVITEONLYCHAN
		return (0);
	}
	if (allFds.channelList[chanNbr].mode.k)
	{
		if (splitBuff.size() < 3 || allFds.channelList[chanNbr].password != splitBuff[2])
		{
			errorStr = "475 " + allFds.userData[userNbr].nickname + " JOIN " + allFds.channelList[chanNbr].name + " :Cannot join channel (+k)\r\n";
			cmd_error(allFds, allFds.userData[userNbr].fd, errorStr); //ERR_BADCHANNELKEY
		}
		return (0);
	}
	if (allFds.channelList[chanNbr].mode.l && allFds.channelList[chanNbr].userList.size() >= (size_t)allFds.channelList[chanNbr].maxUser)
	{
		errorStr = "471 " + allFds.userData[userNbr].nickname + " JOIN " + allFds.channelList[chanNbr].name + " :Cannot join channel (+l)\r\n";
		cmd_error(allFds, allFds.userData[userNbr].fd, errorStr); //ERR_CHANNELISFULL
		return (0);
	}
	return (1);
}


void join_or_create(std::string buffer, fdList &allFds, int userNbr)
{
	int chanNbr;
	int invitedUser;
	channelData joined_chan;
	std::vector<std::string> splitBuff;

	split(buffer, ' ', splitBuff);
	chanNbr = find_channel(allFds, splitBuff[1]);
	if (chanNbr != -1) //chan already exist
	{
		if (!chan_check(allFds, userNbr, chanNbr, splitBuff))
			return ;
		allFds.userData[userNbr].joinedChan.push_back(&allFds.channelList[chanNbr]); //add chan in user data
		allFds.channelList[chanNbr].userList.push_back(&allFds.userData[userNbr]);//add user in chan data
		joined_chan = *(allFds.userData[userNbr].joinedChan.back());
		if ((invitedUser = find_client_list(allFds.channelList[chanNbr].invitedList, &allFds.userData[userNbr])) != -1)
			allFds.channelList[chanNbr].invitedList.erase(allFds.channelList[chanNbr].invitedList.begin() + invitedUser);
	}
	else //chan doesn't exist yet
	{
		channelData tmp_chan;
		allFds.channelList.push_back(tmp_chan);
		channelData &new_chan = allFds.channelList[allFds.channelList.size() - 1];
		if (splitBuff[1][0] != '#' && splitBuff[1][0] != '&')
			cmd_error(allFds, allFds.userData[userNbr].fd, "476 " + allFds.userData[userNbr].nickname + " " + splitBuff[1] + " :Bad Channel Mask\r\n");
		new_chan.name = splitBuff[1];
		new_chan.opList.push_back(&allFds.userData[userNbr]);
		new_chan.userList.push_back(&allFds.userData[userNbr]);
		allFds.userData[userNbr].joinedChan.push_back(&allFds.channelList.back());//add chan in user data
		joined_chan = allFds.channelList[allFds.channelList.size() - 1];
	}
	std::string fullMsg;
	fullMsg = ":" + allFds.userData[userNbr].nickname + "!" + allFds.userData[userNbr].userName + "@" + allFds.userData[userNbr].ip + " JOIN :" + joined_chan.name + "\r\n";
	for (size_t i = 0; i < joined_chan.userList.size(); i++)
		send(joined_chan.userList[i]->fd, fullMsg.c_str(), fullMsg.size(), 0);
	std::cout << "size uselist=" << joined_chan.userList.size() << std::endl;
	names_reply(allFds, joined_chan, allFds.userData[userNbr].fd, userNbr);
	if (chanNbr == -1)
		chanNbr = find_channel(allFds, splitBuff[1]);
	if (!allFds.channelList[chanNbr].topic.empty())
		cmd_reply(allFds, allFds.userData[userNbr].fd, "332 TOPIC " + allFds.channelList[chanNbr].name + " :" + allFds.channelList[chanNbr].topic + "\r\n");
}




void join_loop(fdList &allFds, std::vector<std::string> splitBuff, int userNbr)
{
	std::vector<std::string>	splitChan;
	std::vector<std::string>	splitPwd;
	std::string					buffer;
	
	split(splitBuff[1], ',', splitChan);
	split(splitBuff[1], ',', splitPwd);
	for (size_t i = 0; i < splitChan.size(); i++)
	{
		if (splitChan[i][0] != '#' && splitChan[i][0] != '&')
		{
			buffer = "476 " + allFds.userData[userNbr].nickname + " JOIN " + splitChan[i] + " :Bad Channel Mask\r\n";
			cmd_error(allFds, allFds.userData[userNbr].fd, buffer);
			return ;
		}
		if (i < splitPwd.size())
			buffer = "JOIN " + splitChan[i] + " " + splitPwd[i];
		else
			buffer = "JOIN " + splitChan[i];
		join_or_create(buffer, allFds, userNbr);
	}
}




void JOIN(std::string buffer, fdList &allFds, int userNbr)
{
	std::vector<std::string> splitBuff;
	std::string msg;

	std::cout << "userNbr= " << userNbr << std::endl;
	if (!allFds.userData[userNbr].registered) 
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "451 " + allFds.userData[userNbr].nickname + " JOIN :You have not registered\r\n");
		return ;
	}
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() < 2) 
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "461 " + allFds.userData[userNbr].nickname + " JOIN :Not enough parameters\r\n"); //ERR_NEEDMOREPARAMS
		return ;
	}
	join_loop(allFds, splitBuff, userNbr);
}