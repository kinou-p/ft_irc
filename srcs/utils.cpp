/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 21:46:41 by apommier          #+#    #+#             */
/*   Updated: 2023/02/12 14:31:10 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_irc.hpp"

void ft_error(std::string str)
{
	std::cerr << str << std::endl;
	if (errno)
	{
		std::cerr << "errno: " << strerror(errno);
		exit(errno);
	}
	exit(1);
}

void close_fd(int fd)
{
	if (close(fd))
		ft_error("close() error");
}

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

// void find_user_in_chan(fdList &allFds, channelData *chan)
// {
	
// }

void del_user_in_chan(clientData *user, channelData *chan)
{
	size_t i;
	for (i = 0; user != chan->userList[i]; i++)
		;
	chan->userList.erase(chan->userList.begin() + i);
}

void delete_user(fdList &allFds, int userNbr)
{
	std::cout << "Delete user nbr " << userNbr << std::endl;
	
	for (size_t i = 0; i < allFds.userData[userNbr].joinedChan.size(); i++)//all joined chan
	{
		del_user_in_chan(&allFds.userData[userNbr], allFds.userData[userNbr].joinedChan[i]);
		//allFds.userData[userNbr].joinedChan[i].erase(find_user_in_chan(allFds.userData[userNbr].joinedChan[i])/*find user in chan*/)
	}
	close(allFds.userData[userNbr].fd);
	
	allFds.userData.erase(allFds.userData.begin() + userNbr);
	allFds.userList.erase(allFds.userList.begin() + userNbr);
	
	allFds.nbrUser--;
}