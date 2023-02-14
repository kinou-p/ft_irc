/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_client.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:30:11 by apommier          #+#    #+#             */
/*   Updated: 2023/02/14 02:19:19 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

void connect_client(fdList &allFds, int userNbr)
{
	// allFds.userData[userNbr].fd
	std::cout << "connect client start\n";
	// if (-1 == connect(allFds.userData[userNbr].fd, (struct sockaddr *)&allFds.userData[userNbr].addr, sizeof(allFds.userData[userNbr].addr)))
	// 	ft_error("connect() error");
	
	if (allFds.userData[userNbr].password.empty() || allFds.userData[userNbr].password != allFds.password)
	{
		std::cout << "password= " << allFds.userData[userNbr].password << std::endl;
		cmd_error(allFds, allFds.userData[userNbr].fd, "464 * :Password incorrect\n");
		return ;
	}
   	//464    ERR_PASSWDMISMATCH
    //":Password incorrect"

	allFds.userData[userNbr].registered = 1;
	print_registered_msg(allFds, userNbr);
	std::cout << "connect client end\n";
	//ft_putstr_fd(allFds.userData[userNbr].fd, ":irc.local NOTICE kinou :*** Could not resolve your hostname: Request timed out; using your IP address (172.17.0.1) instead.\nirc.local 376 kinou :End of message of the day.");
}