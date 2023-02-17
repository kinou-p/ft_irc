/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 08:53:03 by apommier          #+#    #+#             */
/*   Updated: 2023/02/16 23:20:25 by apommier         ###   ########.fr       */
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
	
	std::cout << "privmsg bufer= --" << buffer << std::endl;
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() < 2)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "431 * PRIVMSG :Not enought argument\n");
		return ;
	}
	if (splitBuff.size() < 3)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "412 * PRIVMSG :No text to send\n");
		return ;
	}
	std::cout << "privmsg =" << msg << std::endl;
	std::vector<std::string> dest;
	split(splitBuff[1], ',', dest);
	for (size_t i = 0; i < dest.size(); i++)
		send_msg(allFds, buffer, dest[i], userNbr);
}

void send_msg(fdList &allFds, std::string msg, std::string dest, int userNbr)
{
	int pos;
	std::string fullMsg;

	fullMsg = ":" + allFds.userData[userNbr].nickname + "!" + allFds.userData[userNbr].userName + "@172.17.0.1 " + msg + "\n";
	if (dest[0] == '&' || dest[0] == '#')
	{	
		if (is_joined(allFds, dest, userNbr) == -1)
		{	
			cmd_error(allFds, allFds.userData[userNbr].fd, "442 * PRIVMSG " + dest + " :You're not on that channel\n");
			return ;
		}
		if ((pos = find_channel(allFds, dest)) == -1)
		{	
			cmd_error(allFds, allFds.userData[userNbr].fd, "401 * PRIVMSG " + dest + " :No such nick/channel\n");
			return ;
		}
		// if (allFds.channelList[pos].mode.m && !allFds.userData[userNbr].op && !is_chan_op(allFds, &allFds.channelList[pos], userNbr) && !allFds.channelList[pos].userMode[nbr].v)
		// {	
		// 	cmd_error(allFds, allFds.userData[userNbr].fd, "404 * PRIVMSG " + dest + " :Cannot send to channel\n");
		// 	return ;
		// }
		for (size_t i = 0; i < allFds.channelList[pos].userList.size(); i++)
		{
			std::cout << "send nickname " << allFds.channelList[pos].userList[i]->nickname << std::endl;
			if (i != (size_t)userNbr)
				send(allFds.channelList[pos].userList[i]->fd, fullMsg.c_str(), fullMsg.size(), 0);
			std::cout << "loop here\n";
		}
		return ;
	}
	pos = find_user(allFds, dest); //return direct user fd
	if (pos != -1)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "401 * PRIVMSG " + dest + " :No such nick/channel\n");
		return ;
	}
	send(allFds.userData[pos].fd, fullMsg.c_str(), fullMsg.size(), 0);
}