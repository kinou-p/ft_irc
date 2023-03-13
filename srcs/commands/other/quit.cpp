/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:10:26 by apommier          #+#    #+#             */
/*   Updated: 2023/03/13 16:38:01 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

void	send_quit_msg(fdList &allFds, int userNbr, std::string msg)
{
	std::string fullMsg;

	fullMsg = ":" + allFds.userData[userNbr].nickname + "!" + allFds.userData[userNbr].userName + "@" + allFds.userData[userNbr].ip + " QUIT :" + msg + "\r\n";
	for (size_t i = 0; i < allFds.userData[userNbr].joinedChan.size(); i++)
	{
		for (size_t j = 0; j < allFds.userData[userNbr].joinedChan[i]->userList.size(); j++)
		{
			if (allFds.userData[userNbr].joinedChan[i]->userList[j] != &allFds.userData[userNbr])
			{
				if (allFds.userData[userNbr].joinedChan[i]->userList[j]->mode.s)
					send(allFds.userData[userNbr].joinedChan[i]->userList[j]->fd, fullMsg.c_str(), fullMsg.size(), 0);
			}
		}
	}
}

void	QUIT(std::string buffer, fdList &allFds, int userNbr)
{
	std::vector<std::string> splitBuff;
	
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() > 2)
		send_quit_msg(allFds, userNbr, buffer.substr(5, std::string::npos));//to test
	else
		send_quit_msg(allFds, userNbr, allFds.userData[userNbr].nickname);
	delete_user(allFds, userNbr);
	return ;
}