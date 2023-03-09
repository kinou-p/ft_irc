/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:27:37 by apommier          #+#    #+#             */
/*   Updated: 2023/03/09 05:45:36 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sys/socket.h> //socket function

#include <netinet/in.h>//inet
#include <arpa/inet.h>

#include <cstdlib>
#include <exception>

#include <cctype> //toupper
#include <ctime>
#include <cstring> //std::string
#include <cerrno> //errno
#include <iostream> //std::cout | cerr
#include <netinet/in.h> //struct socket
#include <sys/epoll.h> //epoll ensemble
#include <unistd.h> //close(0)
#include <fcntl.h> //fcntl
#include <vector>
#include <algorithm>
#include <list>

#include <sstream>

#include "function_tab.hpp"
#include "accessList.hpp"

#define MAX_EVENTS 5
#define MAX_CHAN 10
#define READ_SIZE 10
#define CMD_NBR 10
#define OP_PASSWORD "q"
#define OP_NAME "q"


	// if (!allFds.userData[userNbr].registered) 
	// {
	// 	/*change error*/
	// 	cmd_error(allFds, allFds.userData[userNbr].fd, "451 * JOIN :You have not registered\n"); //ERR_NEEDMOREPARAMS
	// 	return ;
	// }

/* ************************************************************************** */
/* *********************************STRUCT*********************************** */
/* ************************************************************************** */

struct channelData;

struct chanMode
{
	bool o; //- donne/retire les privilèges d'opérateur de canal
	bool p; //- drapeau de canal privé *
	bool s; //- drapeau de canal secret *
	bool i; //- drapeau de canal accessible uniquement sur invitation
	bool t; //- drapeau de sujet de canal modifiable uniquement par les opérateurs
	bool n; //- pas de messages dans un canal provenant de clients à l'extérieur du canal
	bool m; //- canal modéré
	bool l; //- définit le nombre maximal de personnes dans un canal
	bool b; //- définit un masque de bannissement pour interdire l'accès à des utilisateurs
	bool v; //- donne/retire la possibilité de parler dans un canal modéré
	bool k; //- définit la clé du canal (mot de passe)
	chanMode() 
	: o(0),
	p(0),
	s(0),
	i(0),
	t(0),
	n(1),
	m(0),
	l(0),
	b(0),
	v(0),
	k(0)	{}
								
};

struct userMode
{
	bool i; //- marque un utilisateur comme invisible ;
	bool s; //- marque un utilisateur comme recevant les notifications du serveur ;
	bool w; //- l'utilisateur reçoit les WALLOPs ;
	bool o; //- drapeau d'opérateur.
	
	userMode()
	: i(0),
	s(1),
	w(0),
	o(0)	{}
};

struct clientData //each client have one
{
	bool registered;

	struct sockaddr_in addr;
	std::string ip;

	std::string nickname;
	std::string password;

	std::string userName;
	std::string realName;
	std::string hostName;
	std::string serverName;

	std::string cmdBuffer;
	std::vector<channelData *> joinedChan;

	userMode mode;
	
	int fd;
	int op;
	clientData() : registered(0), op(0) {}
	// { registered = 0; op = 0;}
};

struct channelData //each chan have one
{
	std::string name;
	std::string topic;

	std::vector<clientData *> userList;
	std::vector<clientData *> banList;
	std::vector<clientData *> invitedList;
	std::vector<clientData *> verboseList;
	std::vector<clientData *> opList;

	chanMode mode;
	std::string password;
	int	maxUser;
	//int banMask ???

	int nbrUser;
};

struct fdList //&allFds in code | /!\ only one on the server | REFERENCE ONLY
{
		struct epoll_event events[MAX_EVENTS];
		int epollFd;
		int serverFd;
		std::vector<int> userFdList;
		
		accessList<channelData>	channelList;
		accessList<clientData> userData;

		int alive;
		std::string password;
		std::string creation_date;
		int nbrUser;
		functionTab parsingTab;
};

/* ************************************************************************** */
/* *******************************DEL USER*********************************** */
/* ************************************************************************** */

void	del_user_in_chan(clientData *user, channelData *chan);
void	del_chan_in_user(clientData *user, channelData *chan);
void	delete_user(fdList &allFds, int userNbr);

/* ************************************************************************** */
/* *********************************UTILS************************************ */
/* ************************************************************************** */

int		find_client_list(std::vector<clientData *> &list, clientData *client);
void	ft_putstr_fd(int fd, std::string str);
void	cmd_error(fdList &allFds, int userNbr, std::string error);
void	cmd_reply(fdList &allFds, int userNbr, std::string error);
void	ft_error(std::string str);
void	close_fd(int fd);
int		contain_any(std::string str, std::string toFind);
int		not_contain_other(std::string str, std::string toFind);

/* ************************************************************************** */
/* *******************************AUTH UTILS********************************* */
/* ************************************************************************** */

void	print_registered_msg(fdList &allFds, int userNbr);

/* ************************************************************************** */
/* *******************************CMD UTILS********************************** */
/* ************************************************************************** */

void	split(std::string const &str, const char delim, std::vector<std::string> &out);
void	split_but_keep(std::string const &str, const char delim, std::vector<std::string> &out); //same as split but keep one delimeter


/* ************************************************************************** */
/* *******************************CHAN UTILS********************************* */
/* ************************************************************************** */

int		is_in_same(fdList &allFds, int userNbr, int userNbr2);
int		is_chan_op(fdList &allFds, channelData *chanName, int userNbr);
int		is_joined(fdList &allFds, std::string chanName, int userNbr);
int		find_channel(fdList &allFds, std::string chanName);
int		find_user(fdList &allFds, std::string userName);
void	send_msg(fdList &allFds, std::string msg, std::string dest, int userNbr); //in privmsg.cpp

/* ************************************************************************** */
/* ******************************START SERVER******************************** */
/* ************************************************************************** */

void	initialize(char **av); //start_server.cpp
void	start_loop(fdList &allFds); //server_loop.cpp

/* ************************************************************************** */
/* *****************************EPOLL UTILITY******************************** */
/* ************************************************************************** */

void	epoll_add(int epollFd, int fd);
int		epoll_start();											//2nd

/* ************************************************************************** */
/* *************************CONNECTION AND REQUEST*************************** */
/* ************************************************************************** */

void	new_connection(fdList &allFds);
bool	clientRequest(fdList &allFds, int userNbr);
void	connect_client(fdList &allFds, int userNbr);

/* ************************************************************************** */
/* ***************************COMMANDS PARSING******************************* */
/* ************************************************************************** */

void	parse_commands(std::string buffer, fdList &allFds, int userNbr);

/* ************************************************************************** */
/* ******************************MODE UTILS********************************** */
/* ************************************************************************** */

void	ban_reply(channelData &chan, clientData &user);
void	chan_reply(channelData &chan, clientData &user);
void	user_reply(clientData &user);
int		search_and_erase(std::string &str, std::string toFind);
bool	str_to_int(int &i, const std::string s);
