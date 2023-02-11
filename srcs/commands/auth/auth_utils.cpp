/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auth_utils.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:45:45 by apommier          #+#    #+#             */
/*   Updated: 2023/02/11 10:40:42 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

void print_registered_msg(fdList &allFds, int userNbr)
{
	ft_putstr_fd(allFds.userData[userNbr].fd, "-------------------WELCOME TO MY PERSONNAL IRC SERVER!-------------------" );
	ft_putstr_fd(allFds.userData[userNbr].fd, "your nickname is |" + allFds.userData[userNbr].nickname );
	ft_putstr_fd(allFds.userData[userNbr].fd, "your password is |" + allFds.userData[userNbr].password );
	ft_putstr_fd(allFds.userData[userNbr].fd, "your username is |" + allFds.userData[userNbr].userName );
	ft_putstr_fd(allFds.userData[userNbr].fd, "your realname is |" + allFds.userData[userNbr].realName );
	ft_putstr_fd(allFds.userData[userNbr].fd, "your hostname is |" + allFds.userData[userNbr].hostName );
	ft_putstr_fd(allFds.userData[userNbr].fd, "your servername is |" + allFds.userData[userNbr].serverName );
}

// void delete_client(fdList &allFds)
// {
	
// }