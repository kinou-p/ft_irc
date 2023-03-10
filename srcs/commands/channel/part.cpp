/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:10:07 by apommier          #+#    #+#             */
/*   Updated: 2023/03/10 21:20:26 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

void leave_chan(fdList &allFds, std::string chan, int userNbr, std::string msg)
{
	int chanPos;
	std::string reply;
	
	if ((chanPos = find_channel(allFds, chan)) == -1)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "401 " + allFds.userData[userNbr].nickname + " PART " + chan + " :No such channel\n");
		return ;
	}
	if (is_joined(allFds, chan, userNbr) == -1)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "422 " + allFds.userData[userNbr].nickname + " " + chan + " :You're not on that channel\n");
		return ;
	}
	//del_user_in_chan(&allFds.userData[userNbr], &allFds.channelList[chanPos]);
	int pos = find_client_list(allFds.channelList[chanPos].userList, &allFds.userData[userNbr]);
	allFds.channelList[chanPos].userList.erase(allFds.channelList[chanPos].userList.begin() + pos);
	//allFds.channelList[chanPos].size()--;
	del_chan_in_user(&allFds.userData[userNbr], &allFds.channelList[chanPos]);
	//:WiZ!jto@tolsun.oulu.fi PART #playzone :I lost
	//:awd!kinou@kinou PART #test
	//reply = ":" + allFds.userData[userNbr].nickname + "!" + 
	
	//reply = ":" + allFds.userData[userNbr].nickname + "!" + allFds.userData[userNbr].userName + "@" + allFds.userData[userNbr].ip + " PART " + allFds.channelList[chanPos].name;
	//reply = ":" + allFds.userData[userNbr].nickname + "!" + allFds.userData[userNbr].userName + "@" + allFds.userData[userNbr].ip + " PART :" + allFds.channelList[chanPos].name + "\n";
	reply = ":" + allFds.userData[userNbr].nickname + "!" + allFds.userData[userNbr].userName + "@" + allFds.userData[userNbr].ip;
	if (!msg.empty())
		reply += " PART " + allFds.channelList[chanPos].name + " " + msg + "\n";
	else
		reply += " PART :" + allFds.channelList[chanPos].name + "\n";

	//:awd!kinou@172.17.0.1 PART :#test tcpdump
	//:awd!kinou@127.0.0.1 PART :#test
	//(void )msg;
	//	reply += " " + msg;
	//else
	//	reply += "\n";
	//std::cout << "leave msg=" << reply << std::endl;
	send(allFds.userData[userNbr].fd, reply.c_str(), reply.size(), 0);
	//allFds.channelList[chanPos].size()--;
	for (size_t i = 0; i < allFds.channelList[chanPos].userList.size(); i++)
	{
		if (allFds.channelList[chanPos].userList[i]->mode.s)
			send(allFds.channelList[chanPos].userList[i]->fd, reply.c_str(), reply.size(), 0);
		//std::cout << "loop here\n";
	}
	
	//cmd_reply(allFds, allFds.userData[userNbr].fd, reply + "\n");
}

void	PART(std::string buffer, fdList &allFds, int userNbr)
{
	std::vector<std::string> splitBuff;
	std::vector<std::string> splitChan;
	std::string msg;
	
	if (!allFds.userData[userNbr].registered) 
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "451 " + allFds.userData[userNbr].nickname + " PART :You have not registered\n");
		return ;
	}
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() < 2)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "431 " + allFds.userData[userNbr].nickname + " PART :Not enought argument\n");
		return ;
	}
	split(splitBuff[1], ',', splitChan);
	if (splitBuff.size() > 2)
		msg = buffer.substr(splitBuff[0].size() + splitBuff[1].size() + 2, std::string::npos);
	for (size_t i = 0; i < splitChan.size(); i++)
		leave_chan(allFds, splitChan[i], userNbr, msg);
	return ;
}
