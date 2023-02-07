/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:27:37 by apommier          #+#    #+#             */
/*   Updated: 2023/02/07 20:25:26 by apommier         ###   ########.fr       */
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

#define MAX_EVENTS 5
#define READ_SIZE 10
#define CMD_NBR 10

//struct functionTab;
struct fdList;

//std::string ft_test();

/* ************************************************************************** */
/* *********************************COMMANDS********************************* */
/* ************************************************************************** */

		void	PASS(std::string buffer, fdList allFds, int user);
		void	NICK(std::string buffer, fdList allFds, int user);
		void	USER(std::string buffer, fdList allFds, int user);
		void	SERVER(std::string buffer, fdList allFds, int user);
		void	OPER(std::string buffer, fdList allFds, int user);
		void	QUIT(std::string buffer, fdList allFds, int user);
		void	SQUIT(std::string buffer, fdList allFds, int user);
		void	JOIN(std::string buffer, fdList allFds, int user);
		void	PART(std::string buffer, fdList allFds, int user);
		void	MODE(std::string buffer, fdList allFds, int user);
		void	TOPIC(std::string buffer, fdList allFds, int user);
		void	NAMES(std::string buffer, fdList allFds, int user);
		void	LIST(std::string buffer, fdList allFds, int user);
		void	INVITE(std::string buffer, fdList allFds, int user);
		void	KICK(std::string buffer, fdList allFds, int user);
		void	VERSION(std::string buffer, fdList allFds, int user);
		void	STATS(std::string buffer, fdList allFds, int user);
		void	LINKS(std::string buffer, fdList allFds, int user);
		void	TIME(std::string buffer, fdList allFds, int user);
		void	CONNECT(std::string buffer, fdList allFds, int user);
		void	TRACE(std::string buffer, fdList allFds, int user);
		void	ADMIN(std::string buffer, fdList allFds, int user);
		void	INFO(std::string buffer, fdList allFds, int user);
		void	PRIVMSG(std::string buffer, fdList allFds, int user);
		void	NOTICE(std::string buffer, fdList allFds, int user);
		void	WHO(std::string buffer, fdList allFds, int user);
		void	WHOIS(std::string buffer, fdList allFds, int user);
		void	WHOWAS(std::string buffer, fdList allFds, int user);
		void	KILL(std::string buffer, fdList allFds, int user);
		void	PING(std::string buffer, fdList allFds, int user);
		void	PONG(std::string buffer, fdList allFds, int user);
		void	ERROR(std::string buffer, fdList allFds, int user);
		void	AWAY(std::string buffer, fdList allFds, int user);
		void	REHASH(std::string buffer, fdList allFds, int user);
		void	RESTART(std::string buffer, fdList allFds, int user);
		void	SUMMON(std::string buffer, fdList allFds, int user);
		void	USER(std::string buffer, fdList allFds, int user);
		void	OPERWALL(std::string buffer, fdList allFds, int user);
		void	USERHOST(std::string buffer, fdList allFds, int user);
		void	ISON(std::string buffer, fdList allFds, int user);


/* ************************************************************************** */
/* *****************************COMMAND STRUCT******************************* */
/* ************************************************************************** */

struct functionTab
{
	static const int cmdNbr = 40;
	std::string cmdName[cmdNbr] =
	{
		//4. Détails des messages

			//4.1 Etablissement de connexion
		"PASS",
		"NICK",
		"USER",
		"SERVER",
		"OPER",
		"QUIT",
		"SQUIT",
		
			//4.2 Opérations sur les canaux
		"JOIN",
		"PART",
		"MODE",
		"TOPIC",
		"NAMES",
		"LIST",
		"INVITE",
		"KICK",

			//4.3 Requêtes et commandes des serveurs
		"VERSION",
		"STATS",
		"LINKS",
		"TIME",
		"CONNECT",
		"TRACE",
		"ADMIN",
		"INFO",
		
			//4.4 Envoi de messages
		"PRIVMSG",
		"NOTICE",

			//4.5 Requêtes basées sur les utilisateurs

		"WHO",
		"WHOIS",
		"WHOWAS",
			//4.6 Messages divers
		
		"KILL",
		"PING",
		"PONG",
		"ERROR",
		
		//5. Messages optionnels
		"AWAY",
		"REHASH",
		"RESTART",
		"SUMMON",
		"USER",
		"OPERWALL",
		"USERHOST",
		"ISON"
	};


	//std::string (*cmdPtr[cmdNbr])(void) = 
	void (*cmdPtr[cmdNbr])(std::string buffer, fdList allFds, int user) = 
	{
		//ft_test

		//4. Détails des messages

		// 	//4.1 Etablissement de connexion
		// PASS,
		NICK
		// USER,
		// SERVER,
		// OPER,
		// QUIT,
		// SQUIT,
	
		// //4.2 Opérations sur les canaux
		// JOIN,
		// PART,
		// MODE,
		// TOPIC,
		// NAMES,
		// LIST,
		// INVITE,
		// KICK,

		// 	//4.3 Requêtes et commandes des serveurs
		// VERSION,
		// STATS,
		// LINKS,
		// TIME,
		// CONNECT,
		// TRACE,
		// ADMIN,
		// INFO,
		
		// 	//4.4 Envoi de messages
		// PRIVMSG,
		// NOTICE,

		// 	//4.5 Requêtes basées sur les utilisateurs

		// WHO,
		// WHOIS,
		// WHOWAS,
		// 	//4.6 Messages divers
		
		// KILL,
		// PING,
		// PONG,
		// ERROR,
		
		// 	//5. Messages optionnels
		// AWAY,
		// REHASH,
		// RESTART,
		// SUMMON,
		// USER,
		// OPERWALL,
		// USERHOST,
		// ISON
	};
};

/* ************************************************************************** */
/* *********************************STRUCT*********************************** */
/* ************************************************************************** */

struct channelData;

struct clientData
{
	bool registered = 0;
	std::string buf[1024];
	std::string nickname;
	std::string password;
	
	std::string userName;
	std::string realName;
	std::string hostName;
	std::string serverName;
	
	//std::string joinedChan[20];
	channelData *joinedChan; //is there a limit?
	int nbrChan;
	int	perm;
	int fd;
};

struct channelData
{
	//std::string	userList[MAX_EVENTS];
	clientData userList[MAX_EVENTS];
	int op;
	int nbrUser;
};



struct fdList //allFds in code
{
		struct epoll_event events[MAX_EVENTS];
		int epollFd;
		int serverFd;
		int userList[MAX_EVENTS]; //list of user's fd
		clientData userData[MAX_EVENTS]; 
		int nbrUser;
		functionTab parsingTab;
};





/* ************************************************************************** */
/* *********************************UTILS************************************ */
/* ************************************************************************** */

void ft_error(std::string str);
void close_fd(int fd);

/* ************************************************************************** */
/* ******************************START SERVER******************************** */
/* ************************************************************************** */

void cmd_error(fdList allFds, int user, std::string error);
void split(std::string const &str, const char delim, std::vector<std::string> &out);
void initialize(char **av);									//1st
void start_loop(fdList allFds);								//3rd

/* ************************************************************************** */
/* *****************************EPOLL UTILITY******************************** */
/* ************************************************************************** */

void epoll_add(int epollFd, int fd);
int epoll_start();											//2nd

/* ************************************************************************** */
/* *************************CONNECTION AND REQUEST*************************** */
/* ************************************************************************** */

void new_connection(fdList allFds, struct epoll_event newClient);
bool clientRequest(fdList allFds, int user);

/* ************************************************************************** */
/* ***************************COMMANDS PARSING******************************* */
/* ************************************************************************** */

void parse_commands(std::string buffer, fdList allFds, int user);

