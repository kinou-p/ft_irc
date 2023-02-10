/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:45:45 by apommier          #+#    #+#             */
/*   Updated: 2023/02/10 09:27:27 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

void ft_putstr_fd(int fd, std::string str)
{
	write(fd, str.c_str(), str.size());
	write(fd, "\n", 1);
}

void cmd_error(fdList &allFds, int fd, std::string error)
{
	(void)allFds; //to delete
	write(fd, ":irc.local ", 11);
	write(fd, error.c_str(), error.size());
}

void split(std::string const &str, const char delim, std::vector<std::string> &out)
{
    size_t start;
    size_t end = 0;
 
    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}

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