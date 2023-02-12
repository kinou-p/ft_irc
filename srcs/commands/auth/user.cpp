/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:40:39 by apommier          #+#    #+#             */
/*   Updated: 2023/02/12 16:26:48 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

//Commande: USER
//Paramètres: <nom d'utilisateur> <hôte> <nom de serveur> :<nom réel>
//ERR_NEEDMOREPARAMS	ERR_ALREADYREGISTRED



struct modeChan
{
	bool o;
	bool p;
	bool s; 
	bool i; 
	bool t; 
	bool n; 
	bool m;
	bool l; 
	bool b; 
	bool v; 
	bool k; 
};

struct modeUser
{
	bool i;
	bool s;
	bool w; 
	bool o; 
};



void USER(std::string buffer, fdList &allFds, int userNbr)
{
	if (allFds.userData[userNbr].registered == 1)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "462 * USER :You may not reregister\n");
		return ;
	}
	
	std::string realName = buffer.substr(buffer.find_first_of(":") + 1 , buffer.npos);
	std::vector<std::string> splitBuff;
	
	
	buffer.resize(buffer.size() - realName.size());
	std::cout << "Buffer in userNbr = ---" << buffer << "---" << std::endl;
	std::cout << "realname in userNbr = ---" << realName << "---" << std::endl;
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() < 4)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "461 * USER :Not enough parameters\n");
		//write(allFds.userData[userNbr].fd, "ERR_NEEDMOREPARAMS", 18);
		return ;
	}
	allFds.userData[userNbr].userName = splitBuff[1];
	allFds.userData[userNbr].hostName = splitBuff[2];
	allFds.userData[userNbr].serverName = splitBuff[3];
	
	allFds.userData[userNbr].realName = realName;
	if (!allFds.userData[userNbr].nickname.empty())
	{
		allFds.userData[userNbr].registered = 1;
		print_registered_msg(allFds, userNbr);
	}
}