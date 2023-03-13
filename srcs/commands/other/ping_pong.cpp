/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_pong.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 00:16:27 by apommier          #+#    #+#             */
/*   Updated: 2023/03/13 16:37:45 by apommier         ###   ########.fr       */
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
	msg = ":irc.local PONG irc.local :irc.local\r\n";
	send(allFds.userData[userNbr].fd, msg.c_str(), msg.size(), 0);
	
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
	msg = ":irc.local PONG irc.local :" + splitBuff[1] + "\r\n";
	send(allFds.userData[userNbr].fd, msg.c_str(), msg.size(), 0);
	return ;
}