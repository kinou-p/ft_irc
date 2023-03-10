/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:40:39 by apommier          #+#    #+#             */
/*   Updated: 2023/03/10 22:21:18 by apommier         ###   ########.fr       */
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
// " + allFds.userData[userNbr].nickname + " 
		cmd_error(allFds, allFds.userData[userNbr].fd, "462 " + allFds.userData[userNbr].nickname + " USER :You may not reregister\r\n");
		return ;
	}
	
	std::string realName = buffer.substr(buffer.find_first_of(":") + 1 , buffer.npos);
	std::vector<std::string> splitBuff;
	
	
	buffer.resize(buffer.size() - realName.size());
	//std::cout << "Buffer in userNbr = ---" << buffer << "---" << std::endl;
	//std::cout << "realname in userNbr = ---" << realName << "---" << std::endl;
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() < 4)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "461 " + allFds.userData[userNbr].nickname + "USER :Not enough parameters\r\n");
		//write(allFds.userData[userNbr].fd, "ERR_NEEDMOREPARAMS", 18);
		return ;
	}
	allFds.userData[userNbr].userName = splitBuff[1];
	allFds.userData[userNbr].hostName = splitBuff[2];
	allFds.userData[userNbr].serverName = splitBuff[3];
	
	allFds.userData[userNbr].realName = realName;
	if (!allFds.userData[userNbr].nickname.empty() /*&& !allFds.userData[userNbr].password.empty()*/)
	{
		connect_client(allFds, userNbr);
		// allFds.userData[userNbr].registered = 1;
		// print_registered_msg(allFds, userNbr);
	}
}