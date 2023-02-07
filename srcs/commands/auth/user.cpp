/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:40:39 by apommier          #+#    #+#             */
/*   Updated: 2023/02/07 20:27:12 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

//Commande: USER
//Paramètres: <nom d'utilisateur> <hôte> <nom de serveur> :<nom réel>
//ERR_NEEDMOREPARAMS	ERR_ALREADYREGISTRED

void USER(std::string buffer, fdList allFds, int user)
{
	std::string realName = buffer.substr(buffer.find_first_of(":") + 1 , buffer.npos);
	std::vector<std::string> splitBuff;
	
	buffer.resize(buffer.size() - realName.size());
	std::cout << "Buffer in user = ---" << buffer << "---" << std::endl;
	std::cout << "realname in user = ---" << realName << "---" << std::endl;
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() < 4)
	{
		cmd_error(allFds, user, "461 * PASS :Not enough parameters");
		//write(allFds.userData[user].fd, "ERR_NEEDMOREPARAMS", 18);
		return ;
	}
	allFds.userData[user].userName = splitBuff[1];
	allFds.userData[user].hostName = splitBuff[2];
	allFds.userData[user].serverName = splitBuff[3];
	
	allFds.userData[user].realName = realName;
	
}