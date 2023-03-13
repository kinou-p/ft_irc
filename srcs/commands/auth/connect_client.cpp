/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_client.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:30:11 by apommier          #+#    #+#             */
/*   Updated: 2023/03/13 16:28:12 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

void print_registered_msg(fdList &allFds, int userNbr)
{
	(void)allFds;
	(void)userNbr;

	std::string msg;
	msg = ":irc.local 001 " + allFds.userData[userNbr].nickname + " : Welcome to the Internet Relay Network " + allFds.userData[userNbr].nickname + "!" + allFds.userData[userNbr].userName + "@" + allFds.userData[userNbr].hostName + "\r\n";
	send(allFds.userData[userNbr].fd, msg.c_str(), msg.size(), 0);
	msg = ":irc.local 002 " + allFds.userData[userNbr].nickname + " : Your host is irc.local" + ", running version InspIRCd-3\r\n"; //+ allFds.userData[userNbr].nickname + "!" + allFds.userData[userNbr].userName + "@" + allFds.userData[userNbr].hostName;
	send(allFds.userData[userNbr].fd, msg.c_str(), msg.size(), 0);
	msg = ":irc.local 003 " + allFds.userData[userNbr].nickname + " : This server was created " + allFds.creation_date + "\r\n";//<date>;
	send(allFds.userData[userNbr].fd, msg.c_str(), msg.size(), 0);
	msg = ":irc.local 004 " + allFds.userData[userNbr].nickname + "irc.local " + "InspIRCd-3 " + "iosw " + "biklmnopstv\r\n";
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
	if (allFds.userData[userNbr].password.empty() || allFds.userData[userNbr].password != allFds.password)
	{
		std::cout << "password= " << allFds.userData[userNbr].password << std::endl;
		cmd_error(allFds, allFds.userData[userNbr].fd, "464 * :Password incorrect\r\n");
		return ;
	}
	allFds.userData[userNbr].registered = 1;
	print_registered_msg(allFds, userNbr);
}