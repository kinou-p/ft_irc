/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:27:37 by apommier          #+#    #+#             */
/*   Updated: 2023/02/10 09:59:10 by apommier         ###   ########.fr       */
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
#include <vector>
#include <algorithm>

#include "function_tab.hpp"

#define MAX_EVENTS 5
#define READ_SIZE 10
#define CMD_NBR 10

/* ************************************************************************** */
/* *********************************STRUCT*********************************** */
/* ************************************************************************** */

struct channelData;

struct clientData
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
	//std::string joinedChan[20];
	//channelData *joinedChan; //is there a limit?
	
	// std::vector<std::string> joinedChan;
	std::vector<channelData *> joinedChan;
	int fd;
};

struct channelData
{
	//std::string	userList[MAX_EVENTS];
	
	//clientData userList[MAX_EVENTS];
	std::string name;
	std::vector<clientData> userList;
	std::vector<clientData> banList;
	int op;
	int nbrUser;
};



struct fdList //&allFds in code
{
		struct epoll_event events[MAX_EVENTS];
		int epollFd;
		int serverFd;
		//int userList[MAX_EVENTS]; //list of userNbr's fd
		std::vector<int> userList;
		std::vector<channelData> channelList;
		//clientData userData[MAX_EVENTS];
		std::vector<clientData> userData;
		
		int nbrUser;
		functionTab parsingTab;
};





/* ************************************************************************** */
/* *******************************CMD UTILS********************************** */
/* ************************************************************************** */

void ft_error(std::string str);
void close_fd(int fd);
void cmd_error(fdList &allFds, int userNbr, std::string error);
void split(std::string const &str, const char delim, std::vector<std::string> &out);
void print_registered_msg(fdList &allFds, int userNbr);

/* ************************************************************************** */
/* *******************************CHAN UTILS********************************* */
/* ************************************************************************** */

int find_channel(fdList &allFds, std::string chanName);

/* ************************************************************************** */
/* ******************************START SERVER******************************** */
/* ************************************************************************** */

void initialize(char **av);									//1st
void start_loop(fdList &allFds);								//3rd

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

