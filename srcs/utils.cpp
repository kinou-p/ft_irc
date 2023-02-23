/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 21:46:41 by apommier          #+#    #+#             */
/*   Updated: 2023/02/23 20:29:25 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_irc.hpp"

void ft_error(std::string str)
{
	std::cerr << str << std::endl;
	if (errno)
	{
		std::cerr << "errno: " << strerror(errno) << std::endl;
		throw ;//std::bad_alloc();
		//exit(errno);
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
	// write(fd, str.c_str(), str.size());
	// write(fd, "\n", 1);
	str += "\n";
	send(fd, str.c_str(), str.size(), 0);
}

void cmd_error(fdList &allFds, int fd, std::string error)
{
	(void)allFds; //to delete
	error = ":irc.local " + error;
	//write(fd, ":irc.local ", 11);
	//write(fd, error.c_str(), error.size());
	send(fd, error.c_str(), error.size(), 0);
}

void cmd_reply(fdList &allFds, int fd, std::string error)
{
	
	(void)allFds; //to delete
	error = ":irc.local " + error;
	//std::cout << cmd_reply= --- << error << "---";
	//write(fd, ":irc.local ", 11);
	//write(fd, error.c_str(), error.size());
	send(fd, error.c_str(), error.size(), 0);
}

int contain_any(std::string str, std::string toFind)
{
	for (int i = 0; toFind[i] != 0; i++)
	{
		if (str.find(toFind[i]) != std::string::npos)
			return (1);
	}
	return (0);
}

int not_contain_other(std::string str, std::string toFind)
{
	for (int i = 0; str[i] != 0; i++)
	{
		if (toFind.find(str[i]) == std::string::npos)
			return (0);
	}
	return (1);
}

int find_client_list(std::vector<clientData *> &list, clientData *client)
{
	std::vector<clientData*>::iterator start = list.begin();
	std::vector<clientData*>::iterator  pastEnd = list.end();
	while (start != pastEnd)
	{
		if (*start == client)
			return (start - pastEnd - 1);	
		start++;
	}
	return (-1);
}