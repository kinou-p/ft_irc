/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 08:53:03 by apommier          #+#    #+#             */
/*   Updated: 2023/02/11 12:38:51 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"


void PRIVMSG(std::string buffer, fdList &allFds, int userNbr)
{
	std::vector<std::string> splitBuff;
	std::string msg;
	
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() < 3)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "431 * PRIVMSG :Not enought argument\n");
		//write(allFds.userData[user].fd, "ERR_NEEDMOREPARAMS", 18);
		return ;
	}
	
	for (size_t i = 2; i < splitBuff.size(); i++)
	{
		msg += (" " + splitBuff[i]);
	}

	std::vector<std::string> dest;
	split(splitBuff[1], ',', dest);
	for (size_t i = 0; i < dest.size(); i++)
	{
		send_msg(allFds, msg, dest[i], userNbr);
	}
}

void send_msg(fdList &allFds, std::string msg, std::string dest, int userNbr)
{
	int fd;
	//find dest
	std::string fullMsg;
	fullMsg = "*" + allFds.userData[userNbr].nickname + "* " + msg;
	fd = find_channel(allFds, dest); //return channel nbr
	if (fd != -1)
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
		for (size_t i = 0; i < allFds.channelList[fd].userList.size(); i++)
		{
			std::cout << "send nickname " << allFds.channelList[fd].userList[i]->nickname << std::endl;
			ft_putstr_fd(allFds.channelList[fd].userList[i]->fd, fullMsg);
			std::cout << "loop here\n";
		}
		return ;
	}
	
	fd = find_user(allFds, dest); //return direct user fd
	if (fd != -1)
	{
		ft_putstr_fd(fd, fullMsg);
		return ;
	}
	std::cout << "error msg\n";
	//ft_putstr_fd(fd, msg);
}