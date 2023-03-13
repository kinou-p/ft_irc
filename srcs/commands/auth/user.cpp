/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:40:39 by apommier          #+#    #+#             */
/*   Updated: 2023/03/13 16:29:05 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

//Commande: USER
//Paramètres: <nom d'utilisateur> <hôte> <nom de serveur> :<nom réel>
//ERR_NEEDMOREPARAMS	ERR_ALREADYREGISTRED


void USER(std::string buffer, fdList &allFds, int userNbr)
{
	if (allFds.userData[userNbr].registered == 1)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "462 " + allFds.userData[userNbr].nickname + " USER :You may not reregister\r\n");
		return ;
	}
	std::string realName = buffer.substr(buffer.find_first_of(":") + 1 , buffer.npos);
	std::vector<std::string> splitBuff;
	buffer.resize(buffer.size() - realName.size());
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() < 4)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "461 " + allFds.userData[userNbr].nickname + "USER :Not enough parameters\r\n");
		return ;
	}
	allFds.userData[userNbr].userName = splitBuff[1];
	allFds.userData[userNbr].hostName = splitBuff[2];
	allFds.userData[userNbr].serverName = splitBuff[3];
	
	allFds.userData[userNbr].realName = realName;
	if (!allFds.userData[userNbr].nickname.empty())
		connect_client(allFds, userNbr);
}