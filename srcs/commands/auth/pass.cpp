/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:40:42 by apommier          #+#    #+#             */
/*   Updated: 2023/03/10 22:21:05 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"



void	PASS(std::string buffer, fdList &allFds, int userNbr)
{
	std::string password;


	if (buffer.size() < 6)// ---PASS ---
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "461 * PASS :Not enough parameters\r\n");
		return ;
	}
	if (allFds.userData[userNbr].registered)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "462 * PASS :You may not reregister\r\n");
		return ;
	}
	
	// if (splitBuff.size() != 2)
	// {
	// 	cmd_error(allFds, userNbr, "461 * PASS :Not enough parameters");
	// 		//write(allFds.userData[userNbr].fd, "ERR_NEEDMOREPARAMS", 18);
	// 	return ;
	// }

	password = buffer.substr(5, buffer.npos);
	allFds.userData[userNbr].password = password;

	if (!allFds.userData[userNbr].userName.empty() && !allFds.userData[userNbr].nickname.empty())
	{
		connect_client(allFds, userNbr);
		// allFds.userData[userNbr].registered = 1;
		// print_registered_msg(allFds, userNbr);
	}
}