/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:28:38 by apommier          #+#    #+#             */
/*   Updated: 2023/02/15 15:41:43 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

//           ERR_NONICKNAMEGIVEN             ERR_ERRONEUSNICKNAME
//           ERR_NICKNAMEINUSE               ERR_NICKCOLLISION

void	NICK(std::string buffer, fdList &allFds, int userNbr)
{
	std::vector<std::string> splitBuff;
	
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() < 2)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "431 * NICK :No nickname given\n");
		return ;
	}
	if (!not_contain_other(splitBuff[1], "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789`|^_-{}[]\\"))
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "432 * " + splitBuff[1] + " :Erroneous nickname\n");
		return ;
	}
	if (find_user(allFds, splitBuff[1]) != -1)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "433 * " + splitBuff[1] + " :Nickname is already in use\n");
		return ;
	}
	//if nickname ok then (another user has it? )
	//ERR_NONICKNAMEGIVEN
	allFds.userData[userNbr].nickname = splitBuff[1];
	if (!allFds.userData[userNbr].registered && !allFds.userData[userNbr].userName.empty() /*&& !allFds.userData[userNbr].password.empty()*/)
	{
		connect_client(allFds, userNbr);
		// allFds.userData[userNbr].registered = 1;
		// print_registered_msg(allFds, userNbr);
	}
	
	return ;
}