/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_pong.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 00:16:27 by apommier          #+#    #+#             */
/*   Updated: 2023/02/14 00:11:54 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"


// void ft_putstr_fd(int fd, std::string str)
// {
// 	write(fd, str.c_str(), str.size());
// 	write(fd, "\n", 1);
// }

void	PONG(std::string buffer, fdList &allFds, int userNbr)
{
	(void)buffer; 
	(void)allFds;
	(void)userNbr;

	std::string msg;
	std::vector<std::string> splitBuff;
	split(buffer, ' ', splitBuff);
	msg = ":irc.local PONG irc.local :irc.local";
	// ":irc.local PONG irc.local :irc.local"
	send(allFds.userData[userNbr].fd, msg.c_str(), msg.size(), 0);
	// if (splitBuff.size() < 2)
	// {
	// 	cmd_error(allFds, allFds.userData[userNbr].fd, "431 * NICK :No nickname given\n");
	// 	//write(allFds.userData[user].fd, "ERR_NEEDMOREPARAMS", 18);
	// 	return ;
	// }
	
	return ;
}

void	PING(std::string buffer, fdList &allFds, int userNbr)
{
	(void)buffer; 
	(void)allFds;
	(void)userNbr;

	
	std::string msg;
	std::vector<std::string> splitBuff;
	split(buffer, ' ', splitBuff);
	msg = ":irc.local PONG irc.local :" + splitBuff[1] + "\n";
	//msg = "PONG irc.local " + splitBuff[1];
	send(allFds.userData[userNbr].fd, msg.c_str(), msg.size(), 0);
	std::cout << "pong send\n";
	std::cout << "/r = " << (int)'\r' << "\n";
	std::cout << "/n = " << (int)'\n' << "\n";
	std::cout << "msg=" << msg << "\n";
	// if (splitBuff.size() < 2)
	// {
	// 	cmd_error(allFds, allFds.userData[userNbr].fd, "431 * NICK :No nickname given\n");
	// 	//write(allFds.userData[user].fd, "ERR_NEEDMOREPARAMS", 18);
	// 	return ;
	// }

	return ;
}