/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squit.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:11:03 by apommier          #+#    #+#             */
/*   Updated: 2023/02/15 20:05:27 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

//ERR_NOPRIVILEGES                ERR_NOSUCHSERVER

void	SQUIT(std::string buffer, fdList &allFds, int userNbr)
{
	// (void)buffer; 
	// (void)allFds;
	// (void)userNbr;
	std::cout << "squit | server end\n";
	std::vector<std::string> splitBuff;
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() < 2)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "431 * SQUIT :Not enought argument\n");
		return ;
	}
	if (!allFds.userData[userNbr].op)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "481 * :Permission Denied- You're not an IRC operator\n");
		return ;
	}
	std::cout << "squit serv= " << splitBuff[2] << std::endl;
	if (splitBuff[1] != "irc.local")
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "402 * " + splitBuff[2] + " :No such server\n");
		return ;
	}
	std::cout << "squit | alive = 0\n";
	allFds.alive = 0;
	// if (allFds.userData[userNbr].op)
	// 	allFds.alive = 0;
	// else
	// {
	// 	std::cout << "Not op but okay i'll do it\n";
	// 	allFds.alive = 0;
	// }
	return ;
}