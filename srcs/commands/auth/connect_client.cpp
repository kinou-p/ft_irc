/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_client.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:30:11 by apommier          #+#    #+#             */
/*   Updated: 2023/02/13 11:04:52 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

void connect_client(fdList &allFds, int userNbr)
{
	// allFds.userData[userNbr].fd
	std::cout << "connect client start\n";
	// if (-1 == connect(allFds.userData[userNbr].fd, (struct sockaddr *)&allFds.userData[userNbr].addr, sizeof(allFds.userData[userNbr].addr)))
	// 	ft_error("connect() error");
	
	allFds.userData[userNbr].registered = 1;
	print_registered_msg(allFds, userNbr);
	std::cout << "connect client end\n";
	//ft_putstr_fd(allFds.userData[userNbr].fd, ":irc.local NOTICE kinou :*** Could not resolve your hostname: Request timed out; using your IP address (172.17.0.1) instead.\nirc.local 376 kinou :End of message of the day.");
}