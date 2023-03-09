/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 21:24:55 by apommier          #+#    #+#             */
/*   Updated: 2023/03/09 05:18:13 by apommier         ###   ########.fr       */
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

void send_notice_msg(fdList &allFds, std::string msg, std::string dest, int userNbr)
{
	int pos;
	std::string fullMsg;

	fullMsg = ":" + allFds.userData[userNbr].nickname + "!" + allFds.userData[userNbr].userName + "@172.17.0.1 " + msg + "\n";
	if (dest[0] == '&' || dest[0] == '#')
	{	
		if (is_joined(allFds, dest, userNbr) == -1)
			return ;
		if ((pos = find_channel(allFds, dest)) == -1)
			return ;
		for (size_t i = 0; i < allFds.channelList[pos].userList.size(); i++)
		{
			//std::cout << "send nickname " << allFds.channelList[pos].userList[i]->nickname << std::endl;
			if (i != (size_t)userNbr)
				send(allFds.channelList[pos].userList[i]->fd, fullMsg.c_str(), fullMsg.size(), 0);
			//std::cout << "loop here\n";
		}
		return ;
	}
	pos = find_user(allFds, dest); //return direct user fd
	if (pos != -1)
	{
		send(allFds.userData[pos].fd, fullMsg.c_str(), fullMsg.size(), 0);
		return ;
	}
}

void NOTICE(std::string buffer, fdList &allFds, int userNbr)
{
	std::vector<std::string> splitBuff;
	std::string msg;
	
	//std::cout << "notice bufer= --" << buffer << std::endl;
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() < 2)
		return ;
	if (splitBuff.size() < 3)
		return ;

	std::cout << "notice =" << msg << std::endl;
	std::vector<std::string> dest;
	split(splitBuff[1], ',', dest);
	for (size_t i = 0; i < dest.size(); i++)
		send_notice_msg(allFds, buffer, dest[i], userNbr);
}

