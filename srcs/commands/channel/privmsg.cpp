/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 08:53:03 by apommier          #+#    #+#             */
/*   Updated: 2023/02/13 20:28:11 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"


void PRIVMSG(std::string buffer, fdList &allFds, int userNbr)
{
	std::vector<std::string> splitBuff;
	std::string msg;
	
	std::cout << "privmsg bufer= --" << buffer << std::endl;
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() < 3)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "431 * PRIVMSG :Not enought argument\n");
		//write(allFds.userData[user].fd, "ERR_NEEDMOREPARAMS", 18);
		return ;
	}
	
	// for (size_t i = 2; i < splitBuff.size(); i++)
	// {
	// 	msg += (" " + splitBuff[i]);
	// }
	//msg = buffer.substr(buffer.find(':') + 1, std::string::npos);
	std::cout << "privmsg =" << msg << std::endl;

	std::vector<std::string> dest;
	split(splitBuff[1], ',', dest);
	for (size_t i = 0; i < dest.size(); i++)
	{
		// std::cout << "dest[i] =" << dest[i] << "|" << std::endl;
		// std::cout << "dest[i] =" << dest[i] << "|" << std::endl;
		// std::cout << "dest[i] =" << dest[i] << "|" << std::endl;
		// std::cout << "chan =" << allFds.channelList[0].name << "|" << std::endl;
		// std::cout << "chan =" << allFds.channelList[0].name << "|" << std::endl;
		// std::cout << "chan =" << allFds.channelList[0].name << "|" << std::endl;
		// std::cout << "result =" << (allFds.channelList[0].name == dest[i]) << "|" << std::endl;
		send_msg(allFds, buffer, dest[i], userNbr);
	}
}

void send_msg(fdList &allFds, std::string msg, std::string dest, int userNbr)
{
	int pos;
	//find dest
	std::string fullMsg;
	//fullMsg = "*" + allFds.userData[userNbr].nickname + "* " + msg;
	pos = find_channel(allFds, dest); //return channel nbr
	if (pos != -1)
	{	
		//std::vector<clientData *>::iterator start = allFds.channelList[fd].userList.begin();
		//std::vector<clientData *>::iterator pastEnd = allFds.channelList[fd].userList.end();
		// while (start != pastEnd)
		// {
		// 	std::cout << "send nickname" << (*start)->nickname << std::endl;
		// 	ft_putstr_fd((*start)->fd, fullMsg);
		// 	start++;
		// 	std::cout << "loop here\n";
		// }
		for (size_t i = 0; i < allFds.channelList[pos].userList.size(); i++)
		{
			std::cout << "send nickname " << allFds.channelList[pos].userList[i]->nickname << std::endl;
			//ft_putstr_fd(allFds.channelList[fd].userList[i]->fd, fullMsg);
			fullMsg = ":" + allFds.userData[userNbr].nickname + "!" + allFds.userData[userNbr].userName + "@172.17.0.1 " + msg + "\n";
			//:kinou2!kinou@172.17.0.1 PRIVMSG #test :cc
			//send(allFds.channelList[pos].userList[i]->fd, fullMsg.c_str(), fullMsg.size(), 0);
			send(allFds.channelList[pos].userList[i]->fd, fullMsg.c_str(), fullMsg.size(), 0);
			std::cout << "loop here\n";
		}
		return ;
	}
	
	pos = find_user(allFds, dest); //return direct user fd
	if (pos != -1)
	{
		ft_putstr_fd(pos, fullMsg);
		return ;
	}
	std::cout << "error msg\n";
	//ft_putstr_fd(fd, msg);
}