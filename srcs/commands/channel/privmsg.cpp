/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 08:53:03 by apommier          #+#    #+#             */
/*   Updated: 2023/03/10 22:11:34 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

// Commande: PRIVMSG
// Paramètres: <destinataire>{,<destinataire>} <texte à envoyer >
//    ERR_NORECIPIENT                 ERR_NOTEXTTOSEND +
//    ERR_CANNOTSENDTOCHAN            ERR_NOTOPLEVEL 
//    ERR_WILDTOPLEVEL                ERR_TOOMANYTARGETS
//    ERR_NOSUCHNICK +
//    RPL_AWAY

void PRIVMSG(std::string buffer, fdList &allFds, int userNbr)
{
	std::vector<std::string> splitBuff;
	std::string msg;
	
	if (!allFds.userData[userNbr].registered) 
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "451 " + allFds.userData[userNbr].nickname + " PRIVMSG :You have not registered\r\n");
		return ;
	}
	//std::cout << "privmsg bufer= --" << buffer << std::endl;
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() < 2)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "431 " + allFds.userData[userNbr].nickname + " PRIVMSG :Not enought argument\r\n");
		return ;
	}
	if (splitBuff.size() < 3)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "412 " + allFds.userData[userNbr].nickname + " PRIVMSG :No text to send\r\n");
		return ;
	}
	//std::cout << "privmsg =" << msg << std::endl;
	std::vector<std::string> dest;
	split(splitBuff[1], ',', dest);
	for (size_t i = 0; i < dest.size(); i++)
		send_msg(allFds, buffer, dest[i], userNbr);
}

void send_msg(fdList &allFds, std::string msg, std::string dest, int userNbr)
{
	int pos;
	std::string fullMsg;

	fullMsg = ":" + allFds.userData[userNbr].nickname + "!" + allFds.userData[userNbr].userName + "@172.17.0.1 " + msg + "\r\n";
	if (dest[0] == '&' || dest[0] == '#')
	{	
		pos = find_channel(allFds, dest);
		if (pos == -1)
		{	
			cmd_error(allFds, allFds.userData[userNbr].fd, "401 " + allFds.userData[userNbr].nickname + " PRIVMSG " + dest + " :No such channel\r\n");
			return ;
		}
		if (allFds.channelList[pos].mode.n && is_joined(allFds, dest, userNbr) == -1  )
		{	
			cmd_error(allFds, allFds.userData[userNbr].fd, "442 " + allFds.userData[userNbr].nickname + " PRIVMSG " + dest + " :You're not on that channel\r\n");
			return ;
		}
		// if (find_client_list(allFds.channelList[pos].verboseList, &allFds.userData[userNbr]) != -1)
		// {
		// 	allFds.channelList[pos].verboseList.erase();
		// }
		if (allFds.channelList[pos].mode.m && !allFds.userData[userNbr].op 
			&& !is_chan_op(allFds, &allFds.channelList[pos], userNbr) 
			&& find_client_list(allFds.channelList[pos].verboseList, &allFds.userData[userNbr]) == -1)
		{
			cmd_error(allFds, allFds.userData[userNbr].fd, "404 " + allFds.userData[userNbr].nickname + " PRIVMSG " + dest + " :Cannot send to channel\r\n");
			return ;
		}
		for (size_t i = 0; i < allFds.channelList[pos].userList.size(); i++)
		{
			//std::cout << "send nickname " << allFds.channelList[pos].userList[i]->nickname << std::endl;
			
			if (&allFds.userData[userNbr] != allFds.channelList[pos].userList[i] && allFds.channelList[pos].userList[i]->mode.s)
			{
				//std::cout << "send msg to user nbr" << i << std::endl;
				send(allFds.channelList[pos].userList[i]->fd, fullMsg.c_str(), fullMsg.size(), 0);
			}
			//std::cout << "loop here\n";
		}
		return ;
	}
	pos = find_user(allFds, dest); //return direct user fd
	//std::cout << "pos of user = " << pos << std::endl;
	if (pos == -1)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "401 " + allFds.userData[userNbr].nickname + " PRIVMSG " + dest + " :No such nick\r\n");
		return ;
	}
	if (allFds.userData[pos].mode.s)
		send(allFds.userData[pos].fd, fullMsg.c_str(), fullMsg.size(), 0);
	//std::cout << "msg send\n";
	//std::cout << "msg = " << fullMsg << std::endl;
}