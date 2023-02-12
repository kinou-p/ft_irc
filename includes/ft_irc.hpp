/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:27:37 by apommier          #+#    #+#             */
/*   Updated: 2023/02/11 22:49:29 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sys/socket.h> //socket function
#include <cstdlib> 
#include <cstring> //std::string
#include <cerrno> //errno
#include <iostream> //std::cout | cerr
#include <netinet/in.h> //struct socket
#include <sys/epoll.h> //epoll ensemble
#include <unistd.h> //close()
#include <fcntl.h> //fcntl
#include <vector>
#include <algorithm>

#include "function_tab.hpp"

#define MAX_EVENTS 5
#define MAX_CHAN 10
#define READ_SIZE 10
#define CMD_NBR 10

/* ************************************************************************** */
/* *********************************STRUCT*********************************** */
/* ************************************************************************** */

struct channelData;

struct clientData //each client have one
{
	bool registered;

	clientData() { registered = 0; }
	std::string nickname;
	std::string password;

	std::string userName;
	std::string realName;
	std::string hostName;
	std::string serverName;

	std::string cmdBuffer;
	std::vector<channelData *> joinedChan;
	int fd;
};

struct channelData //each chan have one
{
	std::string name;
	std::vector<clientData *> userList;
	std::vector<clientData *> banList;
	int op;
	int nbrUser;
};

struct fdList //&allFds in code | /!\ only one on the server | REFERENCE ONLY
{
		struct epoll_event events[MAX_EVENTS];
		int epollFd;
		int serverFd;
		std::vector<int> userList;
		std::vector<channelData> channelList;
		std::vector<clientData> userData;

		// std::map<int, channelData> channelList;
		// std::map<int, clientData> userData;
		
		int nbrUser;
		functionTab parsingTab;
};



/* ************************************************************************** */
/* *********************************UTILS************************************ */
/* ************************************************************************** */

void ft_putstr_fd(int fd, std::string str);
void cmd_error(fdList &allFds, int userNbr, std::string error);
void ft_error(std::string str);
void close_fd(int fd);
void del_user_in_chan(clientData *user, channelData *chan);
void delete_user(fdList &allFds, int userNbr);

/* ************************************************************************** */
/* *******************************AUTH UTILS********************************* */
/* ************************************************************************** */

void print_registered_msg(fdList &allFds, int userNbr);

/* ************************************************************************** */
/* *******************************CMD UTILS********************************** */
/* ************************************************************************** */

void split(std::string const &str, const char delim, std::vector<std::string> &out);
void split_but_keep(std::string const &str, const char delim, std::vector<std::string> &out); //same as split but keep one delimeter


/* ************************************************************************** */
/* *******************************CHAN UTILS********************************* */
/* ************************************************************************** */

int find_channel(fdList &allFds, std::string chanName);
int find_user(fdList &allFds, std::string userName);
void send_msg(fdList &allFds, std::string msg, std::string dest, int userNbr); //in privmsg.cpp

/* ************************************************************************** */
/* ******************************START SERVER******************************** */
/* ************************************************************************** */

void initialize(char **av); //start_server.cpp
void start_loop(fdList &allFds); //server_loop.cpp

/* ************************************************************************** */
/* *****************************EPOLL UTILITY******************************** */
/* ************************************************************************** */

void epoll_add(int epollFd, int fd);
int epoll_start();											//2nd

/* ************************************************************************** */
/* *************************CONNECTION AND REQUEST*************************** */
/* ************************************************************************** */

void new_connection(fdList &allFds);
bool clientRequest(fdList &allFds, int userNbr);

/* ************************************************************************** */
/* ***************************COMMANDS PARSING******************************* */
/* ************************************************************************** */

void parse_commands(std::string buffer, fdList &allFds, int userNbr);

