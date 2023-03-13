/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 21:46:41 by apommier          #+#    #+#             */
/*   Updated: 2023/03/13 08:32:00 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_irc.hpp"

void ft_error(std::string str)
{
	std::cerr << str << std::endl;
	throw std::exception();
	// if (errno)
	// {
	// 	std::cerr << "errno: " << strerror(errno) << std::endl;
	// 	throw std::exception();
	// 	//exit(errno);
	// }
	//exit(1);
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
	str += "\r\n";
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
	int size = list.size();
	for (int i = 0; i < size; i++)
	{
		if (list[i] == client)
			return (i);
	}
	return (-1);
}

int print_client_list(std::vector<clientData *> &list)
{
	int size = list.size();
	std::cout << "=PRINT LIST=\n";
	for (int i = 0; i < size; i++)
	{
		std::cout << i << "= " << list[i]->nickname << std::endl;
	}
	return (-1);
}

std::string	int_to_str(int i)
{
	std::string s;
	std::stringstream out;
	out << i;
	s = out.str();
	return (s);
}