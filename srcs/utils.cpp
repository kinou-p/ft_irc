/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 21:46:41 by apommier          #+#    #+#             */
/*   Updated: 2023/02/12 20:52:45 by apommier         ###   ########.fr       */
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

int contain_any(std::string str, std::string toFind)
{
	for (int i = 0; toFind[i] != -1; i++)
	{
		if (str.find(toFind[i]) != std::string::npos)
			return (1);
	}
	return (0);
}

// void find_user_in_chan(fdList &allFds, channelData *chan)
// {
	
// }

