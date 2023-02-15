/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:10:26 by apommier          #+#    #+#             */
/*   Updated: 2023/02/15 13:27:15 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

void	send_quit_msg(fdList &allFds, int userNbr, std::string msg)
{
	std::string fullMsg;

	// if (msg.empty())
	// 	fullMsg = ":" + allFds.userData[userNbr].nickname + "!" + allFds.userData[userNbr].userName + "@" + allFds.userData[userNbr].ip + " QUIT :" + joined_chan.name + "\n";
	// else 
	fullMsg = ":" + allFds.userData[userNbr].nickname + "!" + allFds.userData[userNbr].userName + "@" + allFds.userData[userNbr].ip + " QUIT :" + msg + "\n";
	for (size_t i = 0; i < allFds.userData[userNbr].joinedChan.size(); i++)
	{
		//allFds.userData[userNbr].joinedChan[i]->
		//send(joined_chan.userList[i]->fd, fullMsg.c_str(), fullMsg.size(), 0);

		for (size_t j = 0; j < allFds.userData[userNbr].joinedChan[i]->userList.size(); j++)
		{
			//std::cout << "send nickname " << allFds.userData[userNbr].joinedChan[i]->userList[j]->nickname << std::endl;
			if (allFds.userData[userNbr].joinedChan[i]->userList[j] != &allFds.userData[userNbr])
				send(allFds.userData[userNbr].joinedChan[i]->userList[j]->fd, fullMsg.c_str(), fullMsg.size(), 0);
			else
				std::cout << "hehe je quitte\n";
			std::cout << "loop here\n";
		}
	}
}

void	QUIT(std::string buffer, fdList &allFds, int userNbr)
{
	std::vector<std::string> splitBuff;
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() == 2)
	{
		send_quit_msg(allFds, userNbr, splitBuff[2]);
		//print message?
		//:kinou2!kinou@172.17.0.1 QUIT :Quit: leaving
	}
	else
		send_quit_msg(allFds, userNbr, allFds.userData[userNbr].nickname);
	delete_user(allFds, userNbr);
	return ;
}