/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:28:38 by apommier          #+#    #+#             */
/*   Updated: 2023/02/12 23:37:37 by apommier         ###   ########.fr       */
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
		//write(allFds.userData[user].fd, "ERR_NEEDMOREPARAMS", 18);
		return ;
	}
	//if nickname ok then (another user has it? )
	//ERR_NONICKNAMEGIVEN
	allFds.userData[userNbr].nickname = splitBuff[1];
	if (!allFds.userData[userNbr].registered && !allFds.userData[userNbr].userName.empty())
	{
		connect_client(allFds, userNbr);
		// allFds.userData[userNbr].registered = 1;
		// print_registered_msg(allFds, userNbr);
	}
	
	return ;
}