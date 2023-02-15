/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_client.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:30:11 by apommier          #+#    #+#             */
/*   Updated: 2023/02/15 00:15:32 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

void print_registered_msg(fdList &allFds, int userNbr)
{
	(void)allFds;
	(void)userNbr;

	std::string msg;
	msg = ":irc.local 001 " + allFds.userData[userNbr].nickname + " : Welcome to the Internet Relay Network " + allFds.userData[userNbr].nickname + "!" + allFds.userData[userNbr].userName + "@" + allFds.userData[userNbr].hostName + "\n";
	send(allFds.userData[userNbr].fd, msg.c_str(), msg.size(), 0);
	msg = ":irc.local 002 " + allFds.userData[userNbr].nickname + " : Your host is irc.local" + ", running version InspIRCd-3\n"; //+ allFds.userData[userNbr].nickname + "!" + allFds.userData[userNbr].userName + "@" + allFds.userData[userNbr].hostName;
	send(allFds.userData[userNbr].fd, msg.c_str(), msg.size(), 0);
	msg = ":irc.local 003 " + allFds.userData[userNbr].nickname + " : This server was created " + allFds.creation_date + "\n";//<date>;
	send(allFds.userData[userNbr].fd, msg.c_str(), msg.size(), 0);
	msg = ":irc.local 004 " + allFds.userData[userNbr].nickname + "irc.local " + "InspIRCd-3 " + "iosw " + "biklmnopstv\n";
	//<servername> <version> <available user modes> <available channel modes
	send(allFds.userData[userNbr].fd, msg.c_str(), msg.size(), 0);
	
	
	
	// 001    RPL_WELCOME
    //           "Welcome to the Internet Relay Network
    //            <nick>!<user>@<host>"
    // 002    RPL_YOURHOST
    //           "Your host is <servername>, running version <ver>"
    // 003    RPL_CREATED
    //           "This server was created <date>"
    // 004    RPL_MYINFO
    //           "<servername> <version> <available user modes>
    //            <available channel modes>"
	
			   
	// ft_putstr_fd(allFds.userData[userNbr].fd, "-------------------WELCOME TO MY PERSONNAL IRC SERVER!-------------------" );
	// ft_putstr_fd(allFds.userData[userNbr].fd, "your nickname is |" + allFds.userData[userNbr].nickname );
	// ft_putstr_fd(allFds.userData[userNbr].fd, "your password is |" + allFds.userData[userNbr].password );
	// ft_putstr_fd(allFds.userData[userNbr].fd, "your username is |" + allFds.userData[userNbr].userName );
	// ft_putstr_fd(allFds.userData[userNbr].fd, "your realname is |" + allFds.userData[userNbr].realName );
	// ft_putstr_fd(allFds.userData[userNbr].fd, "your hostname is |" + allFds.userData[userNbr].hostName );
	// ft_putstr_fd(allFds.userData[userNbr].fd, "your servername is |" + allFds.userData[userNbr].serverName );
}

void connect_client(fdList &allFds, int userNbr)
{
	std::cout << "connect client start\n";
	
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